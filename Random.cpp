#include "Random.hpp"

Random::Random() {
      ;
}

Random::~Random() {
}

int
get_random(int i) {
      std::random_device rd;  //Will be used to obtain a seed for the random number engine
      std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
      std::uniform_int_distribution<> dis(1, 100);

      return dis(gen);
}

Solucion* Random::construction(Instancia* inst) {
      Solucion* solucion = new Solucion(inst);
      std::vector<int> indexes = get_indexes(inst->size());

      std::srand(time(0));
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
