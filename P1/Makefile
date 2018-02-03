#$^ evalua a todos los ficheros de la regla
#$< evalua al primer fichero de la regla
#$@ evalua la regla

#Compilador
CXX=clang++
#Carpetas donde buscar cabeceras
VPATH = ../Tests-auto:.
#Flags del compilador
CXXFLAGS = -g -Wall -pedantic -std=c++11
#Flags del preprocesador
CPPFLAGS = -I../Tests-auto -I. -DP1
#Código objeto
OBJS = fecha.o cadena.o test-P1-consola.o test-auto.o test-P1-auto.o test-caso0-fecha-auto.o test-caso0-cadena-auto.o
TESTEXEC = test-P1-auto test-P1-consola
###
all: test-P1-consola test-P1-auto
###
test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@
test-caso0-fecha-auto.o test-caso0-cadena-auto.o: test-auto.hpp fecha.hpp cadena.hpp fct.h

test-P1-consola:test-P1-consola.o fecha.o cadena.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-consola.o:fecha.hpp cadena.hpp

fecha.o:fecha.cpp fecha.hpp

cadena.o:cadena.cpp cadena.hpp

clean:
	$(RM) all $(OBJS) $(TESTEXEC) core *~
