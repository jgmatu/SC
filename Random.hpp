#ifndef RANDOM_H
#define RANDOM_H

#include "Constructivas.hpp"
#include <algorithm>  // for random_shuffle http://cplusplus.com/reference/algorithm/random_shuffle/
#include <ctime>      // std::time


class Random : public Constructivas {

public:

      Random();
      ~Random();
      Solucion* construction(Instancia*);

private:
      std::vector<int> get_indexes(int size);
};

#endif
