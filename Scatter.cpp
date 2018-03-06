#include "Scatter.hpp"


Scatter::Scatter() {
      ;
}

Scatter::~Scatter() {
      ;
}

bool solution_sort_criteria (Solucion* sol1, Solucion* sol2) {
      return sol1->eval() < sol2->eval();
}

std::vector<Solucion*>
Scatter::get_initial_solutions(Instancia* inst) {
      std::vector<Solucion*> solutions(NUM_INITIAL);
      Random* random = new Random();

      for (int i = 0; i < NUM_INITIAL; i++) {
            solutions[i] = random->construction(inst);
      }
      std::sort(solutions.begin(), solutions.end(), solution_sort_criteria);

      delete random;
      return solutions;
}

void
Scatter::set_best_solutions(std::vector<Solucion*>& initials, std::vector<Solucion*>& refSet) {
      if (NUM_INITIAL < NUM_BEST) {
            return;
      }
      std::vector<Solucion*>::const_iterator first = initials.begin();
      std::vector<Solucion*>::const_iterator last = initials.begin() + NUM_BEST;

      refSet = std::vector<Solucion*>(first, last);
      initials.erase(first, last);
}

float
Scatter::get_distance(Solucion* initial, Solucion* refset) {
      float total = 0;

      for (unsigned int i = 0; i < initial->size(); i++) {
            total += fabs(initial->getNode(i) - refset->getNode(i));
      }
      return total;
}

void
Scatter::set_diverses_solutions(std::vector<Solucion*>& initial, std::vector<Solucion*>& refSet) {
      for (unsigned int i = 0; i < NUM_DIV; ++i) {
            float max = FLT_MIN;
            int idx = -1;

            for (unsigned int j = 0; j < initial.size(); ++j) {
                  float min = FLT_MAX;

                  for (unsigned int k = 0; k < refSet.size(); ++k) {
                        float distance = get_distance(initial[j], refSet[k]);

                        if (distance < min) {
                              min = distance;
                        }
                  }
                  if (min > max) {
                        idx = j;
                        max = min;
                  }
            }
            if (idx >= 0) {
                  refSet.insert(refSet.end(), initial[idx]);
                  initial.erase(initial.begin() + idx);
            }
      }
}

Solucion*
Scatter::construction(Instancia* inst) {
      std::vector<Solucion*> initials = get_initial_solutions(inst);
      std::vector<Solucion*> refSet;

      set_best_solutions(initials, refSet);
      set_diverses_solutions(initials, refSet);

      // LocalSearch* search = new ExperimentSearch();
      // search->search(initial_solutions[0]);
      
      if (NUM_INITIAL > 0) {
            return initials[0];
      }
      return new Solucion(inst);
}
