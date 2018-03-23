#ifndef VORAZ_H
#define VORAZ_H

#include "Constructivas.hpp"
#include <algorithm>  //for random_shuffle http://cplusplus.com/reference/algorithm/random_shuffle/
#include <float.h>


class Voraz : public Constructivas {

public:

      Voraz(int init);
      ~Voraz();
      Solucion* construction(Instancia*);

private:

      int get_min_node(std::map<int, double> node_distances);
      int get_last_node(Solucion* solucion);
      void delete_node(std::map<int, double>& node_distances, int idNode);

      int initialNode;
};

#endif
