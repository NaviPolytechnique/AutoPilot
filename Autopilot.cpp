//
//  Autopilot.cpp
//  Created by Louis Faury on 03/10/2015
//
//  This class is the base element for the automatic flight of the quadricopter
//



#include "Autopilot.hpp"




Autopilot::Autopilot(Drone* drone_ , uint8_t time_rate) :   _init(false),
_took_off(false),
_new_target(false),

_time_rate(time_rate),
_interpolating_time(INTERP_TIME),
_clock_counter(0),
_altitude_target(0),
drone(drone_)
{
    
    try {
        _initialize();
        
        std::cout << "Autopilot initialized" << std::endl;
    } catch(const Pilot_Exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Autopilot::start(){
    drone->startThread(this, autoPilotThread);
}


void Autopilot::_initialize() throw(Pilot_Exception){
    
    try {
        _sanity_check();
        
        _init = true;
        
        // TODO : when _init, give the propellers a min speed to show everything is allright ?
    } catch (const Pilot_Exception& e) {
        std::cout << e.what() << std::endl;
        throw Pilot_Exception(Pilot_Exception::other,"Autopilot failed to init");
        
    }
    
    PID* alti_PID = new PID(_time_rate,ALTI_KP,ALTI_KD,ALTI_KD);
    PID* pitch_PID = new PID(_time_rate,PITCH_KP,PITCH_KD,PITCH_KD);
    PID* roll_PID = new PID(_time_rate,ROLL_KP,ROLL_KD,ROLL_KD);
    PID* yaw_PID = new PID(_time_rate,YAW_KP,YAW_KD,YAW_KD);
    _alti_PID = alti_PID;
    _roll_PID = roll_PID;
    _pitch_PID = pitch_PID;
    _yaw_PID = yaw_PID;
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



void* Autopilot::run() {
    
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
                // calculates temporary target given polynom and clock

                double tmp_target = Autopilot_util::calculate_tmp_target(getAltitudeTarget(),_interp_poly,_clock_counter,_interpolating_time);
                // updates the different PID (when hovering, only the altitude target needs to be changed)
                // Missing State class :-(
                _alti_PID->_update(_state->get_Z(),tmp_target);
                 _roll_PID->_update(_state->get_Roll());
                 _pitch_PID->_update(_state->get_Pitch());
                 _yaw_PID->_update(_state->get_Yaw());
                break;
            }
            case trajectory_tracking:{
                
                
            }
        }
        usleep(1000*_time_rate); //TODO : change with time clock
    }
}



void Autopilot::_update() {
    
    // Starts by checking if a new target was assigned
    
    if (_new_target) {
        // New target --> Lets update the polynom
        Autopilot_util::update_poly(getAltitudeTarget(),getWtgAltitudeTarget(),_interpolating_time,_interp_poly);
        // We udpate the current altitude target and put the clock counter back to 0
        setAltitudeTarget(getWtgAltitudeTarget());
        _clock_counter = 0;
        // Reset the alti PID
        _alti_PID->reset();
        // Now there is no new target
        _new_target = false;
        
    }
    
    else {
        _clock_counter += (_clock_counter < UINT16_MAX ? _time_rate : 0); // Cannot overcome UINT16_MAX but doesn't really matter since the interpolating function is constant at this moment
    }
    
}




void Autopilot::setNewTarget(uint16_t altitude_target) throw(Pilot_Exception) {
    if (altitude_target<0 || altitude_target > MAX_ALTI_TARGET) throw Pilot_Exception(Pilot_Exception::target,"Unreachable target");
    // Sets up _new_target to true and the waiting target to the argument altitude target 
    _new_target = true;
    setWtgAltitudeTarget(altitude_target);
}



void Autopilot::take_off(){
    // When given the signal, the quadcopter lifts to INI_ALTI_TARGET
    setNewTarget(INI_ALTI_TARGET);
    _fm = hovering;
    _took_off = true;
}


Autopilot::~Autopilot(){
    delete _alti_PID;
    delete _roll_PID;
    delete _pitch_PID;
    delete _yaw_PID;
    _alti_PID = 0;
    _roll_PID = 0;
    _pitch_PID = 0;
    _yaw_PID = 0;
}


void Autopilot::setAltitudeTarget(uint16_t alt){
    pthread_mutex_lock(&alt_target_mutex);
    _altitude_target = alt;
    pthread_mutex_unlock(&alt_target_mutex);
};


void Autopilot::setWtgAltitudeTarget(uint16_t alt){
    pthread_mutex_lock(&wtg_alt_target_mutex);
    _wtg_altitude_target = alt;
    pthread_mutex_unlock(&wtg_alt_target_mutex);
};

uint16_t Autopilot::getAltitudeTarget(){
    uint16_t r;
    pthread_mutex_lock(&alt_target_mutex);
    r = _altitude_target;
    pthread_mutex_unlock(&alt_target_mutex);
    return r;
};

uint16_t Autopilot::getWtgAltitudeTarget(){
    uint16_t r;
    pthread_mutex_lock(&wtg_alt_target_mutex);
    r = _wtg_altitude_target;
    pthread_mutex_unlock(&wtg_alt_target_mutex);
    return r;
};