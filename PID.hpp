//
//  PID.hpp
//  Auto_Pilot
//
//  Created by Louis Faury on 30/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#ifndef PID_hpp
#define PID_hpp

#include <stdio.h>
#include <cstdint>
#include <iostream>
#include "Config.hpp"

class PID {
    
public:
	
    PID();

    /* \brief Main constructor of the PID class
     * \param uint8_t : time_rate (ms, given by master class Autopilot)
     * \param float : KP
     * \param float : KI
     * \param float : KD
     */    
    PID(uint8_t,float,float,float);
    
    /* \brief Update the state and erros 
     * \param float : state (z in cm)
     */
    void _update(float);
    

    /* \brief Update the state,target and erros 
     * \param float : state (z in cm)
     * \param float : target (ztarget in cm)
     */
    void _update(float,float);
    
    /* \brief Outputs the command 
     */
    float calculate_command() const;
    
    /* \brief Resets (all erros to 0)
     */
    void reset();
    
    /* Functions for develpment and tests 
     */

    std::string sum_up();
    
    float getState();
    
    
private:
    
    float _target;
    float _state;
    
    const uint8_t _time_rate;
    
    // Error
    float _error;
    float _derivative_error;
    float _integral_error;
    // P,I and D coefficients
    const float _KP;
    const float _KI;
    const float _KD;
};


#endif
