#ifndef CONSTRUCTIVAS_H
#define CONSTRUCTIVAS_H

#include "Instancia.hpp"
#include "Solucion.hpp"

class Constructivas {

public:
      
      virtual ~Constructivas() {
            ;
      }

      virtual Solucion* construction(Instancia* i) = 0;

};
#endif
