#include "Scatter.hpp"


Scatter::Scatter() :
      refSet_(NUM_REFSET)
{
      ;
}


Scatter::~Scatter() {
      ;
}

Solucion*
Scatter::construction(Instancia* inst) {
      std::vector<Solucion*> initials = get_initial_solutions(inst);
      this->refSet_ = initials;
      ExperimentSearch* search = new ExperimentSearch();
      int numChanged = -1;

      set_best_solutions(initials);
      set_diverses_solutions(initials);

      do {
            numChanged = 0;
            for (unsigned int i = 0; i < this->refSet_.size(); ++i) {
                  for (unsigned int j = 0; j < this->refSet_.size(); ++j) {
                        if (this->refSet_[i] == this->refSet_[j]) {
                              continue;
                        }
                        Solucion* voted = this->refSet_[i]->vote(this->refSet_[j]);
                        search->search(voted);
                        bool changed = change_refset(voted);
                        if (changed) {
                              std::cout << *this << '\n';
                              numChanged++;
                        }
                  }
            }
      } while (numChanged > 0);
      delete search;
      return this->refSet_[0];
}

bool solution_sort_criteria(Solucion* sol1, Solucion* sol2) {
      return sol1->getActualEval() < sol2->getActualEval(); 
}

std::vector<Solucion*>
Scatter::get_initial_solutions(Instancia* instance) {
      std::vector<Solucion*> solutions(NUM_INITIAL);
      Random* random = new Random();

      for (int i = 0; i < NUM_INITIAL; ++i) {
            solutions[i] = random->construction(instance);
            solutions[i]->eval();
      }
      std::sort(solutions.begin(), solutions.end(), solution_sort_criteria);

      delete random;
      return solutions;
}

void
Scatter::set_best_solutions(std::vector<Solucion*>& initials) {
      if (NUM_INITIAL < NUM_BEST) {
            return;
      }
      std::vector<Solucion*>::const_iterator first = initials.begin();
      std::vector<Solucion*>::const_iterator last = initials.begin() + NUM_BEST;

      this->refSet_ = std::vector<Solucion*>(first, last);
      initials.erase(first, last);
}

void
Scatter::set_diverses_solutions(std::vector<Solucion*>& initials) {
      for (int i = 0; i < NUM_DIVERSE; ++i) {
            double max = FLT_MIN;
            int idx = -1;

            for (unsigned int j = 0; j < initials.size(); ++j) {
                  double min = FLT_MAX;

                  for (unsigned int k = 0; k < this->refSet_.size(); ++k) {
                        double distance = initials[j]->diverse_distance(this->refSet_[k]);

                        if (distance < min) {
                              min = distance;
                        }
                  }
                  if (min > max) {
                        idx = j;
                        max = min;
                  }
            }

            if (idx != -1) {
                  this->refSet_.insert(this->refSet_.end(), initials[idx]);
                  initials.erase(initials.begin() + idx);
            }
      }
}

bool
Scatter::change_refset(Solucion* solution) {
      double mean = this->avg();
      double eval = solution->getActualEval();

      if (solution->getActualEval() > mean) {
            return false;
      }

      for (unsigned int i = 0; i < this->refSet_.size(); i++) {
            if (this->refSet_[i]->getActualEval() > mean && eval < this->refSet_[i]->getActualEval()) {
                  // Cambio en el refset si y solo sí el que estoy examinando tiene un
                  // valor mayor que la media y la evaluación de la solución actual
                  // es menor que la que estoy examinando...
                  delete this->refSet_[i];
                  this->refSet_[i] = solution;
                  std::sort(this->refSet_.begin(), this->refSet_.end(), solution_sort_criteria);
                  return true;
            }
      }
      return false;
}

double
Scatter::avg() {
      double total = 0;

      for (unsigned int i = 0; i < this->refSet_.size(); ++i) {
            total += this->refSet_[i]->getActualEval();
      }
      return total / this->refSet_.size();
}


std::ostream& operator<<(std::ostream& os, const Scatter& scatter) {
      os << "Refset state evals : " << std::endl;
      for (int i = 0; i < scatter.NUM_REFSET; ++i) {
            os << scatter.refSet_[i]->getActualEval() << ' ';
      }
      os << std::endl;
      return os;
}
