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
#include <cstdint>
#include "util.hpp"


class Autopilot {
  
public:
    
    enum FLIGHT_MODE{
	hovering,
	trajectory_tracking
    };


    Autopilot();
    
    
    Autopilot(uint8_t);

    ~Autopilot();

    
    
    void _initialize() throw(std::string);
    
    void _update();
    
    void _run(); // TODO : complete
    
    void _sanity_check() const throw(std::string);
    
    
    
    void setAltitudeTarget(uint8_t); //TODO

    void take_off(); //TODO
    
    void land(); //TODO


    
    
    
private:
    
    const uint8_t _time_rate; // Controller time rate in ms
    
    uint16_t _altitude_target; // Altitude target in cm
    uint16_t _wtg_attitude_target; // New altitude target in cm
    
    uint16_t _clock_counter; // For smoothing the target input (ms)
    uint16_t _interpolating_time; // For smoothing the target input (ms)


    Eigen::Vector4d _commands; // Throttle,pitch,roll and yaw commands
    Eigen::Vector4d _interp_poly; // For smoothing the target input;

    bool _init;
    bool _took_off;
    bool _new_target;
    
    
    FLIGHT_MODE _fm;
    
    //PID* alti_PID;
    //PID* pitch_PID;
    //PID* roll_PID;
    //PID* yaw_PID;
    
    
    //State* _state : ptr to the state of the drone (do forward declaration)
};

#endif
