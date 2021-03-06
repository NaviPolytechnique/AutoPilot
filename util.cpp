//
//  util.cpp
//  Auto_Pilot
//
//  Created by Louis Faury on 28/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include "util.hpp"


float Autopilot_util::calculate_tmp_target(unsigned int target,Eigen::Vector4f& poly_coeff, unsigned int clock_counter, unsigned int interpolating_time) {
    
    // If we are over smoothing time, the target is the initial target
    if (clock_counter > 1000*interpolating_time) return target;
    
    // Else we're using the smoothing polynom to calculate target
    // Polynom being stored as {a,b,c,d} with p(x)=ax^3+bx^2+cx+d
    else return (
                poly_coeff[3]+poly_coeff[2]*clock_counter+poly_coeff[1]*clock_counter*clock_counter+poly_coeff[0]*clock_counter*clock_counter*clock_counter);
}

float Autopilot_util::calculate_tmp_SuperSmooth_target(unsigned int target, Eigen::Vector4f& poly_coeff, unsigned int clock_counter, unsigned int interpolating_time){
    
    // If we are over smoothing time, the target is the initial target
    if (clock_counter > 1000*interpolating_time) return target;
    
    // Else we're using the smoothing polynom to calculate target
    // Polynom being stored as {a,b,c,d} with p(x)=ax^3+bx^2+cx+d
    else return (
                 poly_coeff[3]+poly_coeff[2]*clock_counter*clock_counter+poly_coeff[1]*clock_counter*clock_counter*clock_counter+poly_coeff[0]*clock_counter*clock_counter*clock_counter*clock_counter);
}



void Autopilot_util::update_poly(unsigned int old_target, unsigned int new_target, unsigned int interpolating_time,Eigen::Vector4f& poly){
    
    // Setting value at half time, depends whether you go up or down
    double coef_at_half_time=(new_target>old_target ? 0.9 : 1.1);
    
    // Giving a more handling name to the interpolating time
    unsigned int& T = interpolating_time;
    // Setting the polynom to zero
    poly *= 0;
    
    // We're gonna solve a linear problem 'Ax = b' for calculating the coeff of a 'smoothing' polynom
    Eigen::Vector4f b;
    Eigen::Matrix4f A;
    b << new_target,0,coef_at_half_time*new_target,old_target;
    A  << T*T*T,T*T,T,1,3*T*T,2*T,1,0,0.125*T*T*T,0.25*T*T,0.5*T,1,0,0,0,1;
    
    // Updates the polynom coefficients, which are in this programm as [a,b,c,d] : ax^3+bx^2+cx+d
    poly = A.partialPivLu().solve(b);
    // We're giving the polynom a rescaling (sample time being in stored as in second, but we're working in miliseconds)
    poly[0] /= 1000000000;
    poly[1] /= 1000000;
    poly[2] /= 1000;
}

void Autopilot_util::update_SuperSmoothpoly(unsigned int old_target, unsigned int new_target, unsigned int interpolating_time,Eigen::Vector4f& poly){
    
    // Setting value at half time, depends whether you go up or down
    double coef_at_half_time=(new_target>old_target ? 0.9 : 1.1);
    
    // Giving a more handling name to the interpolating time
    unsigned int& T = interpolating_time;
    // Setting the polynom to zero
    poly *= 0;
    
    // We solve a linear problem 'Ax = b' for calculating the coeff of a 'supersmoothing' polynom
    Eigen::Vector4f b;
    Eigen::Matrix4f A;
    b << new_target,0,coef_at_half_time*new_target,old_target;
    A << T*T*T*T,T*T*T,T*T,1,     4*T*T*T,3*T*T,2*T,0,      0.0625*T*T*T*T,0.125*T*T*T,0.25*T*T,1,        0,0,0,1;
    
    // Updates the polynom coefficients, which are in this programm as [a,b,c,e] : ax^4+bx^3+cx^2+e
    poly = A.partialPivLu().solve(b);

    // We're giving the polynom a rescaling (sample time being in stored as in second, but we're working in miliseconds)
    poly[0]/=1000000000000;
    poly[1]/=1000000000;
    poly[2]/=1000000;
}