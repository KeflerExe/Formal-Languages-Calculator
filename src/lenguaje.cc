// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 3: Calculadora de lenguajes
// Autor: Joel Oscar Martín Gutiérrez
// Correo: alu0101473840@ull.es
// Fecha: 17/10/2022
// Archivo: lenguajes.cc
// Contiene la implementación de la clase Lenguaje encargada de crear objetos tipo cadena y de proporcionar métodos para los mismos.

#include "lenguaje.h"

// Método encargada de insertar cadenas en el lenguaje
void Lenguaje::InsertarCadenas(const Cadenas<std::string>& cadena) {
  cadenas_.insert(cadena);
}

// Método encargada de insertar el alfabeto en el lenguaje
void Lenguaje::InsertarAlfabeto(const Alfabetos<std::string>& alfabeto) {
  alfabeto_.insert(alfabeto);
}

// Método encargado de devolver el tamaño del set que contiene las cadenas
int Lenguaje::TamanioContenedorCadenas() const {
  return cadenas_.size(); 
}

// Método encargado de devolver el tamaño del set que contiene el alfabeto
int Lenguaje::TamanioContenedorAlfabeto() const {
  return alfabeto_.size(); 
}

// Método encargado de comprobar si el lenguaje tiene cadenas o no
bool Lenguaje::CompruebaSiNoTieneCadenas() const {
  std::set<Cadenas<std::string>>::iterator posicion_set = cadenas_.begin();
  Cadenas<std::string> cadena_auxiliar = *posicion_set;
  return cadena_auxiliar.CompruebaSiLaCadenaEstaVacia();
}

// Método encargado de retornar un iterador iniciado al principio del set de cadenas
std::set<Cadenas<std::string>>::iterator Lenguaje::InicioContenedorCadenas() const {
  return cadenas_.begin();
}

// Método encargado de retornar un iterador iniciado al principio del set de alfabeto
std::set<Alfabetos<std::string>>::iterator Lenguaje::InicioContenedorAlfabeto() const {
  return alfabeto_.begin();
}

// Sobrecarga del operador + para concatenar lenguajes
Lenguaje operator+(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje lenguaje_concatenado;
  lenguaje_concatenado = lenguaje1.ConcatenaLenguajes(lenguaje2);
  return lenguaje_concatenado;
}

// Sobrecarga del operador | para unir lenguajes
Lenguaje operator|(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje lenguaje_unido;
  lenguaje_unido = lenguaje1.UnionLenguajes(lenguaje2);
  return lenguaje_unido;
}

// Sobrecarga del operador ^ para intersectar lenguajes
Lenguaje operator^(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje lenguaje_interseccion;
  lenguaje_interseccion = lenguaje1.InterseccionLenguajes(lenguaje2);
  return lenguaje_interseccion;
}

// Sobrecarga del operador - para hacer la diferencia entre lenguajes
Lenguaje operator-(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje lenguaje_interseccion;
  lenguaje_interseccion = lenguaje1.DiferenciaLenguajes(lenguaje2);
  return lenguaje_interseccion;
}

// Sobrecarga del operador * para obtener la potencia de un lenguaje
Lenguaje operator*(const Lenguaje& lenguaje1, const int numero_potencias) {
  Lenguaje lenguaje_potencia;;
  lenguaje_potencia = lenguaje1.PotenciaDeLenguaje(numero_potencias);
  return lenguaje_potencia;
}

// Sobrecarga del operador ! para obtener la inversa de un lenguaje
Lenguaje operator!(const Lenguaje& lenguaje1) {
  Lenguaje lenguaje_inverso;
  lenguaje_inverso = lenguaje1.LenguajeInverso();
  return lenguaje_inverso;;
}

