// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: calculadora.cc
// Contiene la implementación de la clase Calculadora encargada de crear objetos tipo lenguaje y de proporcionar métodos para los mismos.

#include "calculadora.h"

/*
 * Método encargado de extraer y almacenar en la pila los diferentes lenguajes y operaciones de la linea 
 * extraida del archivo para después llamar a otro método encargado de realizar las operaciones.
 */ 
void Calculadora::EvaluaLasOperaciones(const std::string& linea_extraida_archivo, const std::vector<Lenguaje>& conjunto_lenguajes) {
  char caracter_extraido;
  int numero_potencias{0};
  for (int iterador = 0; iterador < linea_extraida_archivo.size(); ++iterador) {
    if (isdigit(linea_extraida_archivo[iterador + 1]) && linea_extraida_archivo[iterador + 2] != '*') {
      caracter_extraido = linea_extraida_archivo[iterador + 1];
      int numero_lenguaje = caracter_extraido - 48;
      pila_.push(conjunto_lenguajes[numero_lenguaje - 1]);
      iterador += 2;
    } else {
      caracter_extraido = linea_extraida_archivo[iterador];
      if (caracter_extraido == '*') {
        char numero_potencias_char = linea_extraida_archivo[iterador - 2];
        numero_potencias = numero_potencias_char - 48;
      }
      OperaLosLenguajes(caracter_extraido, numero_potencias);
    }
  }
}

// Método encargado de realizar los diferentes pops de la pila y de realizar las operaciones necesarias con los lenguajes extraidos.
void Calculadora::OperaLosLenguajes(const char caracter_extraido, const int numero_potencias) {
  Lenguaje lenguaje_resultado;
  Lenguaje lenguaje1;
  Lenguaje lenguaje2;
  switch (caracter_extraido) {
    case '+': {
      lenguaje2 = pila_.top();
      pila_.pop();
      lenguaje1 = pila_.top();
      pila_.pop();
      lenguaje_resultado = lenguaje1 + lenguaje2;
      pila_.push(lenguaje_resultado);
      break;
    }
    case '|': {
      lenguaje2 = pila_.top();
      pila_.pop();
      lenguaje1 = pila_.top();
      pila_.pop(); 
      lenguaje_resultado = lenguaje1 | lenguaje2;
      pila_.push(lenguaje_resultado);
      break;
    }
    case '^': {
      lenguaje2 = pila_.top();
      pila_.pop();
      lenguaje1 = pila_.top();
      pila_.pop(); 
      lenguaje_resultado = lenguaje1 ^ lenguaje2;
      pila_.push(lenguaje_resultado);
      break;
    }
    case '-': {
      lenguaje2 = pila_.top();
      pila_.pop();
      lenguaje1 = pila_.top();
      pila_.pop(); 
      lenguaje_resultado = lenguaje1 - lenguaje2;
      pila_.push(lenguaje_resultado);
      break;
    }
    case '*': {
      lenguaje1 = pila_.top();
      pila_.pop(); 
      lenguaje_resultado = lenguaje1 * numero_potencias;
      pila_.push(lenguaje_resultado);
      break;
    }
    case '!': {
      lenguaje1 = pila_.top();
      pila_.pop(); 
      lenguaje_resultado = !lenguaje1;
      pila_.push(lenguaje_resultado);
      break;
    }
    default: {
      break;
    }
  }
  lenguaje1.Borrar();
  lenguaje2.Borrar();
}

// Método pop para sacar un elemento de la pila
void Calculadora::Pop() {
  pila_.pop();
}

// Sobrecarga del operador de salida para imprimir el elemento situado en el top de la pila
std::ostream& operator<<(std::ostream& salida, const Calculadora& calculadora) {
  Lenguaje lenguaje_extraido = calculadora.pila_.top();
  salida << lenguaje_extraido;
  return salida;
}