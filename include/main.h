#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <iostream>
#include <cmath>

// This exists only because Aden is too stupid to figure out lsp config. If using this code on any other computer, comment it out
#define ADENS_PC

#ifdef ADENS_PC

#include "../../../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/v5.h"
#include "../../../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/vex_mevent.h"
#include "../../../../../../Library/Application Support/Code/User/globalStorage/vexrobotics.vexcode/sdk/cpp/V5/V5_20220726_10_00_00/vexv5/include/v5_vcs.h"

#elif

#include "v5.h"
#include "vex_mevent.h"
#include "v5_vcs.h"

#endif

#include "robot-config.h"
#include "stddefs.h"
#include "globals.h"
#include "util.h"
#include "opcontrol.h"
#include "pid.h"

// Main function declarations
void pre_auton(void);
void autonomous(void);
