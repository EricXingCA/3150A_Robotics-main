/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//#include "STDLib.cpp"
#include "vex.h"
/* includes the Main VEX Header file, which provides access to VEX-specific classes, functions, and hardware definitions (like motors, sensors, and the competition template).
It is required for your program to interact with the VEX hardware and API.*/

#include "screen_gui.hpp"
/*This includes the screen_gui.hpp header file, which likely contains functions and definitions for managing the robot’s screen graphical user interface (GUI).
It allows your program to use custom screen display features, such as drawing, printing messages, or handling user input on the VEX Brain screen.*/
#include "movement.hpp"
/*This includes the movement.hpp header file, which contains function and variable declarations related to robot movement (such as PID control, motor commands, and sensor updates).
It allows your program to use movement-related functions and data structures defined for your robot.*/
#include "routes/routes.hpp"
/*This includes the routes.hpp header file from the routes folder.
It likely contains function declarations for different autonomous routes or routines your robot can perform.
Including this file allows your main program to call specific route functions (like route2(), test(), etc.)*/
using namespace vex;
/*This allows you to use all classes, functions, and objects from the vex namespace without needing to prefix them with vex::.
For example, you can write Brain.Screen.print() instead of vex::Brain.Screen.print().
It makes your code cleaner and easier to read when working with the VEX Robotics API.*/
// A global instance of competition
competition Competition;
/*This creates a global instance of the competition class from the VEX Robotics API.
It manages the robot’s behavior during competition, handling autonomous and driver control periods.
You use this object to set up callbacks for your autonomous and user control functions, allowing the robot to respond correctly to field control signals.*/

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool SP;
/*This declares a global boolean variable named SP.
In your code, SP is used to track the state of the screen press on the VEX Brain.
It helps manage user input during the autonomous selection process, ensuring actions are only triggered once per press.*/
bool EXIT;
/*This declares a global boolean variable named EXIT.
In your code, EXIT is used to control the exit condition for the autonomous selection loop in pre_auton().
When EXIT becomes true, the loop ends, confirming the autonomous routine selection and allowing the program to proceed.*/
void pre_auton(void) {
  /*This declares the pre_auton function, which runs before the competition starts.
It is used to perform setup actions such as initializing sensors, resetting variables, calibrating devices, and allowing the user to select the autonomous routine.
This function is called once after the V5 Brain is powered on and before autonomous or user control tasks begin.*/
  EXIT=false;
  /*It ensures the autonomous selection loop runs until the user confirms their choice, at which point EXIT is set to true to exit the loop and proceed.*/
  Tilt.set(true);//Initial positions of pneumatics
  /*This sets the Tilt pneumatic device to its "active" or "extended" position at the start of the pre_auton function.
It ensures the robot’s tilt mechanism is in the correct initial state before the match begins.
This is typically used to prepare the robot for autonomous actions or to comply with competition starting requirements.*/
  Clamp.set(true);//Clamp closed
  // All activities that occur before the competition starts
  PX=0;//Resetting Encoders
  /*This resets the global variable PX to zero at the start of the pre_auton function.
PX is likely used to track the position of an encoder (distance or rotation).
Resetting it ensures the robot starts from a known reference point before the match begins, which is important for accurate autonomous movement.*/
  JX=0;//Resetting Gyro
  /*This resets the global variable JX to zero at the start of the pre_auton function.
JX is likely used to track the robot’s gyro sensor (orientation or heading).
Resetting it ensures the robot starts from a known reference point before the match begins, which is important for accurate autonomous navigation.*/
  AutoSelectorVal=0;//Resetting AutoSelector
  /*This resets the global variable AutoSelectorVal to zero at the start of the pre_auton function.
AutoSelectorVal is used to track which autonomous routine is selected by the user.
Setting it to zero ensures no routine is selected by default, and the user must choose one before the match begins.*/
  SP=false;//Resetting Screen Press
/*SP is used to track the state of the screen press on the VEX Brain.
Resetting it ensures that the autonomous selection process starts with no screen press detected, allowing accurate user input handling.*/

  // Initializing Robot Configuration. DO NOT REMOVE!
vexcodeInit();//Init motors and sensors
/*This function initializes the robot configuration, motors, sensors, and other devices as defined in your VEXcode project.
It is required for proper hardware setup before running any robot code.
You should not remove or modify this line, as it ensures all devices are ready for use.*/
   //Calibrate Gyro
Gyro.calibrate();
/*This starts the calibration process for the robot’s gyro sensor.
Calibration ensures the gyro provides accurate heading and rotation data by setting a reference point and compensating for drift or sensor errors.
It is important to calibrate the gyro before using it for autonomous navigation or turns.
The code usually waits for calibration to finish before proceeding with autonomous setup.*/


//Ensure Robot Launch Position is set before auto proceeds, once plugged into field control,
//start program and do not temper bot under all circumstances

//1. IF ANY ADJUSTMENT IS NEEDED, QUIT PROGRAM, THEN ADJUST, RESTART PROGRAM AFTER ADJUSTMENTS COMPLETED
//2. DO NOT START PROGRAM BEFORE PLUGGING IN FIELD CONTROL, THIS MAY DISABLE AUTO
//3. ONLY SIGNAL JUDGES TO BEGIN MATCH AFTER THE ZEROING PROMPT ON SCREEN HAS CLEARED

//Print precautionary message
Brain.Screen.drawRectangle(0,0,500,500);

Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(2,10);
Brain.Screen.print("FLIR TIMEOUT");


waitUntil(!Gyro.isCalibrating());


Zeroing(true,true);
/*This calls the Zeroing function (movement.cpp) with both arguments set to true.

The first argument (dist) likely tells the function to reset distance sensors or encoders.
The second argument (HDG) likely tells it to reset heading sensors, such as the gyro.
This ensures the robot’s position and orientation sensors are set to a known reference point before starting autonomous or user control routines, improving movement accuracy.*/
DisplayAutoSelector();
/*This calls the DisplayAutoSelector function (screen_gui.cpp), which likely updates the VEX Brain screen to show the autonomous routine selection interface.
It helps the user visually choose which autonomous routine to run before the match starts, improving usability and ensuring the correct routine is selected.*/
DisplayWords();
/*This calls the DisplayWords function(screen_gui.cpp), which likely prints instructions, status messages, or other helpful information to the VEX Brain screen.
It helps guide the user during autonomous selection or setup, improving clarity and usability before the match starts.*/
//task AutoSelTask=task(ScreenSelMain);
  while(!EXIT)
{
if(Brain.Screen.xPosition()<100)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)AutoSelectorVal=1;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)AutoSelectorVal=3;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)AutoSelectorVal=5;
}
else if(Brain.Screen.xPosition()>375)
{
if(Brain.Screen.yPosition()<75&&Brain.Screen.yPosition()>25)AutoSelectorVal=2;
else if(Brain.Screen.yPosition()<150&&Brain.Screen.yPosition()>100)AutoSelectorVal=4;
else if(Brain.Screen.yPosition()<225&&Brain.Screen.yPosition()>175)AutoSelectorVal=6;
}
/*This checks the position of a screen press on the VEX Brain.
If the press is on the left side (x < 100), it sets AutoSelectorVal to 1, 3, or 5 depending on the vertical position (y).
If the press is on the right side (x > 375), it sets AutoSelectorVal to 2, 4, or 6 depending on the vertical position.
This allows the user to select different autonomous routines by pressing specific regions of the screen.*/
if(Brain.Screen.xPosition()>187&&Brain.Screen.xPosition()<287)
{
if(Brain.Screen.yPosition()<55&&Brain.Screen.yPosition()>5) EXIT=true;
else if(Brain.Screen.yPosition()>125&&Brain.Screen.yPosition()<225)AutoSelectorVal=7;
}
/*If the screen press is in the central horizontal area (x between 187 and 287):
If the vertical position (y) is between 5 and 55, it sets EXIT to true, confirming the autonomous selection and exiting the selection loop.
If the vertical position (y) is between 125 and 225, it sets AutoSelectorVal to 7, selecting the "SKILLS" autonomous routine.
This allows the user to confirm their selection or choose the skills routine by pressing specific regions of the screen.*/


