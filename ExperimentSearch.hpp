#ifndef EXPSEARCH_H
#define EXPSEARCH_H

#include "LocalSearch.hpp"
#include "Solucion.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <float.h>

class ExperimentSearch : public LocalSearch {

public:

      ExperimentSearch();
      ~ExperimentSearch();
      void search(Solucion** solucion);

private:

      const int MAX_ITERATES = 1000;

      std::vector<int> get_indexes(int size);
};

#endif
