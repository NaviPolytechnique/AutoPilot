# Makefile for Auto_Pilot

.PHONY: clean
.SUFFIXES:

# Variables definition
CXX = g++
CXXFLAGS = -g -std=c++11
bindir = bin/
srcdir = src/


# Compilation

all : 
	make main
	make move
	make success

main : main.o GlobalState.o Autopilot.o LowController.o
	$(CXX) -o main main.o GlobalState.o Autopilot.o LowController.o $(CXXFLAGS)

main.o : $(srcdir)main.cpp 
	$(CXX) -c $(srcdir)main.cpp -o main.o $(CXXFLAGS)

GlobalState.o : $(srcdir)GlobalState.cpp 
	$(CXX) -c $(srcdir)GlobalState.cpp -o GlobalState.o $(CXXFLAGS)

Autopilot.o : $(srcdir)Autopilot.cpp
	$(CXX) -c $(srcdir)Autopilot.cpp -o Autopilot.o $(CXXFLAGS)

LowController.o : $(srcdir)LowController.cpp
	$(CXX) -c $(srcdir)LowController.cpp -o LowController.o $(CXXFLAGS)

move : 
	mv *.o $(bindir)

clean :
	 rm -rf *.o 

success : 
	@echo 'SUCCESS'

