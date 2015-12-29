//
//  main.cpp
//  Auto_Pilot
//
//  Created by Louis Faury on 26/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include <iostream>
#include "Autopilot.h"
#include "util.hpp"


int main(int argc, const char * argv[]) {
    
    
    Autopilot _auto(10); // Autopilot with 10 ms time rate
    _auto._update();
    
    

    return 1;
}
