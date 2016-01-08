//
//  Config.hpp
//  Auto_Pilot
//
//  Created by Louis Faury on 29/12/2015.
//  Copyright © 2015 Louis Faury. All rights reserved.
//

#ifndef Config_h
#define Config_h


//*--- For Autopilot Block ---*//
// Units
#define NORMALIZE_CM_TO_M 0.01
// Target
#define MAX_ALTI_TARGET 2000 //cm
#define INI_ALTI_TARGET 50 //cm
// Time
#define MIN_TIME_RATE 5 //ms
#define INTERP_TIME 5 //s
// PID //TODO : set proper coefficient
#define EXTREMUM_INTEGRAL_ERROR 50
#define ALTI_KP 1.
#define ALTI_KI 1.
#define ALTI_KD 1.
#define PITCH_KP 1.
#define PITCH_KI 1.
#define PITCH_KD 1.
#define ROLL_KP 1.
#define ROLL_KI 1.
#define ROLL_KD 1.
#define YAW_KP 1.
#define YAW_KI 1.
#define YAW_KD 1.













#endif
