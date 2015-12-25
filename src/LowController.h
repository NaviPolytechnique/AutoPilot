// 
//  LowController.h
//  Created by Louis Faury on 03/10/2015
//  
//  This class is the the low controller for the autonomous flight, which is the controller in charge of the hovering when the copter doesn't have a mission
//




#ifndef __Auto_Pilot__LowController__
#define __Auto_Pilot__LowController__


#include <stdio.h>
#include <iostream>
#include <vector>
#include "GlobalState.h"


class LowController   {
    
public:
    
    
    LowController();
    
    
    LowController(GlobalState*);
    
    
    void _init(); // TODO : intialise the low controller before taking off (what altitude to take off,..)
    
    
    void lock_and_stabilize();  // TODO : launch PID procedure to lock on a given altitude 
    
    
    void showProperties();
    
private:
    
    GlobalState* navi_state;     // Ptr to the current state of the quadricopter    

    bool _trigger_position_lock;
    bool _init_;
    
    //Point _locking_point; // TODO : define class Point (should be in package "util")
    
    double _time_rate;
    double _target_altitude;
    
    
};


#endif 
