#include "vex.h"


using namespace vex;
// Define signature as an alias for vision::signature
using signature = vision::signature;
// Define code as an alias for vision::code
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);//Defines the primary controller for user input
motor LF = motor(PORT11, ratio6_1, true);//Left Front Motor
motor LM = motor(PORT12, ratio6_1, true);//Left Middle Motor
motor RF = motor(PORT18, ratio6_1, false);//Right Front Motor
motor RM = motor(PORT19, ratio6_1, false);//Right Middle Motor
motor LB = motor(PORT13, ratio6_1, true);//Left Back Motor
motor RB = motor(PORT20, ratio6_1, false);//Right Back Motor
motor Roller = motor(PORT21, ratio6_1, false);//Roller Motor
digital_out Pistake = digital_out(Brain.ThreeWirePort.D);//Pistake Control
digital_out Tilt = digital_out(Brain.ThreeWirePort.B);//Tilt Control
digital_out Clamp = digital_out(Brain.ThreeWirePort.A);//Clamp Control
inertial Gyro = inertial(PORT2);//Gyro Sensor
//Naming convention: 
// Important variables
const double wheelDiam = 2.75;
const double wheelToMotorRatio = 48.0/36;//This represents the gear ratio between the motor and the wheel

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;//a flag that controls whether your robot will respond to the controller during user control.

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}