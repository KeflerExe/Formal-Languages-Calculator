// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: calculadora.h
// Contiene la clase Calculadora encargada de crear objetos tipo lenguaje y de proporcionar métodos para los mismos.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>
#include <cctype>

#include "lenguaje.h"

#ifndef CALCULADORA_H
#define CALCULADORA_H

// Clase Calculadora, encargada de crear y manejar los objetos tipo Calculadora
class Calculadora {  
 public:
  // Constructores
  Calculadora() : pila_{} {}  

  // Métodos para evaluar y calcular las diferentes operaciones 
  void EvaluaLasOperaciones(const std::string& linea_extraida_archivo, const std::vector<Lenguaje>& conjunto_lenguajes);
  void OperaLosLenguajes(const char caracter_extraido, const int numero_potencias);

  // Método Pop para sacar un objeto de la pila.
  void Pop();

  // Sobrecarga de operadores
  friend std::ostream& operator<<(std::ostream& salida, const Calculadora& calculadora);
 private:
  std::stack<Lenguaje> pila_;
};

#endif