#include "Scatter.hpp"


Scatter::Scatter() {
      ;
}

Scatter::~Scatter() {
      ;
}

std::vector<Solucion*>
Scatter::get_initial_solutions(Instancia* inst) {
      std::vector<Solucion*> solutions(inst->size());

      for (int i = 0 ; i < inst->size(); i++) {
            Voraz voraz = Voraz(i);
            solutions[i] = voraz.construction(inst);
      }
      return solutions;
}

Solucion*
Scatter::construction(Instancia* inst) {
      std::vector<Solucion*> mejores_soluciones; // Ordenados por distancias.
      std::vector<Solucion*> peores_soluciones; // Ordenados por distancias.
      std::vector<Solucion*> initial_solutions = get_initial_solutions(inst);
      Solucion* final_solution = initial_solutions[0];

      return final_solution;
}
