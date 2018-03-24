#ifndef SCATTER_H
#define SCATTER_H

#include "Constructivas.hpp"
#include "Voraz.hpp"
#include "LocalSearch.hpp"
#include "ExperimentSearch.hpp"
#include "Random.hpp"
#include <algorithm>
#include <random>
#include <float.h>


class Scatter : public Constructivas {

public:
      Scatter();
      ~Scatter();

      Solucion* construction(Instancia* i);
      friend std::ostream& operator<<(std::ostream& os, const Scatter& scatter);

private:

      const int NUM_INITIAL = 10;
      const int NUM_REFSET = 10;
      const int NUM_BEST = 5;
      const int NUM_DIVERSE = 5;

      std::vector<Solucion*> refSet_;

      std::vector<Solucion*> get_initial_solutions(Instancia* inst);
      void set_best_solutions(std::vector<Solucion*>& initials);
      void set_diverses_solutions(std::vector<Solucion*>& initial);
      double get_distance(Solucion* initial, Solucion* best);
      Solucion* get_vote(Solucion* sol1, Solucion* sol2);
      bool change_refset(Solucion* solution);
      float avg();

};

#endif
