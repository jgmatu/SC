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
#include "Instancia.hpp"

class Solucion {

public:

      Solucion(Instancia* instancia);
      ~Solucion();

      void add(int idNode, int idx);
      void remove(int idx);
      float eval();
      bool exist(int idNode);
      void insert(int idNode, int idx);
      void swap(int idNodeA, int idNodeB);
      void print_route();
      bool is_out_range(int idx);
      int size() { return route.size(); };
      int getNextMin(int idx);
      int getNode(int idx) { return route[idx]; };

private:

      Instancia* instancia;
      std::vector<int> route;
      int length;

};
#endif
