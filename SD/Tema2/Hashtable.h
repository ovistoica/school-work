#include <string>
#include <list>
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

template <typename Tkey, typename Tvalue>
struct elem {
  Tkey key;
  Tvalue value;
};

template <typename Tkey, typename Tvalue>
class Hashtable {
  std::list<struct elem<Tkey, Tvalue> > * H; // pointer to buckets
  unsigned int HMAX; // number of buckets
  unsigned int size; // number
	unsigned int (*hash)(Tkey); // pointer to hash function
public:

	Hashtable(unsigned int hmax, unsigned int (*h)(Tkey)) {
		HMAX = hmax;
		hash = h;
		H = new std::list<struct elem<Tkey, Tvalue> > [HMAX];
    size = 0;
	}

	~Hashtable() {
    delete [] H;
	}

  // Insert an element in the hashtable
	void put(Tkey key, Tvalue value) {
		int index = hash(key) % HMAX;
		int flag = 0;
		typename std::list<struct elem<Tkey,Tvalue>>::iterator it;
		for(it = H[index].begin(); it != H[index].end(); ++it ){
				if( it->key == key){
					it->value = value;
					flag = 1;
					break;
				}
		}
		if(flag == 0) {
			struct elem<Tkey,Tvalue> new_elem;
			new_elem.key = key;
			new_elem.value = value;
			H[index].push_back(new_elem);
			++size;
 		}
		if(size + 1 == HMAX){
			resize();
		}
 	}

  // Remove an element from the hashtable
	void remove(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list<struct elem< Tkey,Tvalue > >::iterator it;
		for (it = H[index].begin(); it != H[index].end(); ++it){
				if (it->key == key){
					break;
				}
		}
    // If the element exists in the list, delete it
		if (it != H[index].end()){
			H[index].erase(it);
			--size;
		}
	}

  // Get the value of the elemet with Key key
	Tvalue get(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list< struct elem< Tkey,Tvalue> >::iterator it;
		for (it = H[index].begin(); it != H[index].end(); ++it){
			if (it->key == key){
				return it->value;
			}
		}
		return Tvalue();
	}

  // Checks if Key key exists in the Hashtable
	bool has_key(Tkey key) {
		int index = hash(key) % HMAX;
		typename std::list< struct elem<Tkey,Tvalue> >::iterator it;
		for (it = H[index].begin(); it != H[index].end(); ++it){
			if (it->key == key)
				return true;
			}
		return false;
	}


  // The hash function used for selecting the bucket
  // Doesn't work for string
  unsigned int hash_function(Tkey key){
    const char *data = reinterpret_cast<char*>(&key);
    size_t length = std::char_traits<char>::length(data);
    unsigned int hsh = 0;
    for(size_t i = 0; i < length; ++i)
    {
      hsh += data[i];
      hsh += (hsh << 10);
      hsh ^= (hsh >> 6);
    }
    hsh += (hsh << 3);
    hsh ^= (hsh >> 11);
    hsh += (hsh << 15);
    return hsh;
}

  // Double the size of the hashtable
	void resize() {

		std::list<struct elem<Tkey,Tvalue> > *newH;
		newH = new std::list< struct elem<Tkey,Tvalue> > [HMAX * 2];

		for (unsigned int bucket = 0; bucket < HMAX; ++bucket){
			for (struct elem<Tkey,Tvalue> elem : H[bucket]){
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

#endif //HASHTABLE_H_
