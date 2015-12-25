//  GlobalState.cpp
//  Created by Louis Faury on 03/10/2015
//  
//  This class gather all the information the INS module gave us on the state of the quadrirotor
//  Here we'll give other classes access to the quadricopter position, speed, acceleration, attitude in quaternion and Euler angle formats. 
//  Is namely used for the control algorithms
//
//




#include "GlobalState.h"




GlobalState::GlobalState() {
    
 std::cout << "Global state constructor has been called" << std::endl;
 
}