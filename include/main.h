#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cmath>

#include "v5.h"
#include "vex_mevent.h"
#include "v5_vcs.h"

#include "stddefs.h"
#include "globals.h"

#include "pid_const.h"
#include "pid.h"
#include "drive.h"
#include "util.h"
#include "movement.h"
#include "robot-config.h"
#include "opcontrol.h"



// Main function declarations
void pre_auton(void);
void autonomous(void);
