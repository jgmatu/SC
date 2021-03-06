#include "Random.hpp"

Random::Random() {
      ;
}

Random::~Random() {
      ;
}

Solucion* Random::construction(Instancia* instance) {
      Solucion* solucion = new Solucion(instance);
      std::vector<int> indexes = get_indexes(instance->size());

      std::random_shuffle(indexes.begin(), indexes.end());
      for (unsigned int i = 0; i < indexes.size(); i++) {
            solucion->add(i, indexes[i]);
      }
      return solucion;
}

std::vector<int>
Random::get_indexes(int size) {
      std::vector<int> indexes(size);

      for (unsigned int i = 0; i < indexes.size(); i++) {
            indexes[i] = i;
      }
      return indexes;
}
