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
    
    /* \brief Flight mode for the quadricopter 
     * \brief Hovering for stabilisation and altitude command 
     * \brief Trajectory tracking for stabilisation aroud reference trajectory 
     */	
    enum FLIGHT_MODE{
        hovering,
        trajectory_tracking
    };
    
    /* \brief Basic constructor (obsolete)
     */
    Autopilot();
    
    /* \brief Main constructor 
     * \param uint8_t : time rate 
     * \param navi_State : ptr to the state class of the drone 
     */
    Autopilot(uint8_t,navi_State*);
    
    ~Autopilot();
    
    
    /* \brief Initialise the autopilot
     * Autopilot will not run if not initiliazed properly
     */
    void _initialize() throw(Pilot_Exception);
    
    /* \brief Update the local clock and checks if a new target has been assigned to the autopilot
     * \throw Pilot_Exception if initialize went wrong 
     */
    void _update();
    
    /* \brief Main method, whill will continuously : 
     * - Update target and smoothing polynomial function 
     * - Update PID controllers (hovering)
     * - Update LQR (trajectory tracking)
     */
    void _run(); 
   
    /* \brief Runs a sanity check over the attributes of the drone (for _init())
     * \throw Pilot_Exception if system is not sane 
     */ 
    void _sanity_check() const throw(Pilot_Exception);
    
    
    /* \brief Sets altitude target for the autopilot 
     * \param uint16_t : 
     * \throw : Pilot_Exception if target is not reachable 
     */
    void setAltitudeTarget(uint16_t) throw(Pilot_Exception);
    
    /* \brief Take off command 
     */
    void take_off(); 
    
    /* \brief Land command 
     */
    void land(); //TODO  : slowly decreases target until hits approx. 0 (10cm)
    
    /* \brief Updates the command vector thanks to the PID controller 
     */
    void update_commands();
    
    
    
private:
    
    const uint8_t _time_rate; // Controller time rate in ms
    
    uint16_t _altitude_target; // Altitude target in cm // TODO : protect
    uint16_t _wtg_attitude_target; // New altitude target in cm // TODO : protect
    
    uint16_t _clock_counter; // For smoothing the target input (ms)
    uint16_t _interpolating_time; // For smoothing the target input (SECOND)
    
    
    Eigen::Vector4f _commands; // Throttle,pitch,roll and yaw commands
    Eigen::Vector4f _interp_poly; // For smoothing the target input
    
    bool _init; // TODO : protéger
    bool _took_off; // TODO : protéger 
    bool _new_target; 
    
    
    FLIGHT_MODE _fm;
    
    PID* _alti_PID;
    PID* _pitch_PID;
    PID* _roll_PID;
    PID* _yaw_PID;
    
    
    navi_State* _state; // ptr to the state of the drone
};

#endif
