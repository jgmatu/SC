#ifndef SCATTER_H
#define SCATTER_H

#include "Constructivas.hpp"
#include "Voraz.hpp"
#include "LocalSearch.hpp"
#include "ExperimentSearch.hpp"
#include "Random.hpp"

class Scatter : public Constructivas {

public:
      Scatter();
      ~Scatter();

      Solucion* construction(Instancia* i);

private:

      const int NUM_INITIAL = 100;

      std::vector<Solucion*> get_initial_solutions(Instancia* inst);


};

#endif
