all: calculadora_main

calculadora_main: calculadora_main.o calculadora_func.o simbolo.o lenguaje.o calculadora.o
	g++ -o calculadora_main calculadora_main.o calculadora_func.o simbolo.o lenguaje.o calculadora.o -std=c++2a

calculadora_func.o: calculadora_func.cc
	g++ -c -o calculadora_func.o calculadora_func.cc -std=c++2a

calculadora_main.o: calculadora_main.cc
	g++ -c -o calculadora_main.o calculadora_main.cc -std=c++2a

simbolo.o: simbolo.cc
	g++ -c -o simbolo.o simbolo.cc -std=c++2a

lenguaje.o: lenguaje.cc
	g++ -c -o lenguaje.o lenguaje.cc -std=c++2a

calculadora.o: calculadora.cc
	g++ -c -o calculadora.o calculadora.cc -std=c++2a

clean:
	-rm calculadora_main.o calculadora_func.o simbolo.o lenguaje.o calculadora.o calculadora_main