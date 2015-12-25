//
//  LowController.cpp
//  Created by Louis Faury on 03/10/2015
//
//  This class is the the low controller for the autonomous flight, which is the controller in charge of the hovering when the copter doesn't have a mission
//



#include "LowController.h"


LowController::LowController(){
}


LowController::LowController(GlobalState* global_state) : navi_state(global_state) {
    std::cout << "LowController constructor called" << std::endl;
}



void LowController::_init(){
 
    _time_rate = 10; // Time rate in milliseconds 
    _target_altitude = 0;
    _trigger_position_lock = false;
    _init_ = true;
    
    std::cout << "Low Controller has been initialised" << std::endl;
}


void LowController::showProperties(){    
 //TODO   
}