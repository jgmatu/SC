#include "Solucion.hpp"

Solucion::Solucion(Instancia* inst) {
      instancia = inst;
      length = inst->size();
      route = std::vector<int>(length);

      for (int i = 1 ; i < length; i++) {
            route[i] = -1;
      }
      eval_ = 0;
}

Solucion::~Solucion() {
      route.clear();
}

Solucion*
Solucion::copy()
{
      Solucion* copy = new Solucion(instancia);

      for (unsigned int i = 0; i < this->route.size(); ++i) {
            copy->route[i] = this->route[i];
      }
      return copy;
}

void
Solucion::add(int idNode, int idx) {
      route[idx] = idNode;
}

void
Solucion::remove(int idx) {
      route[idx] = -1;
}

bool
Solucion::exist(int idNode) {
      for (int i = 0; i < length; i++) {
            if (route[i] == idNode) {
                  return true;
            }
      }
      return false;
}

double
Solucion::eval() {
      double total = 0;

      for (int i = 0; i < length; i++) {
            int first = i % length;
            int second = (i + 1) % length;
            double distance = instancia->get_distance(route[first], route[second]);;

            total += distance;
      }
      this->eval_ = total;
      return total;
}

bool
Solucion::is_out_range(int idx) {
      return idx <= 0 || idx >= length;
}

double
Solucion::getDistanceNeighboors(int id) {
      int first = id - 1;
      if (id == 0) {
            first = length - 1;
      }
      int second = (id + 1) % length;
      return instancia->get_distance(route[first], route[id]) + instancia->get_distance(route[second], route[id]);
}

void
Solucion::swap(int idA, int idB) {
      if (is_out_range(idA) || is_out_range(idB)) {
            return;
      }
      double auxEval = this->eval_;
      auxEval = auxEval - getDistanceNeighboors(idA) - getDistanceNeighboors(idB);

      int aux;
      aux = route[idA];
      route[idA] = route[idB];
      route[idB] = aux;

      auxEval = auxEval + getDistanceNeighboors(idA) + getDistanceNeighboors(idB);
      this->eval_ = auxEval;
}

void
Solucion::insert(int idxPosition, int idxInsert) {
      if (is_out_range(idxPosition) || is_out_range(idxInsert)) {
            return;
      }
      std::vector<int>::iterator it = route.begin();
      int aux = route[idxPosition];

      route.erase(it + idxPosition);
      route.insert(it + idxInsert, aux);
      this->eval_ = this->eval();
}


double
Solucion::diverse_distance(Solucion* sol) {
      double total = 0;

      for (int i = 0; i < sol->size(); i++) {
            if (sol->route[i] != this->route[i]) {
                  total = total + 1.0f;
            }
      }
      return total;
}

std::vector<bool>
Solucion::init_used(unsigned int size) const {
      std::vector<bool> init(size);

      for (unsigned int i = 0; i < size; i++) {
            init[i] = false;
      }
      return init;
}

std::vector<int>
Solucion::get_indexes(int size) const {
      std::vector<int> indexes(size);

      for (unsigned int i = 0; i < indexes.size(); i++) {
            indexes[i] = i;
      }
      return indexes;
}

int
Solucion::get_node_not_used(std::vector<bool> used) const {
      std::vector<int> indexes = get_indexes((int) used.size());

      std::random_shuffle(indexes.begin(), indexes.end());
      for (unsigned int i = 0; i < used.size(); i++) {
            if (!used[indexes[i]]) {
                  return indexes[i];
            }
      }
      return -1; // Not possible value...
}

Solucion*
Solucion::vote(Solucion* sol) const {
      Solucion* voted = new Solucion(instancia);
      std::vector<bool> used = init_used(voted->size());

      for (int i = 0; i < length; i++) {
            int coin = std::rand() % COIN_FACES;

            if (coin == FACE)  {
                  if (!voted->exist(this->route[i])) {
                        voted->route[i] = this->route[i];
                        used[this->route[i]] = true;
                  } else if (!voted->exist(sol->route[i])) {
                        voted->route[i] = sol->route[i];
                        used[sol->route[i]] = true;
                  } else {
                        int idNode = get_node_not_used(used);
                        voted->route[i] = idNode;
                        used[idNode] = true;
                  }
            } else {
                  if (!voted->exist(sol->route[i])) {
                        voted->route[i] = sol->route[i];
                        used[sol->route[i]] = true;
                  } else if (!voted->exist(this->route[i])) {
                        voted->route[i] = this->route[i];
                        used[this->route[i]] = true;
                  } else {
                        int idNode = get_node_not_used(used);
                        voted->route[i] = idNode;
                        used[idNode] = true;
                  }
            }
      }
      voted->eval();
      return voted;
}

std::ostream& operator<<(std::ostream& os, const Solucion& sol) {
      os.precision(5);
      os << sol.getActualEval();
      for (int i = 0; i < sol.length; i++) {
            os << sol.route[i] << ' ';
      }
      return os;
}
