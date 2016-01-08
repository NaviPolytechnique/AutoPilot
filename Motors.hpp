//
//  Motors.hpp
//  Auto_Pilot
//
//  Created by Louis Faury on 03/01/2016.
//  Copyright © 2016 Louis Faury. All rights reserved.
//

#ifndef Motors_hpp
#define Motors_hpp

#include <stdio.h>
#include "util.hpp"
#include "Config.hpp"
// TODO : add DC motor library (PMW)


class Motors {
    
public:
    
    Motors();
    
    void _update(Eigen::Vector4f); // Updates propeller speed given a command 
    
    
    
private:
    
    Eigen::Vector4f _motor_speed;
    // TODO : Port to write on (path to file or instance of serial)
    
};
#endif /* Motors_hpp */
