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

void
Solucion::print_route()
{
      for (int i = 0; i < length; i++) {
            std::cout << route[i] << ' ';
      }
      std::cout << std::endl;
}
