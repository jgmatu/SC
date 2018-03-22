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
ExperimentSearch::search(Solucion* solucion) {
      std::vector<int> indexesI = get_indexes(solucion->size());
      std::vector<int> indexesJ = get_indexes(solucion->size());
      bool improve;

      do {
            improve = false;
            std::random_shuffle(indexesI.begin(), indexesI.end());
            for (int i = 0; i < solucion->size() / 2 && !improve; ++i) {
                  std::random_shuffle(indexesJ.begin(), indexesJ.end());
                  for (int j = i + 1; j < solucion->size() / 2 && !improve; ++j) {
                        float eval = solucion->eval();

                        solucion->swap(indexesI[i], indexesJ[j]);
                        if (solucion->eval() >= eval) {
                              solucion->swap(indexesJ[j], indexesI[i]);
                        } else {
                              improve = true;
                        }
                  }
            }
      } while (improve);
      // std::cout << solucion->eval() << '\n';
}
