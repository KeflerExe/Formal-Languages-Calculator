// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: alfabetos.h
// Contiene la clase Alfabetos encargada de crear objetos tipo alfabeto y de proporcionar métodos para los mismos.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>

#include "simbolo.h"

#ifndef ALFABETOS_H
#define ALFABETOS_H

// Clase Alfabetos, encargada de crear y manejar los objetos tipo Cadenas
template<class T>
class Alfabetos {  
 public:
  // Constructores
  Alfabetos() : alfabetos_{} {}  
  Alfabetos(const T& alfabetos) : alfabetos_{alfabetos} {}

  // Métodos de operación para modificar el atributo alfabetos_ u obtener información de el
  void push_front(const T& simbolo);
  void push_back(const T&);
  void Borrar();
  int TamanioVector() const;

  //Sobrecarga de operadores
  std::string operator[](int posicion) const;
  bool operator<(const Alfabetos& alfabeto) const {
    return alfabetos_ < alfabeto.alfabetos_;
  }
 private:
  std::vector<T> alfabetos_;
};

// Método encargado de introducir datos en el vector alfabetos_ en la parte frontal de este
template<class T>
void Alfabetos<T>::push_front(const T& simbolo) {
  alfabetos_.insert(alfabetos_.begin(), simbolo);
}

// Método encargado de introducir datos en el vector alfabetos_ en la parte trasera de este
template<class T>
void Alfabetos<T>::push_back(const T& estructura_a_introducir) {
  alfabetos_.push_back(estructura_a_introducir);
}

// Método encargado de dejar el vector alfabetos_ vacío
template<class T>
void Alfabetos<T>::Borrar() {
  alfabetos_.clear();
}

// Método encargado de obtener el tamaño del vector alfabetos
template<class T>
int Alfabetos<T>::TamanioVector() const {
  return alfabetos_.size();
}

// Sobrecarga del operador [] con el fin de poder acceder al vector alfabetos_ en una posición concreta
template<class T>
std::string Alfabetos<T>::operator[](int posicion) const{
  return alfabetos_.at(posicion);
}

// Sobrecarga del operador + con el fin de poder concatenar alfabetos 
template<class T>
Alfabetos<std::string> operator+(const Alfabetos<T> alfabeto1, const Alfabetos<T> alfabeto2) {
  Alfabetos<std::string> alfabeto_concatenado = alfabeto1;
  for (int iterador = 0; iterador < alfabeto2.TamanioVector(); ++iterador) {
    alfabeto_concatenado.push_back(alfabeto2[iterador]);
  }
  return alfabeto_concatenado;
}

// Sobrecarga del operador << para imprimir el alfabeto por pantalla 
template<class T>
std::ostream& operator<<(std::ostream& salida, const Alfabetos<T>& alfabetos) {
  for (int iterador = 0; iterador < alfabetos.TamanioVector(); ++iterador) {
    salida << alfabetos[iterador] << " ";
  }
	return salida; 
}

int CompruebaElNumeroDeSimbolosEnCadena(const Cadenas<std::string> cadena, const Alfabetos<std::string> alfabeto);
bool CompruebaSiEstaEnAlfabeto(const Alfabetos<std::string>& alfabeto, const Simbolo& simbolo);

#endif