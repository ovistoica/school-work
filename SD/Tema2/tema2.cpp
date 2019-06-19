#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Graph.h"
#include "Hashtable.h"

unsigned int uintHash(unsigned int key){
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

unsigned int stringHash(std::string key){
  const char *data = key.c_str();
  size_t length = key.length();
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

int main() {
  // Reading data from file
  unsigned int N, M;

  std::cin >> N >> M;

  Graph town_graph(N); //The Graph used for the homework

  // The table for getting the names of towns
  Hashtable<uint32_t, std::string> name_table(N * N, &uintHash);
  // The table for getting the index of the town
  Hashtable<std::string, uint32_t> index_table(N * N, &stringHash);

  // Adding the cities to tables
  for (uint32_t i = 1; i <= N; i++){
    std::string town;
    std::cin >> town;
    name_table.put(i,town);
    index_table.put(town, i);
  }

  // Adding the routes between towns
  for(uint32_t i = 0; i < M; i++){
    std::string t1, t2;
    std::cin >> t1 >> t2;
    int src = index_table.get(t1);
    int dst   = index_table.get(t2);
    town_graph.addEdge(src, dst);
  }

  //TODO: Sort this out
  // Reading task 4 thingies
  int gas_stations_no;
  std::cin >> gas_stations_no;
  std::vector<std::string> gas_cities;
  for(int i = 0; i < gas_stations_no; i++){
    std::string gas;
    std::cin >> gas;
    gas_cities.push_back(gas);
  }



  // Getting the node with the maximum degree
  std::pair<uint32_t, uint32_t> max_deg = town_graph.maxInDegrees();

  // Writing results to task1 file
  std::ofstream task1;
  task1.open("task1.out");
  task1 << name_table.get(max_deg.first) << " " << max_deg.second << std::endl;
  task1.close();


  // Task 2
  std::vector<std::vector<unsigned int> > connexes = town_graph.connex_comp();
  // If there is only 1 connex component, means that the map is valid
  std::ofstream task2;
  task2.open("task2.out");
  if(connexes.size() == 1){
    task2 << "HARTA VALIDA" << std::endl;
  } else {
    task2 << "HARTA INVALIDA" << std::endl;
  }
  task2.close();

  // Task 3
  std::ofstream task3;
  task3.open("task3.out");
  if(connexes.size() == 1){
    task3 << "Exista drum intre oricare doua orase" << std::endl;
  } else {
    int cities;
    std::cin >> cities;
    // Printing unavailable citties for each given citty
    while(cities){
      std::string citty;
      std::cin >> citty;
      uint32_t node = index_table.get(citty);
      unsigned int pos = connexes.size() + 1;

      //Finding the connex component of the citty
      for(auto it = connexes.begin(); it != connexes.end(); ++it){
        for(auto itt = it->begin(); itt != it->end(); ++itt){
          if(node == *itt){
            //The connex component of the city
            pos = it - connexes.begin();
            break;
          }
        }
        if(pos > connexes.size()){
          break;
        }
      }
      // Put all unavailable cities in a vector for sorting
      std::vector<std::string> unav_cities;
      for(unsigned int i = 0;i < connexes.size(); i++){
        if(i == pos) continue;
        for(auto it = connexes[i].begin(); it != connexes[i].end(); ++it){
          unav_cities.push_back(name_table.get(*it));
        }
      }

      std::sort(unav_cities.begin(), unav_cities.end());
      //Printing unavailable cities
      task3 << "Orase inaccesibile pentru " << citty << ": ";
      for (auto it = unav_cities.begin(); it != unav_cities.end(); ++it){
          task3 << *it << " ";
      }
      task3 << std::endl;
      --cities;
    }
  }
  task3.close();
  return 0;

}
