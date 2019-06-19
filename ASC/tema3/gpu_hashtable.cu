#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <string>
#include <cmath>

#include "gpu_hashtable.hpp"
#include "random_generator.h" // RELIABLE RANDOM GENERATOR

#define MAX_ATTEMPTS 1000
#define MAX_INT 0xffffffff
#define JUMP 41
#define NUM_THREADS 64


const Entry EMPTY = (Entry)0xffffffff << 32;

__global__ void fill_empty(Entry *table, unsigned int table_size) {
	unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < table_size) {
		table[id] = EMPTY;
	}
}


__device__ unsigned long jump(int key) {
	return 1 + (key % JUMP);
}

__device__ unsigned long hash_func(int key, unsigned int a, unsigned int b) {
	 return ((a ^ key) + b) % MAX_INT;
}

__device__ int get_key(Entry e) {
	int key = e >> 32;
	return key;
}

__device__ int get_value(Entry e) {
	int val = e - EMPTY;
	return val;
}

__global__ void check_new_items(int *keys, int numKeys, unsigned int table_size,
			      unsigned long a, unsigned long b, Entry *table,
			      unsigned int *new_elems) {

	unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < numKeys) {
		int key = keys[id];

		 Entry entry = ((Entry) key << 32);

		/* Computer hash for the key */
		unsigned long index = hash_func(key, a, b);
		index %= table_size;

		/* Compute the jump for this key */
		unsigned long hash_jump = jump(key);
		Entry old_entry;
		/* Linear probing for maximum of MAX_ATTEMPTS or table size */
		for (unsigned long attempt = 1; attempt <= MAX_ATTEMPTS || attempt <=
		     table_size; ++attempt) {

			if (get_key(table[index]) == key) {
				atomicDec(new_elems, 1);
				return;
			}

			/* else jump to the next index */
			index += attempt * hash_jump;
			if (index >= table_size) index = 0;
		}
	}
}


/* INSERT WITH THREADS
 */
__global__ void kernel_insert(int *keys, int *values, int numKeys, unsigned int table_size,
			      unsigned long a, unsigned long b, Entry *table,
			      unsigned int *num_elements) {
	unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < numKeys) {
		int key = keys[id];
		int value = values[id];

		 Entry entry = ((Entry) key << 32) + value;

		/* Computer hash for the key */
		unsigned long index = hash_func(key, a, b);
		index %= table_size;

		/* Compute the jump for this key */
		unsigned long hash_jump = jump(key);
		Entry old_entry;
		/* Linear probing for maximum of MAX_ATTEMPTS or table size */
		for (unsigned long attempt = 1; attempt <= MAX_ATTEMPTS || attempt <=
		     table_size; ++attempt) {

			old_entry = atomicCAS(table + index, EMPTY, entry);

			/* If the table slot was empty then finish */
			if (old_entry == EMPTY) {
				atomicAdd(num_elements, 1);
				return;
			} else if (get_key(table[index]) == key) {
				atomicExch(table + index, entry);
				return;
			}

			/* else jump to the next index */
			index += attempt * hash_jump;
			if (index >= table_size) index = 0;
		}
	}
}

__global__ void rehash(Entry *old_table, unsigned int old_size, Entry *new_table,
		       unsigned int new_size, unsigned long a, unsigned long b) {

	unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;
	if (id < old_size) {

		/* If no entry in the old table return */
		if (old_table[id] == EMPTY) return;

		/* Compute key and value from old table */
		int key = old_table[id] >> 32;
		int value = old_table[id] - EMPTY;

		 Entry entry = ((Entry) key << 32) + value;

		/* Computer hash for the key */
		unsigned long index = hash_func(key, a, b);
		index %= new_size;

		/* Compute the jump for this key */
		unsigned long hash_jump = jump(key);
		Entry old_entry;
		/* Linear probing for maximum of MAX_ATTEMPTS or table size */
		for (unsigned long attempt = 1; attempt <= MAX_ATTEMPTS || attempt <=
		     new_size; ++attempt) {
			old_entry = atomicCAS(new_table + index, EMPTY, entry);

			/* If the table slot was empty then finish */
			if (old_entry == EMPTY) return;
			/* else jump to the next index */
			index += attempt * hash_jump;
			if (index >= new_size) index = 0;
		}
	}

}

__global__ void kernel_get(int *keys, int *values, int numKeys, Entry *table, unsigned int table_size,
			   unsigned long a, unsigned long b) {

	unsigned int id = blockIdx.x * blockDim.x + threadIdx.x;

	if (id < numKeys) {
		int key = keys[id];
		unsigned long index = hash_func(key, a, b);
		index %= table_size;
		unsigned long hash_jump = jump(key);
		/* Linear probing for maximum of MAX_ATTEMPTS or table size */
		for (unsigned long attempt = 1; attempt <= MAX_ATTEMPTS || attempt <=
		     table_size; ++attempt) {
			/* Retrieve value if the key is valid */
			if (get_key(table[index]) == key) {
				values[id] = get_value(table[index]);
				return;
			}

			index += attempt * hash_jump;
			if (index >= table_size) index = 0;
		}

	}
}

/* INIT HASH
 */
GpuHashTable::GpuHashTable(int size) {
	this->size = size;
	init_genrand(size);

	/* Generate random numbers for hash function */
	this->a = genrand_int32();
	this->b = genrand_int32();

	/* Number of elements is accessed both from CPU and GPU */
	cudaMalloc(&this->num_elements, 1 * sizeof(unsigned int));
	cudaMemset(this->num_elements, 0, sizeof(unsigned int));

	/* Allocate hash table and insert empty entries */
	cudaMalloc((void **)&(this->table), size * sizeof(uint64_t));
	int NUM_BLOCKS = (size + NUM_THREADS - 1) / NUM_THREADS;
	fill_empty<<<NUM_BLOCKS,NUM_THREADS>>>(this->table, size);
}

