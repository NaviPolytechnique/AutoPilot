//
//  PID.cpp
//  Auto_Pilot
//
//  Created by Louis Faury on 30/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include "PID.hpp"




PID::PID(uint8_t time_rate,float KP, float KD, float KI) :   _time_rate(time_rate),
                                                                _KP(KP),
                                                                _KI(KI),
                                                                _KD(KD),
                                                                _error(0),
                                                                _derivative_error(0),
                                                                _integral_error(0),
                                                                _state(0),
                                                                _target(0)
{
}



void PID::_update(float state) {
    _state = state;
    
    float previous_error(_error);
    _error = _target - _state;
    _derivative_error = (_error-previous_error)/(_time_rate)*1000; // 1000 : conversion ms in s.
    // Implement ways of saturationg the integral error with a saturator
    _integral_error += (_time_rate*_error)/1000;
}


void PID::_update(float state, float target) {
    _target = target;
    _state = state;
    
    float previous_error(_error);
    _error = _target - _state;
    _derivative_error = (_error-previous_error)/(_time_rate)*1000; // 1000 : conversion ms in s.
    // Implement ways of saturationg the integral error with a saturator
    _integral_error += (_time_rate*_error)/1000;
}




float PID::calculate_command() const {
    return _KI*_error+_KD*_derivative_error+_KI*_integral_error;
}



void PID::reset() {
    // Put back to 0 all the errors (but derivative to avoid jumps in command)
    _error = 0;
    _integral_error = 0;
}