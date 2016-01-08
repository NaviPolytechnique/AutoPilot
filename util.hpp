//
//  util.hpp
//  Auto_Pilot
//
//  Created by Louis Faury on 28/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include "/usr/local/include/Dense"
#include <iostream>

namespace Autopilot_util {
    
    // Returns the value of interpolation polynom for smoothing the target at the current time
    float calculate_tmp_target(unsigned int,Eigen::Vector4f&,unsigned int,unsigned int);
    
    // Returns the value of interpolation polynom for super smoothing the target at the current time
    float calculate_tmp_SuperSmooth_target(unsigned int, Eigen::Vector4f&, unsigned int, unsigned int);
    
    // Updates the polynomials coefficient for the target smoothing polynom
    void update_poly(unsigned int,unsigned int,unsigned int,Eigen::Vector4f&);
    
    // Updates the polynomials coefficent for the target super smoothing polynom
    void update_SuperSmoothpoly(unsigned int, unsigned int, unsigned int,Eigen::Vector4f&);

}

#endif
