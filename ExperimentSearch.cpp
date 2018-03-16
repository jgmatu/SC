#include "ExperimentSearch.hpp"

ExperimentSearch::ExperimentSearch() {
      ;
}

ExperimentSearch::~ExperimentSearch() {
      ;
}


std::vector<int>
ExperimentSearch::get_indexes(int size) {
      std::vector<int> indexes(size);

      for (unsigned int i = 0; i < indexes.size(); i++) {
            indexes[i] = i;
      }
      return indexes;
}



void
ExperimentSearch::search(Solucion** result) {
      bool improve;
      Solucion* solucion = *result;
      std::vector<int> indexesI = get_indexes(solucion->size());
      std::vector<int> indexesJ = get_indexes(solucion->size());

      do {
            improve = false;
            std::random_shuffle(indexesI.begin(), indexesI.end());
            for (int i = 0; i < solucion->size(); ++i) {
                  std::random_shuffle(indexesJ.begin(), indexesJ.end());
                  for (int j = i + 1; j < solucion->size(); ++j) {
                        Solucion* aux = solucion->copy();
                        aux->swap(indexesI[i], indexesJ[j]);

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
