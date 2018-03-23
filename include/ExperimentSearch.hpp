#ifndef EXPSEARCH_H
#define EXPSEARCH_H

#include "LocalSearch.hpp"
#include "Solucion.hpp"
#include <stdlib.h>     /* srand, rand */
#include <float.h>
#include <algorithm>  // for random_shuffle http://cplusplus.com/reference/algorithm/random_shuffle/


class ExperimentSearch : public LocalSearch {

public:

      ExperimentSearch();
      ~ExperimentSearch();
      void search(Solucion* solucion);

private:

      const int MAX_ITERATES = 1000;
      std::vector<int> get_indexes(int size);
};

#endif