if(Brain.Screen.pressing()&&!SP) UpdateDynamic();
SP=Brain.Screen.pressing();
/*Brain.Screen.pressing() checks if the screen is currently being pressed.
!SP ensures the action only triggers on a new press (not while holding).
UpdateDynamic() (screen_gui.cpp)is called once per press to update the screen or selection.
SP is then set to the current pressing state, so the update only happens once per press, not repeatedly while holding.*/


}

Brain.Screen.clearScreen();
if(AutoSelectorVal==1){
  Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("6 BALL");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");

}
/*This code displays information about the selected autonomous routine on the VEX Brain screen when AutoSelectorVal is set to 1:
This visually confirms to the user that the "GOAL SIDE 6 BALL" autonomous routine has been selected.
It uses large, readable text and color contrast for clarity on the VEX Brain screen.
*/


if(AutoSelectorVal==2){
Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("StealAWP");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");
}

if(AutoSelectorVal==3){

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("5 BALL");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#39FF14");
}

if(AutoSelectorVal==4){

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("Elim-Steal");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(AutoSelectorVal==5){

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("GOAL SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("GS-AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(AutoSelectorVal==6){
  
  Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("MATCHLOAD");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("ONLY AWP");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

  }

if(AutoSelectorVal==7){

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("SKILLS");
Brain.Screen.setFont(monoM); 
Brain.Screen.setFillColor("#39FF14");

}

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(5,10);
Brain.Screen.print("AUTO CONFIRMED");

/*This code displays a confirmation message on the VEX Brain screen after the autonomous routine is selected:
It visually confirms to the user that their selection has been acknowledged.
*/

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
/*This declares the autonomous function, which runs during the autonomous phase of a VEX competition.
Inside this function, you control the robot without user input, using sensors and pre-programmed routines.
Your code uses AutoSelectorVal to determine which autonomous routine to execute, allowing for flexible strategy selection before the match.*/  


//PID Straight and turn arguments:
// MoveEncoderPID(TestPara, motor speed, encoder travel distance (inches), time to full speed(sec), relative heading(to starting position), braking?)
// TurnMaxTimePID(TestPara, Desired Heading -180 to 180, time out to calculate turn, Braking?)
// MoveTimePID(TestPara, motor speed, time traveled (sec), time to full speed, heading, false);

//Do not change the below
PIDDataSet TestPara={4,0.1,0.2};
/*This creates a PIDDataSet structure (in movement.hpp) named TestPara  (in movement.hpp) and initializes its values:
kp = 4 (proportional gain)
ki = 0.1 (integral gain)
kd = 0.2 (derivative gain)
These values are used for PID control algorithms to help the robot move accurately by adjusting motor power based on sensor feedback.
You can pass TestPara to movement functions like MoveEncoderPID or TurnMaxTimePID to use these PID settings.*/

Zeroing(true,true);


//can start editing if nessary
//Put Auto route function into if statements to use autoselector
if(AutoSelectorVal==1) //Quali close 6 triball auto 
{
  test();
  /*This calls the test() function, which is defined in your project (likely in routes/routes.hpp and its corresponding .cpp file).*/
}

if(AutoSelectorVal==2)// awp mid steal
{
  test2();

}

if(AutoSelectorVal==3) // route2
{
  route2();
} 

if(AutoSelectorVal==4)// Elim-Steal
{

  test3();
  
}

if(AutoSelectorVal==5)// empty
{
   //test();
}


if(AutoSelectorVal==6)//AWP only
{

}


if(AutoSelectorVal==7)//temporary prog skills
{ 
 

}
//MoveTimePID(TestPara, -100, 0.5,0.1,-40,true);//score 2nd triball
//(PID Parameters, motor speed -100 - 100, time for travel 0 - inf, time to accelerate to full speed, Absolute Heading, Braking?)

    // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
CStop();
/*This calls the CStop() function, which is defined in your project (likely in movement.hpp and its corresponding .cpp file).
CStop() is used to stop the robot’s chassis motors at the end of the autonomous routine, ensuring the robot does not continue moving after autonomous actions are complete.
It helps safely end autonomous movement before switching to user control.*/
}


int RV;
int LV;
int DriveTask(void){
  while(true)
  {
    EXIT=true;
    /*Sets EXIT=true to ensure the autonomous selection loop is exited when driver control begins.*/
    RV=-Controller1.Axis3.position(percent)-Controller1.Axis1.position(percent);
    /*This calculates the right motor value (RV) for arcade drive control using the VEX Controller:
    Controller1.Axis3.position(percent) reads the forward/backward joystick value.
    Controller1.Axis1.position(percent) reads the turning joystick value.
    The negative sign reverses the direction if needed.
    This formula combines forward/backward and turning inputs to control the right side motors, allowing smooth driving and turning with a single joystick.*/
    LV=-Controller1.Axis3.position(percent)+Controller1.Axis1.position(percent);
    /*Controller1.Axis3.position(percent) reads the forward/backward joystick value.
    Controller1.Axis1.position(percent) reads the turning joystick value.
    The negative sign reverses the direction if needed.
    This formula combines forward/backward and turning inputs to control the left side motors, allowing smooth driving and turning with a single joystick.*/
    Move(LV,RV);
    /*This calls the Move function (in movement.cpp), passing the calculated left (LV) and right (RV) motor values.
    Move sets the speeds of the robot’s drive motors, allowing for arcade-style driving based on joystick input.
    It enables smooth and responsive control during the user control phase.*/
  }

return 0;
/*This function implements the main drive control logic for your robot:
Continuously reads joystick positions from Controller1 to calculate left (LV) and right (RV) motor speeds.
Uses Axis3 (forward/backward) and Axis1 (turning) for arcade drive control.
Calls Move(LV, RV) to update the robot’s motors.
*/

}


int V;//Variable for puncher speed
int ATask(void)
{
  /*Here’s what your ATask function does:
Continuously checks the state of ButtonR2 and ButtonR1 on the controller.
Calculates pow as 100 if ButtonR2 is pressed, -100 if ButtonR1 is pressed, 0 if neither or both are pressed.
Calls RunRoller(-pow) to control the intake roller motor.
The puncher control is commented out but would run if ButtonB is pressed.
*/
  double pow;
    while(true)
  {
    pow=((Controller1.ButtonR2.pressing()-Controller1.ButtonR1.pressing())*100);//Calculate intake power, if button pressed, button.pressing returns 1
    RunRoller(-pow);
    /*This calls the RunRoller function (in movement.cpp), passing -pow as the argument.
    RunRoller(-pow) sets the intake roller motor speed and direction, allowing the driver to control the roller 
    for intaking or outtaking game objects.*/
  
  //RunPuncher((Controller1.ButtonB.pressing())*100);
  }
  
  return 0;



}

int ButtonPressingX,XTaskActiv;
int ButtonPressingY,YTaskActiv;

int PTask(void)
{
    /*Here’s what your PTask function does:
    Implements toggle logic for the tilt and clamp mechanisms using the X and Y buttons on the controller.
    Ensures each action only triggers once per button press, not repeatedly while holding.
    Activates or deactivates the mechanisms based on the current state and button input.
    */
    while(true)
    {
      //Toggles Tilt
    if(XTaskActiv==0&&Controller1.ButtonX.pressing()&&ButtonPressingX==0)
    /*This condition checks if:
    The tilt mechanism (XTaskActiv) is currently inactive (0)
    The X button on the controller is being pressed
    The button press is new (ButtonPressingX==0), meaning it wasn’t pressed in the previous loop
    If all are true, it triggers the toggle logic to activate the tilt mechanism and ensures the action only happens once per press, 
    not repeatedly while holding the button.*/
    {
      ButtonPressingX=1;
      /*This sets the ButtonPressingX variable to 1 when the X button is pressed.
      It marks that the button press event has been registered, preventing the toggle action from repeating while the button is held down.
      This ensures the tilt mechanism only toggles once per press, not continuously while the button is held.*/
      XTaskActiv=1;
      /*This sets the XTaskActiv variable to 1, indicating that the tilt mechanism is now active.
      It is used in your toggle logic to track the current state of the tilt mechanism, so pressing the X button again will deactivate it.
      This helps ensure the tilt only toggles once per button press, not repeatedly while holding.*/
      Tilt.set(true);
      /*This sets the Tilt (defined in robot-config.cpp) pneumatic device to its "active" or "extended" position.
      It is used to activate the tilt mechanism on your robot, either during pre-autonomous setup or when toggled by the X button on the controller.
      This allows the robot to perform actions such as tilting a tray or mechanism as part of its operation.*/
    }

    else if(!Controller1.ButtonX.pressing())ButtonPressingX=0;
    /*This resets ButtonPressingX to 0 when the X button is released.
    It allows the toggle logic to detect a new button press in the next loop iteration, ensuring the tilt mechanism only toggles once per press
     and not repeatedly while holding the button.*/

    else if(XTaskActiv==1&&Controller1.ButtonX.pressing()&&ButtonPressingX==0)
    /*This condition checks if:
    The tilt mechanism (XTaskActiv) is currently active (1)
    The X button on the controller is being pressed
    The button press is new (ButtonPressingX==0), meaning it wasn’t pressed in the previous loop
    If all are true, it triggers the toggle logic to deactivate the tilt mechanism and ensures the action only happens once per press, 
    not repeatedly while holding the button.*/
    {
      ButtonPressingX=1;//Mark button as pressed.
      XTaskActiv=0;//Set tilt as inactive
      Tilt.set(false);//Deactivate tilt pneumatic
    }
    //----------------------
      //Toggles Clamp
/*This code implements toggle logic for the clamp mechanism using the Y button on the controller:
Toggles the clamp pneumatic device on or off with each press of the Y button.
Ensures the action only triggers once per button press, not repeatedly while holding.
Tracks the clamp state with YTaskActiv and the button state with ButtonPressingY.
*/
    if(YTaskActiv==0&&Controller1.ButtonY.pressing()&&ButtonPressingY==0)
    /*This condition checks if:
The clamp mechanism (YTaskActiv) is currently inactive (0)
The Y button on the controller is being pressed
The button press is new (ButtonPressingY==0), meaning it wasn’t pressed in the previous loop
If all are true, it triggers the toggle logic to activate the clamp mechanism and ensures the action only happens once per press, not repeatedly while holding the button.
*/
    {
      ButtonPressingY=1;//Mark button as pressed.
      YTaskActiv=1;//Set clamp as active
      Clamp.set(true);//Activate clamp pneumatic
    }

    else if(!Controller1.ButtonY.pressing())ButtonPressingY=0;//Reset button press once button is released

    else if(YTaskActiv==1&&Controller1.ButtonY.pressing()&&ButtonPressingY==0)
    /*This condition checks if:
The clamp mechanism (YTaskActiv) is currently active (1)
The Y button on the controller is being pressed
The button press is new (ButtonPressingY==0), meaning it wasn’t pressed in the previous loop
If all are true, it triggers the toggle logic to deactivate the clamp mechanism and ensures the action only happens once per press, not repeatedly while holding the button.
*/
    {
      ButtonPressingY=1;//Mark button as pressed.
      YTaskActiv=0;//Set clamp as inactive
      Clamp.set(false);//Deactivate clamp pneumatic
    }



  }
  return 0;
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/*Your usercontrol function currently creates new tasks for driving, intake, and pneumatics inside the main loop, 
which will repeatedly start new tasks every 20ms. This is inefficient and can cause performance issues or unexpected behavior.
Recommended fix:
Move the task creation outside the while (1) loop so each task is started only once when user control begins.
*/
void usercontrol(void) {
  EXIT=true;//Force Exit Autosel once drivercontrol began.
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    
     
    
    task Dtask=task(DriveTask);
    task Atask=task(ATask);
    task Ptask=task(PTask);
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//



  int main() {
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);//Set autonomous function to be called during the autonomous period.
  Competition.drivercontrol(usercontrol);//Set driver control function to be called during the driver control period.

  // Run the pre-autonomous function.
  pre_auton();
  
  

  // Prevent main from exiting with an infinite loop.
  /*Keeps the program running so it does not exit after setup.
The wait(100, msec); statement pauses the loop for 100 milliseconds each iteration, reducing CPU usage.
This is standard in VEX competition templates to ensure the robot remains responsive to field control signals throughout the match.*/
  while (true) {
    wait(100, msec);
  }
}