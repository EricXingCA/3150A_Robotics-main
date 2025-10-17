using namespace vex;

extern brain Brain;//

// VEXcode devices
extern controller Controller1;//Main Controller
extern motor LF;//Left Front Motor
extern motor LM;//Left Middle Motor
extern motor RF;//Right Front Motor
extern motor RM;//Right Middle Motor
extern motor LB;//Left Back Motor
extern motor RB;//Right Back Motor
extern motor Roller;//Roller Motor
extern digital_out Tilt;//Pneumatic to tilt the roller
extern digital_out Clamp;//Pneumatic to clamp the roller
extern digital_out RightBackWing;//Pneumatic to open the right side of the claw
extern digital_out Pistake;//Pneumatic to open the left side of the claw
extern motor PU;//Puncher Motor
extern inertial Gyro;//Gyro
extern digital_out LeftBackWing;//Pneumatic to open the left side of the claw
extern const double wheelDiam;//Wheel Diameter in inches
extern const double wheelToMotorRatio;//Wheel to Motor Gear Ratio
extern const double wheelCircumference;//Wheel Circumference in inches
extern const double robotWidth;//Distance between left and right wheels in inches
extern const double robotLength;//Distance between front and back wheels in inches
extern const double robotRadius;//Distance from center of robot to wheel in inches
extern const double robotPerimeter;//Distance around the robot in inches
extern const double motorToWheelRatio;//Motor to Wheel Gear Ratio
extern const double motorToRollerRatio;//Motor to Roller Gear Ratio
extern const double rollerDiam;//Roller Diameter in inches
extern const double rollerCircumference;//Roller Circumference in inches
extern const double rollerToMotorRatio;//Roller to Motor Gear Ratio
extern const double PUToMotorRatio;//Puncher to Motor Gear Ratio
extern const double PUFullRotation;//Degrees of puncher rotation for a full rotation of the puncher
extern const double PUHalfRotation;//Degrees of puncher rotation for a half rotation of the puncher
extern const double PUQuarterRotation;//Degrees of puncher rotation for a quarter rotation of the puncher
extern const double PUEighthRotation;//Degrees of puncher rotation for an eighth rotation of the puncher
extern const double PUSixteenthRotation;//Degrees of puncher rotation for a sixteenth rotation of the puncher
extern const double PUThirtySecondRotation;//Degrees of puncher rotation for a thirty-second rotation of the puncher
extern const double PUOneTwentyFourthRotation;//Degrees of puncher rotation for a one-twenty-fourth rotation of the puncher
extern const double PUToDegrees;//Degrees the motor must turn for one degree of puncher rotation
extern const double GyroToDegrees;//Degrees the gyro must turn for one degree of robot rotation

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );