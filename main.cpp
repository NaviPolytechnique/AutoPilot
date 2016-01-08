//
//  main.cpp
//  Auto_Pilot
//
//  Created by Louis Faury on 26/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#include <iostream>
#include "Autopilot.hpp"
#include "util.hpp"
#include "PID.hpp"
#include <fstream>
#include "Config.hpp"

int main(int argc, const char * argv[]) {
    
    
    /*Autopilot _auto(10); // Autopilot with 10 ms time rate
    _auto.take_off();
    _auto._run(); */
    
    const std::string file_path = "/Users/louisfaury/Documents/C++/Auto_pilot/test.txt";
    std::ofstream file(file_path.c_str());
    PID pid(10,-3,-1.2,-0.8);
    pid.sum_up();
    pid._update(0,50);
    // Test and simulate PID controler for \dot{x) = u
    for (int i=0; i<1000; i++) {
        file << pid.sum_up() << std::endl;
        pid._update(pid.getState() + pid.calculate_command()/100); 
        usleep(1000);
    }
    return 0;
}
