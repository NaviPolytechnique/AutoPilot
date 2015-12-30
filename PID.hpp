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

// TODO : class method for dealing with yaw sign problem 


class PID {
    
public:
    
    PID();
    
    PID(uint8_t,float,float,float);
    
    // Updates target and state, as well as errors
    void _update(float);
    
    // Outputs the command (U_i)
    float calculate_command() const;
    
    // Update the target and state
    void _update(float,float);
    
    // Reset PID (when a new target is received by the autopilot)
    void reset();
    
    
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
