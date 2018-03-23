#include "Voraz.hpp"

Voraz::Voraz(int init) {
      initialNode = init;
}

Voraz::~Voraz() {
      ;
}

int
Voraz::get_min_node(std::map<int, double> node_distances) {
      double min = FLT_MAX;
      int idNode = -1;

      for (std::map<int, double>::const_iterator it = node_distances.begin(); it != node_distances.end(); ++it) {
            if (it->second < min) {
                  min = it->second;
                  idNode = it->first;
            }
      }
      return idNode;
}

void
Voraz::delete_node(std::map<int, double>& node_distances, int idNode) {
      std::map<int, double>::iterator it = node_distances.find(idNode);

      if (it != node_distances.end()) {
            node_distances.erase(it);
      }
}

/**
 * Instancia es la matriz de distancias... que en java son float[][]
 * para acceder a una columna de la matriz.
 * Si matriz es float[][] matriz
 * Columna deberá ser float[] node_distances = matriz[idNode];
 *
 * node distances deberás ir eliminando los valores que ya hayan salido.
 * pon un valor muy alto para que no lo coja el algoritmo get_min_node
 * con MAX_FLT por ejemplo.
 *
 * Si sigues el pseudo código deberías sacar la ruta al siguiente nodo con
 * el valor de distancia más pequeño que no haya salido.
 */
Solucion*
Voraz::construction(Instancia* inst) {
      Solucion* solucion = new Solucion(inst);

      solucion->add(initialNode, 0);
      for (int i = 1; i < inst->size(); i++) {
            int idNode = initialNode; // Node Added like first, because we have to jump from this
                                      // node...
            std::map<int, double> node_distances = inst->get_column(idNode);
            while (solucion->exist(idNode)) {
                  idNode = get_min_node(node_distances); // Obtención de la ruta más corta...
                  if (solucion->exist(idNode)) { // Comprobar si existe el nodo en la ruta.
                        delete_node(node_distances, idNode); // Borrar el nodo, ya está en la ruta.
                  }
            }
            solucion->add(idNode, i); // Añadir en la siguiente ruta de soluciones el nodo seleccionado.
      }
      return solucion;
}
