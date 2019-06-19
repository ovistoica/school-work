#include <unordered_map>
#include <iostream>

int main() {
  std::unordered_map<int, int> occ;
  occ[1] = 3;
  std::cout << occ[1] << " " ;
  occ[1] = occ[1] + 1;
  std::cout << occ[1] << " " ;
  // TODO cout occ[2] fara sa asignez nimic acolo
  occ[2]++;
  occ[2]++;
  std::cout << occ[2];
  return 0;
}