// Sobrecarga del operador * para las potencias de lenguajes
Lenguaje operator*(const Lenguaje& lenguaje1, const Lenguaje& lenguaje2) {
  Lenguaje lenguaje_multiplicado;
  Cadenas<std::string> cadena_a_introducir;
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = lenguaje1.InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < lenguaje1.TamanioContenedorCadenas(); ++iterador1) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;  
    std::set<Cadenas<std::string>>::iterator iterador_set_cadenas2 = lenguaje2.InicioContenedorCadenas();
    for (int iterador2 = 0; iterador2 < lenguaje2.TamanioContenedorCadenas(); ++iterador2) {
      Cadenas<std::string> cadena_extraida_lenguaje2 = *iterador_set_cadenas2;
      if (cadena_extraida_lenguaje1[0] != "&" && cadena_extraida_lenguaje2[0] != "&") {
        cadena_a_introducir = cadena_extraida_lenguaje1 + cadena_extraida_lenguaje2;
        lenguaje_multiplicado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] == "&" && cadena_extraida_lenguaje2[0] != "&") {
        cadena_a_introducir = cadena_extraida_lenguaje2;
        lenguaje_multiplicado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] != "&" && cadena_extraida_lenguaje2[0] == "&") {
        cadena_a_introducir = cadena_extraida_lenguaje1;
        lenguaje_multiplicado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] == "&" && cadena_extraida_lenguaje2[0] == "&") {
        Simbolo simbolo_ampersan;
        simbolo_ampersan.set_simbolo("&");
        cadena_a_introducir.push_back(simbolo_ampersan.get_simbolo());
        lenguaje_multiplicado.InsertarCadenas(cadena_a_introducir);
      }
      std::advance(iterador_set_cadenas2, 1);
    }
    std::advance(iterador_set_cadenas, 1);
  }
  return lenguaje_multiplicado;
}

// Método encargado de obtener la concatenación de dos lenguajes
Lenguaje Lenguaje::ConcatenaLenguajes(const Lenguaje& lenguaje2) const {
  Lenguaje lenguaje_concatenado;
  if (CompruebaSiNoTieneCadenas() == true) {
    lenguaje_concatenado.alfabeto_ = lenguaje2.alfabeto_;
    return lenguaje_concatenado;
  } 
  if (lenguaje2.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_concatenado.alfabeto_ = alfabeto_;
    return lenguaje_concatenado;
  }
  std::set<Cadenas<std::string>>::iterator posicion_set = cadenas_.begin();
  Cadenas<std::string> cadena_auxiliar = *posicion_set;
  if (cadena_auxiliar[0] == "&" && cadenas_.size() == 1) {
    lenguaje_concatenado = lenguaje2;
    return lenguaje_concatenado;
  }
  posicion_set = lenguaje2.InicioContenedorCadenas();
  cadena_auxiliar = *posicion_set;
  if (cadena_auxiliar[0] == "&" && lenguaje2.TamanioContenedorCadenas() == 1) {
    lenguaje_concatenado.cadenas_ = cadenas_;
    lenguaje_concatenado.alfabeto_ = alfabeto_;
    return lenguaje_concatenado;
  }
  Cadenas<std::string> cadena_a_introducir;
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < TamanioContenedorCadenas(); ++iterador1) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;  
    std::set<Cadenas<std::string>>::iterator iterador_set_cadenas2 = lenguaje2.InicioContenedorCadenas();
    for (int iterador2 = 0; iterador2 < lenguaje2.TamanioContenedorCadenas(); ++iterador2) {
      Cadenas<std::string> cadena_extraida_lenguaje2 = *iterador_set_cadenas2;
      if (cadena_extraida_lenguaje1[0] != "&" && cadena_extraida_lenguaje2[0] != "&") {
        cadena_a_introducir = cadena_extraida_lenguaje1 + cadena_extraida_lenguaje2;
        lenguaje_concatenado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] == "&" && cadena_extraida_lenguaje2[0] != "&") {
        cadena_a_introducir = cadena_extraida_lenguaje2;
        lenguaje_concatenado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] != "&" && cadena_extraida_lenguaje2[0] == "&") {
        cadena_a_introducir = cadena_extraida_lenguaje1;
        lenguaje_concatenado.InsertarCadenas(cadena_a_introducir);
      }
      if (cadena_extraida_lenguaje1[0] == "&" && cadena_extraida_lenguaje2[0] == "&") {
        Simbolo simbolo_ampersan;
        simbolo_ampersan.set_simbolo("&");
        cadena_a_introducir.push_back(simbolo_ampersan.get_simbolo());
        lenguaje_concatenado.InsertarCadenas(cadena_a_introducir);
      }
      std::advance(iterador_set_cadenas2, 1);
    }
    std::advance(iterador_set_cadenas, 1);
  }
  Simbolo simbolo_extraido;
  Alfabetos<std::string> alfabeto_concatenacion;
  iterador_set_cadenas = lenguaje_concatenado.InicioContenedorCadenas();
  for (int iterador = 0; iterador < lenguaje_concatenado.TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;
    for (int iterador2 = 0; iterador2 < cadena_extraida_lenguaje1.LongitudDeCadena(); ++iterador2) {
      if (cadena_extraida_lenguaje1[iterador2] != "&") {
        simbolo_extraido.set_simbolo(cadena_extraida_lenguaje1[iterador2]);
        if (CompruebaSiEstaEnAlfabeto(alfabeto_concatenacion, simbolo_extraido) == false) {
          alfabeto_concatenacion.push_back(simbolo_extraido.get_simbolo());
        }
        simbolo_extraido.Borrar();
      }
    }
    std::advance(iterador_set_cadenas, 1);
  }
  lenguaje_concatenado.InsertarAlfabeto(alfabeto_concatenacion);
  if (lenguaje_concatenado.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_concatenado.alfabeto_.clear();
  }
  return lenguaje_concatenado;
}

