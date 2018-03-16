#include "Solucion.hpp"

Solucion::Solucion(Instancia* inst) {
      instancia = inst;
      length = inst->size();
      route = std::vector<int>(length);

      for (int i = 1 ; i < length; i++) {
            route[i] = -1;
      }
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

float
Solucion::eval() {
      float total = 0;

      for (int i = 0; i < length; i++) {
            int first = i % length;
            int second = (i + 1) % length;

            total += instancia->get_distance(route[first], route[second]);
      }
      return total;
}

bool
Solucion::is_out_range(int idx) {
      return idx <= 0 || idx >= length;
}

void
Solucion::swap(int idA, int idB) {
      if (is_out_range(idA) || is_out_range(idB)) {
            return;
      }

      int aux;
      aux = route[idA];
      route[idA] = route[idB];
      route[idB] = aux;
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
}

int
Solucion::getNextMin(int idx) {
      float dist = instancia->get_distance(idx, (idx + 1) % length);
      int aux = idx;

      for (int i = 1; i < length; i++) {
            float nextDist = instancia->get_distance(aux, (aux + 1) % length);

            if (nextDist < dist) {
                  return aux;
            }
            aux = (idx + i) % length;
      }
      return -1; // No deberia entrar nunca....
}


float
Solucion::diverse_distance(Solucion* sol) {
      float total = 0;

      for (int i = 0; i < sol->size(); i++) {
            if (sol->route[i] != this->route[i]) {
                  total = total + 1.0f;
            }
      }
      return total;
}


bool mypredicate (int i, int j) {
      return i == j;
}

//bool
//equals(Solucion* sol) {
//      return std::equal(this->route.begin(), this->route.end(), sol->route, mypredicate);
//}


std::vector<bool>
Solucion::init_used(unsigned int size) const {
      std::vector<bool> init(size);

      for (unsigned int i = 0; i < size; i++) {
            init[i] = false;
      }
      return init;
}

int
get_node_not_used(std::vector<bool> used) {
      for (unsigned int i = 0; i < used.size(); i++) {
            if (!used[i]) {
                  return i;
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
      return voted;
}

void
Solucion::print_route() const
{
      for (int i = 0; i < length; i++) {
            std::cout << route[i] << ' ';
      }
      std::cout << std::endl;
}
