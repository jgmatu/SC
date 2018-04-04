#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <random>
#include <ctime>

#include <math.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "Instancia.hpp"
#include "Solucion.hpp"
#include "Scatter.hpp"

#define MAX_PATH 255

// Directorio con todos los ficheros tsp con formato EUC_2D
// si alguno de los ficheros no tiene formato EUC_2D el Resultado
// es inesperado...
const char* DIRNAME = "./graphs/EUC_2D/";


/**
 * función que coprueba si el fichero es un fichero regular es decir un fichero
 * de texto que pueda ser abierto para lectura de datos.
 */
int
isregfile(char *file)
{
	struct stat sb;

	if (stat(file , &sb) < 0) {
		fprintf(stderr, "Error stat file... %s error... %s\n" , file , strerror(errno));
            exit(1);
	}
	switch (sb.st_mode & S_IFMT) {
	case S_IFREG:
		return 1;
	default:
		return 0;
	}
}

void set_path(char* path, char* filename)
{
	sprintf(path, "%s", DIRNAME);
	strcat(path, filename);
}

// Recorrerse el directorio de
// ficheros tsp con los diferentes problemas.
// de resolución metaheurística...
int main() {
      std::srand ( unsigned ( std::time(0) ) ); // Intialize pseudo random sequence...
      Scatter* scatter = new Scatter();

      DIR* dir = opendir(DIRNAME);
      if (dir == NULL) {
            std::cout << "Error open dir : " << strerror(errno) << '\n';
            return 1;
      }

      struct dirent* _dirent;
      while ((_dirent = readdir(dir)) != NULL) {
            if (strcmp(_dirent->d_name, ".") == 0 && strcmp(_dirent->d_name, "..") == 0) {
                  // Father and this are not considered....
                  continue;
            }
            char path[MAX_PATH];
		set_path(path, _dirent->d_name);
            if (!isregfile(path)) {
			// Recursives directoryies
			// are not considered...
                  continue;
            }

		Instancia *instancia = new Instancia();
            instancia->readFile(path);
            instancia->calc_distances();

            time_t before = time(0);
            Solucion* solucion = scatter->construction(instancia);
            time_t after = time(0);

            std::cout << _dirent->d_name << ',';
		std::cout << after - before << ',';
		std::cout << *solucion << '\n';

		delete instancia;
            delete solucion;
      }
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
