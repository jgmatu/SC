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
Scatter::get_initial_solutions(Instancia* instance) {
      std::vector<Solucion*> solutions(NUM_INITIAL);
      Random* random = new Random();

      for (int i = 0; i < NUM_INITIAL; ++i) {
            solutions[i] = random->construction(instance);
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

void
Scatter::set_diverses_solutions(std::vector<Solucion*>& initial, std::vector<Solucion*>& refSet) {
      for (unsigned int i = 0; i < NUM_DIVERSE; ++i) {
            float max = FLT_MIN;
            int idx = -1;

            for (unsigned int j = 0; j < initial.size(); ++j) {
                  float min = FLT_MAX;

                  for (unsigned int k = 0; k < refSet.size(); ++k) {
                        float distance = initial[j]->diverse_distance(refSet[k]);

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


void
Scatter::change_refset(std::vector<Solucion*>& refSet, Solucion* solution) {
      float eval = solution->eval();
      float min = FLT_MAX;
      int idx = -1;

      for (unsigned int i = 0; i < refSet.size(); i++) {
            float dist = fabs(refSet[i]->eval() - eval);
            if (dist < min) {
                  min = dist;
                  idx = i;
            }
      }
      if (idx != -1) {
            delete refSet[idx];
            refSet[idx] = solution;
      }
}

Solucion*
Scatter::construction(Instancia* inst) {
      std::vector<Solucion*> initials = get_initial_solutions(inst);
      std::vector<Solucion*> refSet;

      set_best_solutions(initials, refSet);
      set_diverses_solutions(initials, refSet);

      ExperimentSearch* search = new ExperimentSearch();
      for (unsigned int i = 0; i < refSet.size(); ++i) {
            for (unsigned int j = 0; j < refSet.size(); ++j) {
//                  if (refSet[i])
                  Solucion* voted = refSet[i]->vote(refSet[j]);
//                  search->search(voted);
//                  change_refset(refSet, voted);
                  delete voted;
            }
      }
      if (NUM_INITIAL == 0) {
            return new Solucion(inst);
      }
      return initials[0];
}
