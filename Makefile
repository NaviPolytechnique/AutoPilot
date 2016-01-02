# Makefile for Autopilot
#

# Variable
CXX = g++
CXXFLAGS =-g -std=c++11 


# Rules 

main : main.o Autopilot.o Pilot_Exception.o util.o PID.o
	g++ $(CXXFLAGS) $^ -o $@

main.o : main.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Autopilot.o : Autopilot.cpp 
	g++ $(CXXFLAGS) -c $^ -o $@

util.o : util.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

Pilot_Exception.o : Pilot_Exception.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

PID.o : PID.cpp
	g++ $(CXXFLAGS) -c $^ -o $@

clean : 
	rm -rf *.o

all : 
	make main 
	make clean
	@echo SUCESS
