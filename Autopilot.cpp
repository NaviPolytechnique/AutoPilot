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
    

    
    

}




void Autopilot::init(){
    
    std::cout << "Init() Autopilot launched" << std::endl;
    
    
    _ready_to_take_off = true;
}





Autopilot::~Autopilot(){
}




