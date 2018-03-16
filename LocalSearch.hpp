
#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "Solucion.hpp"

class LocalSearch {

public:

      virtual ~LocalSearch() {
            ;
      }
      virtual void search(Solucion** s) = 0;

};
#endif