// Método encargado de obtener la unión de dos lenguajes
Lenguaje Lenguaje::UnionLenguajes(const Lenguaje& lenguaje2) const {
  Lenguaje lenguaje_unido;
  if (CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_unido.cadenas_ = lenguaje2.cadenas_;
    lenguaje_unido.alfabeto_ = lenguaje2.alfabeto_;
    return lenguaje_unido;
  } 
  if (lenguaje2.CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_unido.cadenas_ = cadenas_;
    lenguaje_unido.alfabeto_ = alfabeto_;
    return lenguaje_unido;
  } 
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = InicioContenedorCadenas();
  for (int iterador = 0; iterador < TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje = *iterador_set_cadenas;
    lenguaje_unido.InsertarCadenas(cadena_extraida_lenguaje);
    std::advance(iterador_set_cadenas, 1);
  }
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas2 = lenguaje2.InicioContenedorCadenas();
  for (int iterador = 0; iterador < lenguaje2.TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje2 = *iterador_set_cadenas2;
    lenguaje_unido.InsertarCadenas(cadena_extraida_lenguaje2);
    std::advance(iterador_set_cadenas2, 1);
  }
  Simbolo simbolo_extraido;
  Alfabetos<std::string> alfabeto_union;
  iterador_set_cadenas = lenguaje_unido.InicioContenedorCadenas();
  for (int iterador = 0; iterador < lenguaje_unido.TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;
    for (int iterador2 = 0; iterador2 < cadena_extraida_lenguaje1.LongitudDeCadena(); ++iterador2) {
      if (cadena_extraida_lenguaje1[iterador2] != "&") {
        simbolo_extraido.set_simbolo(cadena_extraida_lenguaje1[iterador2]);
        if (CompruebaSiEstaEnAlfabeto(alfabeto_union, simbolo_extraido) == false) {
          alfabeto_union.push_back(simbolo_extraido.get_simbolo());
        }
        simbolo_extraido.Borrar();
      }
    }
    std::advance(iterador_set_cadenas, 1);
  }
  lenguaje_unido.InsertarAlfabeto(alfabeto_union);
  if (lenguaje_unido.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_unido.alfabeto_.clear();
  }
  return lenguaje_unido;
}

