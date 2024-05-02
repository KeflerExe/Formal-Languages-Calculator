// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: lenguaje.h
// Contiene la clase Lenguaje encargada de crear objetos tipo lenguaje y de proporcionar métodos para los mismos.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>

#include "cadenas.h"
#include "alfabetos.h"

#ifndef LENGUAJE_H
#define LENGUAJE_H

// Clase Lenguajes, encargada de crear y manejar los objetos tipo Lenguajes
class Lenguaje {  
 public:
  // Constructores
  Lenguaje() : cadenas_{}, alfabeto_{}  {}  
  
  // Métodos para modificar u obtener información del atributo cadenas_ o alfabeto_ 
  void InsertarCadenas(const Cadenas<std::string>& cadena);
  void InsertarAlfabeto(const Alfabetos<std::string>& alfabeto);
  int TamanioContenedorCadenas() const;
  int TamanioContenedorAlfabeto() const;
  bool CompruebaSiNoTieneCadenas() const;
  void Borrar();
  std::set<Cadenas<std::string>>::iterator InicioContenedorCadenas() const;
  std::set<Alfabetos<std::string>>::iterator InicioContenedorAlfabeto() const;

  // Métodos de operación correspondientes a las 6 operaciones disponibles con lenguajes.
  Lenguaje ConcatenaLenguajes(const Lenguaje& lenguaje2) const;
  Lenguaje UnionLenguajes(const Lenguaje& lenguaje2) const;
  Lenguaje InterseccionLenguajes(const Lenguaje& lenguaje2) const;
  Lenguaje DiferenciaLenguajes(const Lenguaje& lenguaje2) const;
  Lenguaje LenguajeInverso() const;
  Lenguaje PotenciaDeLenguaje(const int numero_potencias) const;

  // Sobrecarga de operadores
  bool operator<(const Lenguaje& lenguaje) const {
    return cadenas_ < lenguaje.cadenas_;
  }
  friend std::ofstream& operator<<(std::ofstream& salida, const Lenguaje& lenguaje);
  friend std::ostream& operator<<(std::ostream& salida, const Lenguaje& lenguaje); 
 private:
  std::set<Cadenas<std::string>> cadenas_;
  std::set<Alfabetos<std::string>> alfabeto_;
};

Lenguaje operator|(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2);
Lenguaje operator+(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2);
Lenguaje operator^(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2);
Lenguaje operator-(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2);
Lenguaje operator*(const Lenguaje& lenguaje1, const int numero_potencias);
Lenguaje operator!(const Lenguaje& lenguaje1);

void LectorDeDatos(const std::string linea_extraida, const std::string nombre_archivo_origen, std::vector<Lenguaje>& conjunto_lenguajes);

#endif