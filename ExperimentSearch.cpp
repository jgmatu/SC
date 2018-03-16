#include "ExperimentSearch.hpp"

ExperimentSearch::ExperimentSearch() {
      ;
}

ExperimentSearch::~ExperimentSearch() {
      ;
}


void
ExperimentSearch::search(Solucion** result) {
      bool improve;
      Solucion* solucion = *result;

      do {
            improve = false;
            for (int i = 0; i < solucion->size(); ++i) {
                  for (int j = i + 1; j < solucion->size(); ++j) {
                        Solucion* aux = solucion->copy();
                        aux->swap(i, j);

                        if (aux->eval() < solucion->eval()) {
                              delete solucion;
                              solucion = aux;
                              *result = solucion;
                              improve = true;
                        } else {
                              delete aux;
                        }
                        aux = NULL;
                  }
            }
      } while (improve);
}

/*
void
ExperimentSearch::search(Solucion* solucion) {
      std::vector<Solucion*> solutions(10);

      for (;;) {
            float min = FLT_MAX;
            int idx = -1;

            for (unsigned int i = 0; i < solutions.size(); ++i) {
                  int random = std::rand() % solucion->size();
                  int change = solucion->getNextMin(random);

                  solutions[i] = solucion->copy();
                  solutions[i]->swap(random, change);

                  float eval = solutions[i]->eval();
                  if (eval < min) {
                        min = eval;
                        idx = i;
                  }
            }

            if (solutions[idx]->eval() < solucion->eval()) {
                  delete solucion;
                  solucion = solutions[idx];
            } else {
                  break;
            }
      }
}
*/
