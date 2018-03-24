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
            for (int i = 0; i < solucion->size() / 10 && !improve; ++i) {
                  std::random_shuffle(indexesJ.begin(), indexesJ.end());
                  for (int j = i + 1; j < solucion->size() / 10 && !improve; ++j) {
                        double eval = solucion->eval();
                        int a = indexesI[i];
                        int b = indexesJ[j];

                        solucion->swap(a, b);
                        if (solucion->eval() > eval || fabs(solucion->eval() - eval) < 0.001) {
                              solucion->swap(b, a);
                        } else {
                              improve = true;
                        }
                  }
            }
      } while (improve);
      std::cout << "End local Search : " << solucion->eval() << '\n';
}
