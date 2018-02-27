#ifndef SCATTER_H
#define SCATTER_H

#include "Constructivas.hpp"
#include "Voraz.hpp"

class Scatter : public Constructivas {

public:
      Scatter();
      ~Scatter();

      Solucion* construction(Instancia* i);

private:

      std::vector<Solucion*> get_initial_solutions(Instancia* inst);

};

#endif
