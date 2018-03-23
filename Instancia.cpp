#include "Instancia.hpp"

Instancia::Instancia() {
      ;
}

Instancia::~Instancia() {
      for (std::map<int, std::map<int, double>>::iterator it = distances.begin(); it != distances.end(); it++) {
            it->second.clear();
      }
      distances.clear();

      for (std::vector<std::vector<double>>::iterator it = graph.begin(); it != graph.end(); it++) {
            it->clear();
      }
      graph.clear();
}

void
Instancia::readFile(std::string filename) {
      std::ifstream ifs;
      std::string line;
      int numline = 0;

      ifs.open (filename, std::ifstream::in);
      while (std::getline(ifs, line)) {
            if (numline >= METADATA && is_valid_vertex(line)) {
                  graph.push_back(get_vertex(line));
            }
            numline++;
      }
      ifs.close();
}

bool
Instancia::is_valid_vertex(const std::string& line) {
      return line.compare("EOF") != 0 && line.compare("") != 0;
}

std::vector<double>
Instancia::get_vertex(const std::string& line) {
      std::istringstream iss(line);
      std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

      std::vector<double> values;
      for (std::vector<std::string>::const_iterator it = results.begin(); it != results.end(); it++) {
            values.push_back(std::stof(*it));
      }
      return values;
}

void
Instancia::calc_distances() {
      int n = 0;

      for (std::vector<std::vector<double>>::const_iterator it = graph.begin(); it != graph.end(); it++, n++) {
            std::map<int, double> distances_node;
            int m = 0;

            for (std::vector<std::vector<double>>::const_iterator itJ = graph.begin(); itJ != graph.end(); itJ++, m++) {
                  if (it != itJ) {
                        distances_node[m] = sqrt(pow((*itJ)[1] - (*it)[1], 2) + pow((*itJ)[2] - (*it)[2], 2));
                  }
            }
            distances[n] = distances_node;
      }
}

void
Instancia::print_distances() {
      for (std::map<int, std::map<int, double>>::const_iterator it = distances.begin(); it != distances.end(); it++) {
            std::cout <<  "Node : " << it->first << std::endl;
            for (std::map<int, double>::const_iterator itJ = it->second.begin(); itJ != it->second.end(); itJ++) {
                  std::cout << "\t" << itJ->first << " :" << itJ->second << std::endl;
            }
      }
}

void
Instancia::print_graph() {
      for (std::vector<std::vector<double>>::const_iterator itI = graph.begin(); itI != graph.end(); itI++) {
            for (std::vector<double>::const_iterator itJ = itI->begin(); itJ != itI->end(); itJ++) {
                  std::cout << *itJ << " ";
            }
            std::cout << std::endl;
      }
}


double
Instancia::get_distance(int first, int second) {
      return distances[first][second];
}

std::map<int, double>
Instancia::get_column(int idNode) {
      return distances[idNode];
}

std::ostream& operator<<(std::ostream& os, const Instancia& inst) {
      return os << inst.name;
}
