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

private:

      const int NUM_INITIAL = 100;
      const int NUM_REFSET = 10;
      const int NUM_BEST = 5;
      const int NUM_DIVERSE = 5;

      std::vector<Solucion*> get_initial_solutions(Instancia* inst);
      Instancia* instancia;

      void set_best_solutions(std::vector<Solucion*>& initials, std::vector<Solucion*>& refSet);
      void set_diverses_solutions(std::vector<Solucion*>& initial, std::vector<Solucion*>& refSet);
      float get_distance(Solucion* initial, Solucion* best);
      Solucion* get_vote(Solucion* sol1, Solucion* sol2);
      void change_refset(std::vector<Solucion*>& refSet, Solucion* solution);


};

#endif
