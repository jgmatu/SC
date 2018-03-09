#include "ExperimentSearch.hpp"

ExperimentSearch::ExperimentSearch() {
      ;
}

ExperimentSearch::~ExperimentSearch() {
      ;
}

void
ExperimentSearch::search(Solucion* solucion) {
      float initEval = solucion->eval();
      float localEval = initEval;
      int numIterates = 0;

      while (initEval <= localEval && numIterates < MAX_ITERATES) {
            int initial = std::rand() % solucion->size();
            int change = solucion->getNextMin(initial);

            solucion->swap(initial, change);
            localEval = solucion->eval();
            if (initEval < localEval) {
                  solucion->swap(change, initial);
            }
            numIterates++;
      }
}
