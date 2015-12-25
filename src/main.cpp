// 
//  main.cpp
//  Created by Louis Faury on 03/10/2015
//  
//  Testing the basis of the AutoPilot Programm
//


#include <iostream>
#include <stdio.h>
#include "GlobalState.h"
#include "Autopilot.h"




int main(int argc,const char* argv[]) {
    
    // Declaring a pointeur to a global state
    GlobalState global_state;

    
    // Constructing the Autopilot
    Autopilot auto_pilot(&global_state);
    
    // Ending 
    
    std::cout << "End !" << std::endl;
    
    
    return 1;
    
}