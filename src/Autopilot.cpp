// 
//  Autopilot.cpp
//  Created by Louis Faury on 03/10/2015
//  
//  This class is the base element for the automatic flight of the quadricopter 
//



#include "Autopilot.h"



Autopilot::Autopilot() {
}



Autopilot::Autopilot(GlobalState* global_state) : _mission_available(false), _hovering(false), _ready_to_take_off(false), navi_state(global_state) {
    
    LowController low_controller(navi_state);
   // HighController high_controller(_HC_time_rate,navi_state);

    LC = &low_controller;
    //_HC = &high_controller;
    
    std::cout << "Autopilot created" << std::endl;
    
    this->init();

}




void Autopilot::init(){
    
    std::cout << "Init() Autopilot launched" << std::endl;
    LC->_init();
    //HC->_init();
    
    // TODO : launch routine to initialize the low and high controllers 
    
    _ready_to_take_off = true;
}


Autopilot::~Autopilot(){
}




