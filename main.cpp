#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <math.h>
#include <random>

#include "Instancia.hpp"
#include "Solucion.hpp"
#include "Scatter.hpp"

Instancia* loadInstance(std::string filename) {
      Instancia* instancia = new Instancia();

      instancia->readFile(filename);
      instancia->calc_distances();
      instancia->print_distances();
      return instancia;
}


// Recorrerse el directorio de ficheros tsp.
int main () {
      Instancia* instancia = loadInstance("graphs/example.tsp");
      Scatter* scatter = new Scatter();
      Solucion* solucion = scatter->construction(instancia);


      std::cout << "Total Distance : " << solucion->eval() << std::endl;
      solucion->print_route();
      solucion->insert(4, 1);
      solucion->insert(3, 4);
      solucion->insert(4, 1);
      solucion->insert(0, 2);
      solucion->insert(1, 5);
      solucion->insert(5, 1);
      solucion->insert(0, 3);
      solucion->insert(3, 0);
      solucion->insert(1, 4);

      solucion->swap(1, 2),
      solucion->print_route();

      delete solucion;
      delete instancia;
      delete scatter;
}

// Clase instancia.

// La clase instancia con método read file que recibe el nombre del fichero.
// Guarda los valores en memoria. Guardar una matriz de distancias e nxn por cada ciudad.

// No guardar las coordenadas. Distancias geométricas, la memoria es gratis pero el tiempo no.

// Guardar la distancia de matrices completa. Guardar en la instancia la matriz de distancias. Mapa de ciudad distancias.

// La clase instancia va a ser única que se pasa por referencia a todas las instancias que se utilicen.


// Clase solución.

// Tiene todo lo necesario para realizar una solución.
// int[] Camino de solución.
// longitud Suma total de distancias.


// Métodos de modificación de la ruta.

      // add ( ruta )
      // remove ()
      // update ()
      // eval() // Calcular la longitud de la ruta.

// Cuando implementamos búsuqedas locales 1.. 40, 41 ... 100.000  Si intercambio dos posiciones optimizar
// la solución de manera rápida... Sumar la distancia a la única añadida pensar las modificaciones y evaluaciones
// de la ruta para optimizarla.

// La base...

// Cada solución tiene una referencia a la instancia para la cual es solución...



// Constructivos, búsquedas locales y perturbaciones.


// Constructivos es una interfaz que recibe una instancia y devuelve una solución.
// Con la interfaz para realizar Open Closed... solo modifico en la interfaz cual Constructivo
// utilizo :).


// Grafo demo de 10 para calcular las distancias y ver que la matriz de distancias la estamos generando bien.
// Crear la clase slución que genera una solución al azar de la instancia dada...