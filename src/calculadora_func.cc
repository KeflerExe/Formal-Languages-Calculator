// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: calculadora_func.cc
// Contiene las diferentes funciones que son llamadas desde el main encargadas de realizar ciertas funciones como extraer datos, comprobar que cadena y alfabeto coincidan etc...

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

// Función encargada de comprobar que ambos ficheros de entrada contienen la misma cantidad de lenguajes.
void CompruebaNumeroDeLineas(const std::string nombre_archivo_origen1, const std::string nombre_archivo_origen2) {
  std::string string_auxiliar;
  std::ifstream archivo_origen1;
  std::ifstream archivo_origen2;
  int numero_lineas_archivo1 = 0;
  int numero_lineas_archivo2 = 0;
  archivo_origen1.open(nombre_archivo_origen1);
  while (getline(archivo_origen1, string_auxiliar)) {
    ++numero_lineas_archivo1;
  }
  archivo_origen1.close();
  archivo_origen2.open(nombre_archivo_origen2);
  while (getline(archivo_origen2, string_auxiliar)) {
    ++numero_lineas_archivo2;
  }
  archivo_origen2.close();
  if (numero_lineas_archivo1 != numero_lineas_archivo2) {
    std::cout << "Fallo crítico: ambos ficheros no contienen la misma cantidad de lenguajes." << std::endl;
    exit(EXIT_FAILURE);
  }
}

/*
 * La función ComprobacionCadenaYAlfabeto es la encargada de comprobar que no hay ningún símbolo en la cadena que no se encuentre en el alfabeto y 
 * de que no se repitan 2 símbolos en el alfabeto. En caso de que alguno de los dos casos se cumpla saltará un mensaje de error indicándolo y se detendrá el programa.
 */
void ComprobacionCadenaYAlfabeto(const Alfabetos<std::string>& alfabeto, const Cadenas<std::string>& cadena) {
  for (int iterador = 0; iterador < cadena.LongitudDeCadena(); ++iterador) {
    bool mismo_simbolo_encontrado = false;
    for (int iterador2 = 0; iterador2 < alfabeto.TamanioVector(); ++iterador2) {
      if(cadena[iterador] == alfabeto[iterador2]) {
        mismo_simbolo_encontrado = true;
        break;
      }
    }
    if(mismo_simbolo_encontrado == false) {
      std::cout << "Fallo crítico: la cadena \"" << cadena << "\" contiene caracteres no incluidos en el alfabeto \"" << alfabeto << "\"" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  for (int iterador = 0; iterador < alfabeto.TamanioVector(); ++iterador) {
    bool mismo_simbolo_encontrado = false;
    for (int iterador2 = 0; iterador2 < alfabeto.TamanioVector(); ++iterador2) {
      if(iterador != iterador2 && alfabeto[iterador] == alfabeto[iterador2]) {
        mismo_simbolo_encontrado = true;
        break;
      }
    }
    if(mismo_simbolo_encontrado == true) {
      std::cout << "Fallo crítico: el alfabeto \"" << alfabeto << "\" contiene caracteres repetidos" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

// Esta función calcula cuantos simbolos del total de simbolos del alfabeto se encuentran en la cadena.
int CompruebaElNumeroDeSimbolosEnCadena(const Cadenas<std::string> cadena, const Alfabetos<std::string> alfabeto) {
  int numero_de_simbolos_totales{0};
  for (int iterador1 = 0; iterador1 < alfabeto.TamanioVector(); ++iterador1) {
    for (int iterador2 = 0; iterador2 < cadena.LongitudDeCadena(); ++iterador2) {
      if (alfabeto[iterador1] == cadena[iterador2]) {
        numero_de_simbolos_totales += 1;
        break;
      }
    }
  }
  return numero_de_simbolos_totales;
}

// Esta función recibe un alfabeto y un simbolo y comprueba si dicho simbolo está en el alfabeto indicado.
bool CompruebaSiEstaEnAlfabeto(const Alfabetos<std::string>& alfabeto, const Simbolo& simbolo) {
  for (int iterador = 0; iterador < alfabeto.TamanioVector(); ++iterador) {
    if (alfabeto[iterador] == simbolo.get_simbolo()) {
      return true;
    }
  }
  return false;
}

/* 
 * Esta función recibe la línea extraída del fichero y su objetivo es extraer de dicha línea la cadena, alfabeto y símbolos encontrados en ella para formar un lenguaje que se 
 * introducirá al vector conjunto_lenguajes para poder ser usados en las operaciones.
 */
void LectorDeDatos(const std::string linea_extraida, const std::string nombre_archivo_origen, std::vector<Lenguaje>& conjunto_lenguajes) {
  Alfabetos<std::string> alfabeto;
  Simbolo simbolo;
  Cadenas<std::string> cadena;
  Lenguaje lenguajes;
  char simbolo_extraido;
  int posicion_inicial_lenguaje{0};
  posicion_inicial_lenguaje = linea_extraida.find_first_of("{") + 1;
  while (posicion_inicial_lenguaje < linea_extraida.size()) {
    if (linea_extraida[posicion_inicial_lenguaje] != ' ' && linea_extraida[posicion_inicial_lenguaje] != ',' && linea_extraida[posicion_inicial_lenguaje] != '}') {
      simbolo_extraido = linea_extraida[posicion_inicial_lenguaje];
      if (simbolo_extraido == '{') {
        std::cout << "Fallo crítico: las cadenas de un lenguaje no pueden contener el símbolo \"{\"." << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string simbolo_extraido_string(1, simbolo_extraido);
      simbolo.set_simbolo(simbolo_extraido_string);
      if (simbolo_extraido != '&') {
        if (CompruebaSiEstaEnAlfabeto(alfabeto, simbolo) == false) {
          alfabeto.push_back(simbolo.get_simbolo());
        }
      }
      cadena.push_back(simbolo.get_simbolo());
      simbolo.Borrar(); 
    } 
    if (linea_extraida[posicion_inicial_lenguaje] == ',' || linea_extraida[posicion_inicial_lenguaje] == '}') {
      lenguajes.InsertarCadenas(cadena);
      cadena.Borrar();
    }
    ++posicion_inicial_lenguaje;
  }
  lenguajes.InsertarAlfabeto(alfabeto);
  conjunto_lenguajes.push_back(lenguajes);
  lenguajes.Borrar();
}

/*
 * Comprueba que los argumentos introducidos por línea de comandos sean los 
 * correctos, además de proporcionar ayuda en caso de que el usuario no sepa como se han de introducir los argumentos.
 */
void Usage(int argc, char *argv[]) {
  if (argc != 2) {
    std::string parametro_introducido = argv[1];
    if (parametro_introducido == "--help") {
      std::cout << "--Cadenas" << std::endl;
      std::cout << "Modo de uso: ./calculadora_main fichero_entrada1" << std::endl;
      std::cout << "fichero_entrada1: Fichero de texto de origen donde se encuentran los diferentes lenguajes" << std::endl;
      exit(EXIT_SUCCESS);
    } else {
      std::cout << "--Cadenas " << std::endl;
      std::cout << "Modo de uso: ./calculadora_main fichero_entrada1" << std::endl << "Pruebe ./calculadora_main --help para más información" << std::endl;
      exit(EXIT_FAILURE);
    }
  }   
}