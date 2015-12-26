// 
//  Autopilot.cpp
//  Created by Louis Faury on 03/10/2015
//  
//  This class is the base element for the automatic flight of the quadricopter 
//



#include "Autopilot.h"



Autopilot::Autopilot(uint8_t time_rate) :   _init(false),
                                            _took_off(false),
                                            _new_target(false),

                                            _time_rate(time_rate),
                                            _interpolating_time(5000),
                                            _clock_counter(UINT16_MAX)
{
    try {
        _initialize();
        
        std::cout << "Autopilot initiated" << std::endl;
    } catch(std::string & s) {
        std::cout << s << std::endl;
    }
}




void Autopilot::_initialize() throw(std::string){
    
    try {
        _sanity_check();
    
        _altitude_target = 50; // TODO : change with config file
        _tmp_altitude_target = 50; // TODO : same
        
        _init = true;
        
    } catch (const std::string& s) {
        std::cout << s << std::endl;
        throw std::string("Autopilot failed to init");
        
    }
    
}



void Autopilot::_sanity_check() const throw(std::string) {
    
    //Lets check that the rate is reachable
    if (_time_rate <= 5) throw std::string("Timing issue");
    
    // Lets check that the sampling time is at least superior to the functionning rate
    if (_interpolating_time <= _time_rate) throw std::string("Timing issue");
    
    //TODO : add security (checks size of int for instance)
    
}



void Autopilot::_run() {

    while (!_init) {
        //delay
    }
    
    while (!_took_off) {
        //wait for order to take off and then take off
    }
    
    while (true) {
        _update();
        switch(_fm) {
            case hovering : {
                // PID pid_alti.write_target(_tmp_target);
                // command = PID.calculate_command();
            }
            case trajectory_tracking:{
                
                
            }
                
        }
    }
}



void Autopilot::_update() {
    
    // Starts by checking if a new target was assigned
    
    if (_new_target) {
        _altitude_target = _wtg_attitude_target;
        _clock_counter = 0;
        // _interp_poly = update the interpolation polynom coeffs
        _new_target = false;
        
    }
    
    else {
        if (_clock_counter < _interpolating_time) {
             // tmp_target = updated target
            _clock_counter += _time_rate;
        }
        // else we change nothing, the target must remain const.
    }
    
    std::cout << "updated" << std::endl;
}


Autopilot::~Autopilot(){
}

