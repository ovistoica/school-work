/**
 * LabSD 5
 * hashtable.h
 * Purpose: Skeleton code for Hashtable.
 *
 * @authors Razvan Radoi, Alex Selea
 * @changes Ioana Stefan
 */

#ifndef __HASHTABLE__H
#define __HASHTABLE__H
#include <algorithm>
#include <iterator>
#include <list>

#define TRESHOLD 0.75

template <typename Tkey, typename Tvalue> struct elem_info {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
private:
	std::list<struct elem_info<Tkey, Tvalue> > * H; // pointer to buckets
	unsigned int HMAX; // number of buckets
	unsigned int (*hash)(Tkey); // pointer to hash function
	unsigned int size; // number of elements in hashtable

public:
	Hashtable(int hmax, unsigned int (*h)(Tkey)) {
		hash = h;
		HMAX = hmax;
		H = new std::list<struct elem_info<Tkey, Tvalue>> [HMAX];
	}

	~Hashtable() {
		delete [] H;
	}

	void put(Tkey key, Tvalue value) {
		int index = hash(key) % HMAX;
		int flag = 0;
		typename std::list<struct elem_info<Tkey,Tvalue>>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it ){
				if( it->key == key){
					it->value = value;
					flag = 1;
					break;
				}
		}
		if(flag == 0) {
			struct elem_info<Tkey,Tvalue> new_elem;
			new_elem.key = key;
			new_elem.value = value;
			H[index].push_back(new_elem);
			++size;
 		}
		if(size + 1 == HMAX){
			resize();
		}
 	}

	void remove(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list<struct elem_info<Tkey,Tvalue>>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
				if(it->key == key){
					break;
				}
		}
		if(it != H[index].end()){
			H[index].erase(it);
			--size;
		}
	}

	Tvalue get(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list<struct elem_info<Tkey,Tvalue>>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->key == key){
				return it->value;
			}
		}
		return NULL;
	}

	bool has_key(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list<struct elem_info<Tkey,Tvalue>>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it){
			if(it->key == key)
				return true;
			}
		return false;
	}

	void resize() {

		std::list<struct elem_info<Tkey,Tvalue>> *newH;
		newH = new std::list<struct elem_info<Tkey,Tvalue>> [HMAX * 2];

		for(int bucket = 0; bucket < HMAX; ++bucket){
			for(struct elem_info<Tkey,Tvalue> elem : H[bucket]){
				int index = hash(elem.key) % (HMAX * 2);
				newH[index].push_back(elem);
			}
		}

		delete [] H;
		H = newH;
		HMAX *= 2;
	}

	int get_size() {
		return size;
	}

	int get_capacity() {
		return HMAX;
	}

	float current_factor(){
		return (float)(size) / (float)(HMAX);
	}
};

#endif //__HASHTABLE__
