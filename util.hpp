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

namespace Autopilot_util {
    
    // Returns the inteprolation polynom for smoothing the target
    int calculate_tmp_target(unsigned int,Eigen::Vector4d&,unsigned int,unsigned int);
    
    
    // Updates the polynomials coefficient for the target smoothing polynom
    void update_poly(unsigned int,unsigned int,unsigned int,Eigen::Vector4d&);

}

#endif
