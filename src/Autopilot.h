// 
//  Autopilot.h
//  Created by Louis Faury on 03/10/2015
//  
//  This class is the base element for the automatic flight of the quadricopter 
//




#ifndef __Auto_Pilot__Autopilot__
#define __Auto_Pilot__Autopilot__


#include <stdio.h>
#include <iostream>
#include <vector>
#include "LowController.h"
#include "HighController.h"
#include "GlobalState.h"





class Autopilot {
  
public:
    
    Autopilot();
    
    
    Autopilot(GlobalState*);
    
    
    void init();
    
    
    void setMission();
    
    
    void hover(double z);
    
    
    ~Autopilot();
    
    
    
private:
    
    LowController* LC;           // Ptr to the autopilot low controller 
    //HighController* HC;          // Ptr to the autopilot high controller
    
    double _LC_time_rate;
    double _HC_time_rate;
    
    bool _hovering;             // True if the quadcopter is waiting for a new mission
    bool _mission_available;    // True if a mission is avalaible for the quadcopter
    bool _ready_to_take_off;    // True is the autopilot is correctly initialized 
    
    //Mission _current_mission;    // TODO : Create the Mission class
    GlobalState* navi_state;     
    
    
    
};

#endif