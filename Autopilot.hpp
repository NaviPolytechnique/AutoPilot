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
#include "Pilot_Exception.hpp"
#include "Config.hpp"
#include "PID.hpp"
#include <unistd.h>
#include "navi_State.hpp"

class Pilot_Exception; // forward declaration

class PID; // forward declaration

class navi_State; // forward declaration


class Autopilot {
    
public:
    
    enum FLIGHT_MODE{
        hovering,
        trajectory_tracking
    };
    
    
    Autopilot();
    
    Autopilot(uint8_t,navi_State*);
    
    ~Autopilot();
    
    
    
    void _initialize() throw(Pilot_Exception);
    
    void _update();
    
    void _run(); // TO COMPLETE with PID
    
    void _sanity_check() const throw(Pilot_Exception);
    
    
    
    void setAltitudeTarget(uint16_t) throw(Pilot_Exception);
    
    void take_off(); //TO COMPLETE
    
    void land(); //TODO  : slowly decreases target until hits approx. 0 (10cm)
    
    
    
    
private:
    
    const uint8_t _time_rate; // Controller time rate in ms
    
    uint16_t _altitude_target; // Altitude target in cm
    uint16_t _wtg_attitude_target; // New altitude target in cm
    
    uint16_t _clock_counter; // For smoothing the target input (ms)
    uint16_t _interpolating_time; // For smoothing the target input (SECOND)
    
    
    Eigen::Vector4f _commands; // Throttle,pitch,roll and yaw commands
    Eigen::Vector4f _interp_poly; // For smoothing the target input;
    
    bool _init;
    bool _took_off;
    bool _new_target;
    
    
    FLIGHT_MODE _fm;
    
    PID* _alti_PID;
    PID* _pitch_PID;
    PID* _roll_PID;
    PID* _yaw_PID;
    
    
    navi_State* _state; // ptr to the state of the drone
};

#endif
