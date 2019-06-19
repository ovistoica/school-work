#ifndef _HASHCPU_
#define _HASHCPU_

using namespace std;

#define	KEY_INVALID		0

#define DIE(assertion, call_description) \
	do {	\
		if (assertion) {	\
			fprintf(stderr, "(%s, %d): ",	\
				__FILE__, __LINE__);	\
			perror(call_description);	\
			exit(errno);	\
		}	\
	} while (0)

typedef unsigned long long Entry;

//
// GPU HashTable
//
class GpuHashTable
{
public:
	unsigned long size;
	unsigned int *num_elements;
	Entry *table;

	/* Operands in the hash function */
	unsigned long a;
	unsigned long b;

	GpuHashTable(int size);
	void reshape(int sizeReshape);

	bool insertBatch(int *keys, int* values, int numKeys);
	int* getBatch(int* key, int numItems);

	float loadFactor();
	void occupancy();
	void print(string info);
	void printTable();

	~GpuHashTable();
};

#endif

