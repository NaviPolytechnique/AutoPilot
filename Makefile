# Makefile for Autopilot
#

# Variable
CXX = g++
CXXFLAGS =-g 


# Rules 

main : main.o Autopilot.o Pilot_Exception.o util.o
	g++ $^ -o $@

main.o : main.cpp
	g++ -c $^ -o $@

Autopilot.o : Autopilot.cpp 
	g++ -c $^ -o $@

util.o : util.cpp
	g++ -c $^ -o $@

Pilot_Exception.o : Pilot_Exception.cpp
	g++ -c $^ -o $@

clean : 
	rm -rf *.o

all : 
	make main 
	make clean