// Método encargado de obtener la intersección de dos lenguajes
Lenguaje Lenguaje::InterseccionLenguajes(const Lenguaje& lenguaje2) const {
  Lenguaje lenguaje_interseccion;
  if (CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_interseccion.alfabeto_ = lenguaje2.alfabeto_;
    return lenguaje_interseccion;
  } 
  if (lenguaje2.CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_interseccion.alfabeto_ = alfabeto_;
    return lenguaje_interseccion;
  } 
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < TamanioContenedorCadenas(); ++iterador1) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;
    std::set<Cadenas<std::string>>::iterator iterador_set_cadenas2 = lenguaje2.InicioContenedorCadenas();
    for (int iterador2 = 0; iterador2 < lenguaje2.TamanioContenedorCadenas(); ++iterador2) {
      Cadenas<std::string> cadena_extraida_lenguaje2 = *iterador_set_cadenas2;
      if (cadena_extraida_lenguaje1 == cadena_extraida_lenguaje2) {
        lenguaje_interseccion.InsertarCadenas(cadena_extraida_lenguaje1);
      }
      std::advance(iterador_set_cadenas2, 1);
    }
    std::advance(iterador_set_cadenas, 1);
  }
  Simbolo simbolo_extraido;
  Alfabetos<std::string> alfabeto_interseccion;
  iterador_set_cadenas = lenguaje_interseccion.InicioContenedorCadenas();
  for (int iterador = 0; iterador < lenguaje_interseccion.TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set_cadenas;
    for (int iterador2 = 0; iterador2 < cadena_extraida_lenguaje1.LongitudDeCadena(); ++iterador2) {
      if (cadena_extraida_lenguaje1[iterador2] != "&") {
        simbolo_extraido.set_simbolo(cadena_extraida_lenguaje1[iterador2]);
        if (CompruebaSiEstaEnAlfabeto(alfabeto_interseccion, simbolo_extraido) == false) {
          alfabeto_interseccion.push_back(simbolo_extraido.get_simbolo());
        }
        simbolo_extraido.Borrar();
      }
    }
    std::advance(iterador_set_cadenas, 1);
  }
  lenguaje_interseccion.InsertarAlfabeto(alfabeto_interseccion);
  if (lenguaje_interseccion.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_interseccion.alfabeto_ = lenguaje2.alfabeto_;
  } 
  return lenguaje_interseccion;
}

// Método encargado de obtener la diferencia de dos lenguajes
Lenguaje Lenguaje::DiferenciaLenguajes(const Lenguaje& lenguaje2) const {
  Lenguaje lenguaje_diferencia;
  if (CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_diferencia.alfabeto_ = alfabeto_;
    return lenguaje_diferencia;
  } 
  if (lenguaje2.CompruebaSiNoTieneCadenas() == true ) {
    lenguaje_diferencia.cadenas_ = cadenas_;
    lenguaje_diferencia.alfabeto_ = alfabeto_;
    return lenguaje_diferencia;
  } 
  std::set<Cadenas<std::string>>::iterator iterador_set = InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < TamanioContenedorCadenas(); ++iterador1) {
    bool misma_cadena_encontrada = false;
    Cadenas<std::string> cadena_extraida_lenguaje1 = *iterador_set;
    std::set<Cadenas<std::string>>::iterator iterador_set2 = lenguaje2.InicioContenedorCadenas();
    for (int iterador2 = 0; iterador2 < lenguaje2.TamanioContenedorCadenas(); ++iterador2) {
      Cadenas<std::string> cadena_extraida_lenguaje2 = *iterador_set2;
      if (cadena_extraida_lenguaje1 == cadena_extraida_lenguaje2) {
        misma_cadena_encontrada = true;
        break;
      }
      std::advance(iterador_set2, 1);
    }
    if (misma_cadena_encontrada == false) {
      lenguaje_diferencia.InsertarCadenas(cadena_extraida_lenguaje1);
    }
    std::advance(iterador_set, 1);
  }
  lenguaje_diferencia.alfabeto_ = alfabeto_;
  if (lenguaje_diferencia.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_diferencia.alfabeto_ = alfabeto_;
  } 
  return lenguaje_diferencia;
}

// Método encargado de obtener la inversa de un lenguaje
Lenguaje Lenguaje::LenguajeInverso() const {
  Lenguaje lenguaje_inverso;
  if (CompruebaSiNoTieneCadenas() == true ) {
    return lenguaje_inverso;
  } 
  std::set<Cadenas<std::string>>::iterator iterador_set = InicioContenedorCadenas();
  for (int iterador = 0; iterador < TamanioContenedorCadenas(); ++iterador) {
    Cadenas<std::string> cadena_extraida_lenguaje = *iterador_set;
    cadena_extraida_lenguaje.InvierteLaCadena();
    lenguaje_inverso.InsertarCadenas(cadena_extraida_lenguaje);
    std::advance(iterador_set, 1);
  }
  lenguaje_inverso.alfabeto_ = alfabeto_;
  return lenguaje_inverso;
}

