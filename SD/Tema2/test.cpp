#include "Hashtable.h"
#include <iostream>
#include <string>

  template <typename Tkey>
  unsigned int hash_function(Tkey key){
    /*
    if(typeid(key).name() == typeid(std::string).name()){

    }
    */
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

int main () {
  Hashtable<int, std::string> name_table;
  Hashtable<std::string, int> index_table;
  std::string c = "cinci";
  name_table.put(5, c);
  index_table.put(c, 5);
  const char *data = c.c_str();
  size_t length = std::char_traits<char>::length(data);
  for(size_t i = 0; i < length; i++){
      std::cout << data[i];
  }

  std::cout << length << std::endl;

  return 0;

}
