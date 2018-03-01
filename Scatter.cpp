#include "Scatter.hpp"


Scatter::Scatter() {
      ;
}

Scatter::~Scatter() {
      ;
}

std::vector<Solucion*>
Scatter::get_initial_solutions(Instancia* inst) {
      std::vector<Solucion*> solutions(NUM_INITIAL);
      Random* random = new Random();

      for (int i = 0 ; i < NUM_INITIAL; i++) {
            solutions[i] = random->construction(inst);
      }
      delete random;
      return solutions;
}

Solucion*
Scatter::construction(Instancia* inst) {
      std::vector<Solucion*> initial_solutions = get_initial_solutions(inst);
      // LocalSearch* search = new ExperimentSearch();

      // search->search(initial_solutions[0]);
      for (int i = 0 ; i < NUM_INITIAL; i++) {
            initial_solutions[i]->print_route();
      }
      return initial_solutions[0];
}
