// 
//  GlobalState.h
//  Created by Louis Faury on 03/10/2015
//  
//  This class gather all the information the INS module gave us on the state of the quadrirotor
//  Here we'll give other classes access to the quadricopter position, speed, acceleration, attitude in quaternion and Euler angle formats. 
//  Is namely used for the control algorithms
//
//




#ifndef __Auto_Pilot__GlobalState__
#define __Auto_Pilot__GlobalState__

#include <stdio.h>
#include <iostream>
#include </usr/local/include/Dense>



class GlobalState {
    
public:
    
    GlobalState();
    
    
    
private:
    
    Eigen::Vector3f _position;
    Eigen::Vector3f _speed;
    Eigen::Vector3f _acceleration;
    Eigen::Vector4f _quaternion;
    Eigen::Vector3f _RPY;
    Eigen::Vector3f _angular_acceleration;
    Eigen::Vector3f _angular_speed;
    
};


#endif

