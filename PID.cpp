//
//  PID.cpp
//  Auto_Pilot
//
//  Created by Louis Faury on 30/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include "PID.hpp"



PID::PID(uint8_t time_rate,float KP, float KI, float KD) :   _time_rate(time_rate),
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



// Fonctions à checker avec Charles (indépendance du time rate ++ )
void PID::_update(float state) {
    _state = state;
    
    float previous_error(_error);
    _error = _state - _target;
    _derivative_error = (_error-previous_error);
    // TODO : Implement ways of saturationg the integral error with a saturator
    // Voir ordre de grandeur et limite de linéarité (doc)
    _integral_error += _error;
}


void PID::_update(float state, float target) {
    _target = target;
    _state = state;
    
    float previous_error(_error);
    _error = _state - _target;
    _derivative_error = _error-previous_error;
    // TODO : Implement ways of saturationg the integral error with a saturator
    // Voir ordre de grandeur et limite de linéarité (doc)
    _integral_error += _error;
}




float PID::calculate_command() const {
    return _KP*_error+_KD*_derivative_error+_KI*_integral_error;
}



void PID::reset() {
    // Put back to 0 all the errors (but derivative to avoid jumps in command)
    _error = 0;
    _integral_error = 0;
}



float PID::getState() {
    return _state;
}



std::string PID::sum_up() {
    std::string s = std::to_string(_state);
    
    std::cout << "Error : " << _error << '\n' << "Integral error : " << _integral_error << '\n' << "Derivative error : " << _derivative_error << '\n' << "Command : " << calculate_command() << std::endl;
    
    return s;
}