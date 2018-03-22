#ifndef SOLUCION_H
#define SOLUCION_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <math.h>
#include <random>
#include <algorithm>  // for random_shuffle http://cplusplus.com/reference/algorithm/random_shuffle/
#include "Instancia.hpp"

class Solucion {

public:

      Solucion(Instancia* instancia);
      ~Solucion();

      void add(int idNode, int idx);
      void remove(int idx);
      float eval() const;
      bool exist(int idNode);
      void insert(int idNode, int idx);
      void swap(int idNodeA, int idNodeB);
      int size() { return route.size(); };
      int getNextMin(int idx);
      Solucion* vote(Solucion* sol) const;
      float diverse_distance(Solucion* sol);
      Solucion* copy();


      friend std::ostream& operator<<(std::ostream& os, const Solucion& sol);

private:

      int get_node_not_used(std::vector<bool> used) const;
      std::vector<bool> init_used(unsigned int size) const;
      std::vector<int> get_indexes(int size) const;
      bool is_out_range(int idx);


      Instancia* instancia;
      std::vector<int> route;
      int length;

      const int COIN_FACES = 2;
      const int FACE = 1;
      const int CROSS = 0;

};
#endif
