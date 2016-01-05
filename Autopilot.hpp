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
#include "Drone.h"
#include "Runnable.h"
#include <unistd.h>
#include <pthread.h>

class Pilot_Exception; // forward declaration

class PID; // forward declaration

extern int autoPilotThread;

class Autopilot : public Runnable {
    
public:
    
    enum FLIGHT_MODE{
        hovering,
        trajectory_tracking
    };
    
    Autopilot();
    
    Autopilot(Drone* drone_, uint8_t time_rate); // ne vaudrait-il pas mieux mettre le time rate en parmètre de config ?
    
    ~Autopilot();
    
    
    
    void _initialize() throw(Pilot_Exception);
    
    void _update();
    
    void* run(); // TO COMPLETE with PID
    
    void start();
    
    void _sanity_check() const throw(Pilot_Exception);
    
    
    
    void setNewTarget(uint16_t) throw(Pilot_Exception);
    
    void take_off(); //TO COMPLETE
    
    void land(); //TODO  : slowly decreases target until hits approx. 0 (10cm)
    
    uint16_t getAltitudeTarget();
    
    uint16_t getWtgAltitudeTarget();
    
    void setAltitudeTarget(uint16_t a);
    
    void setWtgAltitudeTarget(uint16_t a);
    
    
    
    
private:
    
    Drone* drone;
    
    const uint8_t _time_rate; // Controller time rate in ms
    
    pthread_mutex_t alt_target_mutex;
    uint16_t _altitude_target; // Altitude target in cm
    
    pthread_mutex_t wtg_alt_target_mutex;
    uint16_t _wtg_altitude_target; // New altitude target in cm
    
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
