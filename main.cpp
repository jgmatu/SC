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

// Recorrerse el directorio de ficheros tsp.
int main() {
//       std::srand ( unsigned ( std::time(0) ) ); // Intialize pseudo random sequence...
      std::srand ( 13 ); // Intialize pseudo random sequence...

      Instancia* instancia = new Instancia();
      instancia->readFile("graphs/pr152.tsp");
      instancia->calc_distances();

      Scatter* scatter = new Scatter();
      Solucion* solucion = scatter->construction(instancia);

      std::cout << "Eval route : " << solucion->eval() << '\n';
      solucion->print_route();

      delete solucion;
      delete instancia;
      delete scatter;
      return 0;
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


// Resultado final :
//      F. O.     Time : Toda la iteración de la metaurística.

//    tsp1  .....
//    tsp2  .....
//    tsp3  .....
