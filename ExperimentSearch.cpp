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
      std::random_shuffle(indexes.begin(), indexes.end());
      return indexes;
}

void
ExperimentSearch::search(Solucion* solucion) {
      std::vector<int> indexesI = get_indexes(solucion->size());
      std::vector<int> indexesJ = get_indexes(solucion->size());
      bool improve = false;

      int size = solucion->size() / 10;

      do {
            improve = false;
            for (int i = 0; i < size && !improve; ++i) {
                  for (int j = i + 1; j < size && !improve; ++j) {
                        double eval = solucion->getActualEval();
                        int a = indexesI[i];
                        int b = indexesJ[j];

                        // Se puede actualizar de otra manera?, Es un único
                        // cambio...
                        solucion->swap(a, b);
                        double newEval = solucion->getActualEval();

                        if (newEval > eval || fabs(newEval - eval) < 0.001) {
                              solucion->swap(b, a);
                        } else {
                              improve = true;
                        }
                  }
            }
      } while (improve);
      std::cout << "End local Search : " << solucion->getActualEval() << '\n';
}


// 259269 277832 278395 278407 283227 285521 287415 293494 294294 295191