// Método encargado de obtener la potencia de un lenguaje
Lenguaje Lenguaje::PotenciaDeLenguaje(const int numero_potencias) const {
  Lenguaje lenguaje_potencias;
  Lenguaje lenguaje_auxiliar;
  if (CompruebaSiNoTieneCadenas() == true ) {
    return lenguaje_potencias;
  } 
  if (numero_potencias == 0) {
    std::string ampersan = "&";
    Cadenas<std::string> cadena_vacia;
    cadena_vacia.push_back(ampersan);
    lenguaje_potencias.InsertarCadenas(cadena_vacia);
    lenguaje_potencias.alfabeto_ = alfabeto_;
    return lenguaje_potencias;
  }
  if (numero_potencias == 1) {
    lenguaje_potencias.cadenas_ = cadenas_;
    lenguaje_potencias.alfabeto_ = alfabeto_;
    return lenguaje_potencias;
  }
  lenguaje_auxiliar.cadenas_ = cadenas_;
  lenguaje_potencias.cadenas_ = cadenas_;
  for (int iterador = 1; iterador < numero_potencias; ++iterador) {
    lenguaje_potencias = lenguaje_potencias * lenguaje_auxiliar;
  }
  lenguaje_potencias.alfabeto_ = alfabeto_;
  if (lenguaje_potencias.CompruebaSiNoTieneCadenas() == true) {
    lenguaje_potencias.alfabeto_.clear();
  } 
  return lenguaje_potencias;
}

// Método encargado de limpiar el contenido de un lenguaje y dejar vacíos sus atributos
void Lenguaje::Borrar() {
  cadenas_.clear();
  alfabeto_.clear();
}

// Sobrecarga del operador << para la escritura de los lenguajes en un fchero
std::ofstream& operator<<(std::ofstream& salida, const Lenguaje& lenguaje) {
  std::set<Alfabetos<std::string>>::iterator iterador_set_alfabeto = lenguaje.InicioContenedorAlfabeto();
  salida << "{ ";
  for (int iterador1 = 0; iterador1 < lenguaje.TamanioContenedorAlfabeto(); ++iterador1) {
    Alfabetos<std::string> alfabeto_extraido_lenguaje = *iterador_set_alfabeto;
    salida << alfabeto_extraido_lenguaje;
    std::advance(iterador_set_alfabeto, 1);
  }
  salida << "} ";
  salida << "{ ";
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = lenguaje.InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < lenguaje.TamanioContenedorCadenas(); ++iterador1) {
    Cadenas<std::string> cadena_extraida_lenguaje = *iterador_set_cadenas;
    salida << cadena_extraida_lenguaje << " ";
    std::advance(iterador_set_cadenas, 1);
  }
  salida << "}";
  return salida;
}

// Sobrecarga del operador << para la impresión de los lenguajes por pantalla
std::ostream& operator<<(std::ostream& salida, const Lenguaje& lenguaje) {
  std::set<Alfabetos<std::string>>::iterator iterador_set_alfabeto = lenguaje.InicioContenedorAlfabeto();
  salida << "{ ";
  for (int iterador1 = 0; iterador1 < lenguaje.TamanioContenedorAlfabeto(); ++iterador1) {
    Alfabetos<std::string> alfabeto_extraido_lenguaje = *iterador_set_alfabeto;
    salida << alfabeto_extraido_lenguaje;
    std::advance(iterador_set_alfabeto, 1);
  }
  salida << "} ";
  salida << "{ ";
  std::set<Cadenas<std::string>>::iterator iterador_set_cadenas = lenguaje.InicioContenedorCadenas();
  for (int iterador1 = 0; iterador1 < lenguaje.TamanioContenedorCadenas(); ++iterador1) {
    Cadenas<std::string> cadena_extraida_lenguaje = *iterador_set_cadenas;
    salida << cadena_extraida_lenguaje << " ";
    std::advance(iterador_set_cadenas, 1);
  }
  salida << "}";
  return salida;
}