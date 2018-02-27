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

      float get_distance(int first, int second);

      std::map<int, float> get_column(int idNode);
            
private:

      const int METADATA = 6;

      std::string name;
      std::map<int, std::map<int, float>> distances;
      std::vector<std::vector<float>> graph;

      std::vector<float> get_vertex(const std::string& line);
      bool is_valid_vertex(const std::string& line);
};

#endif
