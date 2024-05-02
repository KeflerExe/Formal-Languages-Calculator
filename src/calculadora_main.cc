// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: calculadora_main.cc
// Contiene la función main del proyecto que usa la clase Calculadora y llama a otras funciones
// para realizar las diferentes operaciones requeridas por el usuario.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>

#include "cadenas.h"
#include "alfabetos.h"
#include "lenguaje.h"
#include "calculadora.h"

// Función main: encargada de crear los objetos de las clases y de llamar al resto de funciones y métodos necesarios para el funcionamiento del programa.
int main(int argc, char *argv[]) {
  Usage(argc, argv);
  Calculadora pila_rpn;
  std::string nombre_archivo_origen = argv[1];
  std::vector<Lenguaje> conjunto_lenguajes;
  std::ifstream archivo_origen;
  std::string linea_extraida_archivo;
  archivo_origen.open(nombre_archivo_origen);
  while (true) { 
    getline(archivo_origen, linea_extraida_archivo);
    if (linea_extraida_archivo.find('=') == -1) {
      break;
    }
    LectorDeDatos(linea_extraida_archivo, nombre_archivo_origen, conjunto_lenguajes);
  }
  while (true) { 
    pila_rpn.EvaluaLasOperaciones(linea_extraida_archivo, conjunto_lenguajes);
    std::cout << pila_rpn << std::endl;
    pila_rpn.Pop();
    if (archivo_origen.eof()) {
      break;
    }
    getline(archivo_origen, linea_extraida_archivo);
  }
  archivo_origen.close();
}