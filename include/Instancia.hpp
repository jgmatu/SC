#ifndef INSTANCIA_H
#define INSTANCIA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <math.h>

class Instancia {

public:

      Instancia();
      ~Instancia();

      void readFile(std::string filename);
      void print_graph();
      void calc_distances();
      void print_distances();
      int size() { return distances.size(); };

      double get_distance(int first, int second);
      std::map<int, double> get_column(int idNode);

      friend std::ostream& operator<<(std::ostream& os, const Instancia& inst);

private:

      const int METADATA = 6;

      std::string name;
      std::map<int, std::map<int, double>> distances;
      std::vector<std::vector<double>> graph;

      std::vector<double> get_vertex(const std::string& line);
      bool is_valid_vertex(const std::string& line);

};

#endif