/* DESTROY HASH
 */
GpuHashTable::~GpuHashTable() {
	cudaFree(this->table);
	cudaFree(this->num_elements);
}

/* RESHAPE HASH
 */
void GpuHashTable::reshape(int numBucketsReshape) {
	Entry *new_table;
	int new_size;

	new_size = ceil(numBucketsReshape * 1.25);
	cudaMalloc((void**)&(new_table), new_size * sizeof(Entry));

	int blocks = (new_size + NUM_THREADS - 1) / NUM_THREADS;

	/* Fill new table with empty entries */
	fill_empty<<<blocks,NUM_THREADS>>>(new_table, new_size);

	int NUM_BLOCKS = (this->size + NUM_THREADS - 1) / NUM_THREADS;

	/* Rehashing old entries into the new table */
	rehash<<<NUM_BLOCKS, NUM_THREADS>>>(this->table, this->size, new_table,
					    new_size, this->a, this->b);

	cout << "Rehash Func " << "Reserve arg: " << numBucketsReshape << endl;
	this->printTable();

	cudaFree(this->table);
	this->table = new_table;
	this->size = new_size;

	cout << "New table " << endl;
	this->printTable();
	cout << "\n\n";

}

void GpuHashTable::printTable() {
	Entry *my_table;
	int *num_ele;
	num_ele = (int *)malloc(sizeof(int));
	my_table = (Entry *)malloc(sizeof(Entry) * this->size);
	cudaMemcpy(num_ele, this->num_elements, sizeof(int),
		   cudaMemcpyDeviceToHost);
	cudaMemcpy(my_table, this->table, this->size * sizeof(Entry),
		   cudaMemcpyDeviceToHost);
	cout << "Size: " << this->size << " Table: \n";
	for(int i = 0; i < this->size; ++i) {
		cout << my_table[i] << " ";
	}
	cout << endl;
	cout << "Num elements: " << *num_ele << endl;
	free(my_table);
	free(num_ele);
}




/* INSERT BATCH
 */
bool GpuHashTable::insertBatch(int *keys, int* values, int numKeys) {
	int *num_ele;
	num_ele = (int *)malloc(sizeof(int));
	cudaMemcpy(num_ele, this->num_elements, sizeof(int),
		   cudaMemcpyDeviceToHost);
	// float load = this->loadFactor();
	// if ((numKeys > this->size || numKeys > this->size - *(num_ele)) && load
	//     > 0.5) {
	// 	this->reshape(numKeys);
	// }
	if (*num_ele + numKeys > this->size * 0.7) {
		this->reshape(*num_ele + numKeys);
	}

	int *device_keys, *device_values;
	cudaMalloc((void**)&device_keys, numKeys * sizeof(int));
	cudaMalloc((void**)&device_values, numKeys * sizeof(int));
	cudaMemcpy(device_keys, keys, numKeys * sizeof(int),
		   cudaMemcpyHostToDevice);
	cudaMemcpy(device_values, values, numKeys * sizeof(int),
		   cudaMemcpyHostToDevice);

	int blocks = (numKeys + NUM_THREADS - 1) / NUM_THREADS;
	kernel_insert<<<blocks, NUM_THREADS>>>(device_keys, device_values, numKeys,
					       this->size, this->a, this->b,
					       this->table, this->num_elements);
	cout << "InsertBatch " << "Num keys: " << numKeys << endl;
	this->printTable();
	cout << "\n\n";

	cudaFree(device_keys);
	cudaFree(device_values);
	free(num_ele);
	return true;
}


/* GET BATCH
 */
int* GpuHashTable::getBatch(int* keys, int numKeys) {
	int *device_keys, *device_values, *values;

	cudaMalloc((void**)&device_keys, numKeys * sizeof(int));
	cudaMalloc((void**)&device_values, numKeys * sizeof(int));
	values = (int *)malloc(numKeys * sizeof(int));
	cudaMemcpy(device_keys, keys, numKeys * sizeof(int),
		   cudaMemcpyHostToDevice);

	/* Calculate proper block number and launch get kernel */
	int blocks = (numKeys + NUM_THREADS - 1) / NUM_THREADS;
	kernel_get<<<blocks, NUM_THREADS>>>(device_keys, device_values, numKeys,
					    this->table, this->size, this->a,
					    this->b);

	cudaMemcpy(values, device_values, numKeys * sizeof(int),
		   cudaMemcpyDeviceToHost);
	cudaFree(device_keys);
	cudaFree(device_values);
	return values;
}

/* GET LOAD FACTOR
 * num elements / hash total slots elements
 */
float GpuHashTable::loadFactor() {
	int *num_ele;
	num_ele = (int *)malloc(sizeof(int));
	cudaMemcpy(num_ele, this->num_elements, sizeof(int),
		   cudaMemcpyDeviceToHost);

	cout << "Load factor " << "num_ele " << *num_ele << endl;
	float load_fact = *num_ele / (this->size * 1.0f); // no larger than 1.0f = 100%

	cout << "load: " << load_fact << endl;
	cout << "\n\n";
	free(num_ele);

	return load_fact;
}

/*********************************************************/

#define HASH_INIT GpuHashTable GpuHashTable(1);
#define HASH_RESERVE(size) GpuHashTable.reshape(size);

#define HASH_BATCH_INSERT(keys, values, numKeys) GpuHashTable.insertBatch(keys, values, numKeys)
#define HASH_BATCH_GET(keys, numKeys) GpuHashTable.getBatch(keys, numKeys)

#define HASH_LOAD_FACTOR GpuHashTable.loadFactor()

#include "test_map.cpp"
