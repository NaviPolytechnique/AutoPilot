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
                                            _interpolating_time(INTERP_TIME),
                                            _clock_counter(0)
{
    try {
        _initialize();
        
        std::cout << "Autopilot initiated" << std::endl;
    } catch(const Pilot_Exception& e) {
        std::cout << e.what() << std::endl;
    }
}




void Autopilot::_initialize() throw(Pilot_Exception){
    
    try {
        _sanity_check();
    
        _altitude_target = INI_ALTI_TARGET; // TODO : change with config file
        
        _init = true;
        
    } catch (const Pilot_Exception& e) {
        std::cout << e.what() << std::endl;
        throw Pilot_Exception(Pilot_Exception::other,"Autopilot failed to init");
        
    }
    
}



void Autopilot::_sanity_check() const throw(Pilot_Exception) {
    
    //Lets check that the rate is reachable
    if (_time_rate <= MIN_TIME_RATE) throw Pilot_Exception(Pilot_Exception::timing,"Rate time is not feasible");
    
    // Lets check that the sampling time is at least superior to the functionning rate
    if (_interpolating_time <= _time_rate) Pilot_Exception(Pilot_Exception::timing,"Change interp. time and rate time ratio !");
    
    // Checks that other integers are fit
    bool sanity_const = (_interpolating_time > 0 && _interpolating_time < UINT16_MAX);
    if (!sanity_const) throw Pilot_Exception(Pilot_Exception::timing,"Interpolating time is not feasible");
    
    
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
                // calculate temporary target given polynom and clock
                //double tmp_target = Autopilot_util::calculate_tmp_target(_altitude_target,_interp_poly,_clock_counter,_interpolating_time);
                // Then calculate the corresponding PID commands
                // command = PID.calculate_command(target);
                //
                break;
            }
            case trajectory_tracking:{
                
                
            }
                
        }
    }
}



void Autopilot::_update() {
    
    // Starts by checking if a new target was assigned
    
    if (_new_target) {
        // New target --> Lets update the polynom
        Autopilot_util::update_poly(_altitude_target,_wtg_attitude_target,_interpolating_time,_interp_poly);
        // We udpate the current altitude target and put the clock counter back to 0
        _altitude_target = _wtg_attitude_target;
        _clock_counter = 0;
        // Now there is no new target
        _new_target = false;
        
    }
    
    else {
            if (_clock_counter < UINT16_MAX) _clock_counter += _time_rate; // Cannot overcome UINT16_MAX but doesn't really matter since the interpolating function is constant at this moment 
    }
    
    std::cout << "updated" << std::endl;
}



void Autopilot::setAltitudeTarget(uint16_t altitude_target) throw(Pilot_Exception) {
    if (altitude_target<0 || altitude_target > MAX_ALTI_TARGET) throw Pilot_Exception(Pilot_Exception::target,"Unreachable target");
    // TODO : change those values with config
    _new_target = true;
    _wtg_attitude_target = altitude_target;
}



void Autopilot::take_off(){
    // This function is a sign that everything is working allright. We simply put command U1 to a value so that the quadcopter does not lift but activite its propellers for a given amount of time.
    // Then we can set a target
    _took_off = true;
}


Autopilot::~Autopilot(){
}

