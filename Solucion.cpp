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
      return -1;
}


float
Solucion::diverse_distance(Solucion* sol) {
      float total = 0;

      for (unsigned int i = 0; i < sol->size(); i++) {
            total += fabs(sol->route[i] - this->route[i]);
      }
      return total;
}

std::vector<int>
Solucion::init_count() const {
      std::vector<int> init(length);

      for (int i = 0; i < length; ++i) {
            init[i] = 0;
      }
      return init;
}

unsigned int
Solucion::get_node_not_used(std::vector<int> count) const {
      for (unsigned int i = 0; i < length; i++) {
            if (count[i] == NOT_USED) {
                  return i;
            }
      }
      return 0;
}


bool mypredicate (int i, int j) {
  return i == j;
}

//bool
//equals(Solucion* sol) {
//      return std::equal(this->route.begin(), this->route.end(), sol->route, mypredicate);
//}


Solucion*
Solucion::vote(Solucion* sol) const {
      Solucion* voted = new Solucion(instancia);
      std::vector<int> count = init_count();

      for (unsigned int i = 0; i < length; i++) {
            int face = std::rand() % COIN_FACES;
            
            if (face == FACE)  {
                  if (!voted->exist(this->route[i])) {
                        voted->route[i] = this->route[i];
                        count[sol->route[i]]++;
                  } else if (!voted->exist(sol->route[i])) {
                        voted->route[i] = sol->route[i];
                        count[this->route[i]]++;
                  } else {
                        int idNode = get_node_not_used(count);
                        voted->route[i] = idNode;
                        count[idNode] = 0;
                  }
            } else {
                  if (!voted->exist(sol->route[i])) {
                        voted->route[i] = sol->route[i];
                        count[this->route[i]]++;
                  } else if (!voted->exist(this->route[i])) {
                        voted->route[i] = this->route[i];
                        count[sol->route[i]]++;
                  } else {
                        int idNode = get_node_not_used(count);
                        voted->route[i] = idNode;
                        count[idNode] = 0;
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
