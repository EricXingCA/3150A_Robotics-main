#include "vex.h"//Main VEX Robotics API
#include "math.h"//Standard math functions
#include "screen_gui.hpp"//Custom screen GUI functions
#include "helper_functions.hpp"//Additional helper functions
#include "movement.hpp"//Movement-related declarations and structures

#include <iostream>//For debugging
/*include necessary headers to ensures your file has access to VEX hardware, 
math operations, GUI, helper, and movement functions/structures.*/

using namespace vex;

int turninverse=-1;//change this to -1 if turning is inversed

int JB;//Intake Button
int PB;//Puncher Button
int PX;//Puncher Extend
int JX;//Junction X

//General Sect;
//This section includes all general codes for drive and auto


/** Resets the robot's drive train and inertial sensor
If dist is true, it resets the position of all drive motors (left and right, front/middle/back).
If HDG is true, it sets the gyro sensor heading to zero.
Use this function before autonomous or user control routines to ensure your robot starts from a known reference point.
 */
void Zeroing(bool dist, bool HDG)
{
  if(dist){
  LF.resetPosition();
  LM.resetPosition();
  LB.resetPosition();
  RF.resetPosition();
  RM.resetPosition();
  RB.resetPosition();
  }
  if(HDG){
    Gyro.setHeading(0,degrees);
  }
}

//This function updates and returns the robot’s drive train and heading data:
/*Creates a ChassisDataSet structure to hold drive train and heading data.
Calculates the average position for left and right drive motors, converts to distance, and stores in Left and Right.
Computes the average (Avg) and difference (Diff) between left and right.
Gets the current gyro heading (HDG).
Returns the structure for use elsewhere in your code.
*/

ChassisDataSet ChassisUpdate()
/*This is a function that collects and returns the robot’s current drive train and heading data in a single structure (ChassisDataSet).
How it works:
It calculates the average position of the left and right drive motors, converts those to distance traveled.
It computes the average and difference between left and right distances.
It reads the current gyro heading.
It returns all this data in a ChassisDataSet struct.
*/
{
  ChassisDataSet CDS;
  /*This defines a variable named CDS of type ChassisDataSet.

It allocates memory for the structure and allows you to store and access drive train and heading data using 
its members (Left, Right, Avg, Diff, HDG).
You can use CDS to hold and manipulate movement data within your function.
*/
  CDS.Left=get_dist_travelled((LF.position(degrees)+LM.position(degrees)+LB.position(degrees))/3.0);
  /*This calculates the average position of the left drive motors and converts it to distance.
  get_dist_travelled is defined in helper_functions.hpp
  CDS.Left accesses the Left member of the CDS variable, which is of type ChassisDataSet.
  */
  CDS.Right=get_dist_travelled((RF.position(degrees)+RM.position(degrees)+RB.position(degrees))/3.0);
  CDS.Avg=(CDS.Left+CDS.Right)/2;
  CDS.Diff=CDS.Left-CDS.Right;
  CDS.HDG=Gyro.heading(degrees);

  return CDS;
}

void Move(int left, int right)
/* variable left: value from main.cpp LV;
   variable right: value from main.cpp RV;
   This function sets the speed of the left and right motors based on the input values.
   The left motors (LF, LM, LB) are set to the 'left' value, and the right motors (RF, RM, RB) are set to the 'right' value.
   The speed is scaled to a voltage range by multiplying by 11/100 (assuming input is from -100 to 100).
   The motors are set to spin forward at the calculated voltage.
   The max torque for each motor is set to 100% to ensure they can deliver full power.
*/
{
LF.setMaxTorque(100,percent);
LM.setMaxTorque(100,percent);
LB.setMaxTorque(100,percent);
RF.setMaxTorque(100,percent);
RM.setMaxTorque(100,percent);
RB.setMaxTorque(100,percent);

LF.spin(forward,(double)left/100.0*11,volt);
LM.spin(forward,(double)left/100.0*11,volt);
LB.spin(forward,(double)left/100.0*11,volt);
RF.spin(forward,(double)right/100.0*11,volt);
RM.spin(forward,(double)right/100.0*11,volt);
RB.spin(forward,(double)right/100.0*11,volt);
}

void BStop()
{
LF.setStopping(brake);
LM.setStopping(brake);
LB.setStopping(brake);
RF.setStopping(brake);
RM.setStopping(brake);
RB.setStopping(brake);

LF.stop();
LM.stop();
LB.stop();
RF.stop();
RM.stop();
RB.stop();
}

void CStop()
{
LF.setStopping(coast);
LM.setStopping(coast);
LB.setStopping(coast);
RF.setStopping(coast);
RM.setStopping(coast);
RB.setStopping(coast);

LF.stop();
LM.stop();
LB.stop();
RF.stop();
RM.stop();
RB.stop();
}




void RunRoller(int val)
/* variable val: value from main.cpp pow;
   This function sets the speed of the roller motor based on the input value.
   If R1 is pressed, val=-100, the roller spins forward (intake) at the specified speed.
   If R2 is pressed, val=100, the roller spins in reverse (outtake) at the specified speed.
   If R1 and R2 are not pressed, val=0, the roller stops.
   If R1 and R2 are both pressed, val=0, the roller stops to prevent conflicting commands.
   */
{
Roller.setMaxTorque(100,percent);
Roller.spin(forward,(double)val/100.0*12,volt);
}

int PrevE;//Error at t-1

/** Moves the robot forward or backward. Negative speed moves
 * the robot forward. Positive value moves it backward. (Ik it's fucked up)
 * @param KVals the PID constants
 * @param Speed the speed, from -100 to 100
 * @param dist distance travelled, in inches
 * @param AccT time to max speed (s)
 * @param ABSHDG absolute heading of the robot
 * @param brake Brake at end, or coast
 */
void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist,double AccT, double ABSHDG,bool brake){
  /*Here’s what this function does:
Moves the robot a set distance using PID control for heading correction.
Smoothly accelerates to target speed.
Continuously updates sensor values and applies PID correction.
Stops with brake or coast at the end, based on the brake parameter.
  */
  double CSpeed=0;//Current Speed
  Zeroing(true,false);//Reset encoders, not gyro
/*Use this before starting a movement or PID routine to ensure your drive encoders are zeroed,
 but your heading remains unchanged. This helps maintain accurate distance tracking for autonomous actions.*/
  ChassisDataSet SensorVals;//Define a variable named SensorVals of type ChassisDataSet.
  SensorVals=ChassisUpdate();
  double PVal=0;//Proportional value
  double IVal=0;//Integral value
  double DVal=0;//Derivative value
  double LGV=0;//define local gyro variable.
  PrevE=0;
  double Correction=0;
  Brain.Screen.clearScreen();

  while(fabs(SensorVals.Avg) <= fabs(dist))
  /*This ensures the robot keeps moving until it has traveled the desired distance, regardless of direction.*/
  {
    //std::cout << SensorVals.Avg << " " << dist << std::endl;
if(fabs(CSpeed)<fabs((double)Speed))
/*Checks if the absolute value of the current speed (CSpeed) is less than the absolute value of the target speed (Speed).
If true, the code inside the if block will increment CSpeed to gradually accelerate the robot up to the desired speed.
This is commonly used for smooth acceleration in PID movement routines, preventing sudden jumps in motor power.*/
{
  CSpeed+=Speed/AccT*0.02;
/*Example:
If Speed = 100, AccT = 2 (seconds), then:

Speed / AccT = 50 (units per second)
Each loop: CSpeed += 50 * 0.02 = 1
So, every 20ms, CSpeed increases by 1, reaching 100 after 2 seconds.*/
}

  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-ABSHDG;//Calculate the difference between current heading and target absolute heading.
  if(LGV>180) LGV=LGV-360;
  /*This code normalizes the heading error (LGV) to the range [-180, 180] degrees.

If the difference between the current heading and the target heading (LGV) is greater than 180 degrees, subtracting 360 brings it into the shortest rotation direction.
This prevents the robot from trying to turn almost a full circle when a small turn in the opposite direction would reach the target heading faster.
Usage:
Common in robotics to ensure heading corrections always use the shortest path.
  */
  PVal=KVals.kp*LGV;//responds to the current heading error
  IVal=IVal+KVals.ki*LGV*0.02;//accumulates the error over time for long-term correction (multiplied by loop interval 0.02 seconds).
  DVal=KVals.kd*(LGV-PrevE);//reacts to how quickly the error is changing (difference between current and previous error).

  Correction=PVal+IVal+DVal/0.02;//Total correction value from PID components

  Move(CSpeed-Correction,CSpeed+Correction);//Apply the calculated speed and correction
  PrevE=LGV;//Store current error for next loop's derivative calculation
  wait(20, msec);//Wait for 20 milliseconds before the next loop iteration
  }
  if(brake){
    BStop();
    wait(120,msec);
  }
  else CStop();
}

/** Moves the robot forward or backward. Negative speed moves
 * the robot forward. Positive value moves it backward. (Ik it's fucked up)
 * @param KVals the PID constants
 * @param DeltaAngle the absolute heading to turn to
 * @param TE time to calculate turn (not time to turn)
 * @param brake Brake at end, or coast
 */

 void TurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake){
/*This function turns the robot to a specific heading (DeltaAngle) using PID control, for a maximum time (TE seconds).
It uses the PID constants from KVals to calculate the correction needed to reach the target heading.
The loop runs until the specified time elapses, updating the correction and applying it to the motors each cycle.
At the end, it either brakes or coasts, depending on the brake parameter.
*/
  double CSpeed=0;//Current Speed
  Zeroing(true,false);//Reset encoders, not gyro
  ChassisDataSet SensorVals;
  /*This defines a variable named SensorVals of type ChassisDataSet.

It allocates memory for the structure and allows you to store and access drive train and heading data using its members (Left, Right, Avg, Diff, HDG).
You can use SensorVals to hold and manipulate movement data within your function, typically by assigning it the result of ChassisUpdate():
  */
  SensorVals=ChassisUpdate();
  /*This calls the ChassisUpdate() function and assigns its returned ChassisDataSet structure to the variable SensorVals.
SensorVals now contains updated drive train and heading data (Left, Right, Avg, Diff, HDG).
You can use SensorVals to access the robot’s current movement and orientation information for control and feedback in your PID functions.
  */
  double PVal=0;//Proportional value
  double IVal=0;//Integral value
  double DVal=0;//Derivative value
  double LGV=0;//Local gyro variable
  PrevE=0;//Previous error
  double Correction=0;//Correction value
  Brain.Timer.reset();//Reset the timer to zero before starting the turn

  while(Brain.Timer.value() <= TE)//Run the loop until the elapsed time exceeds the specified time limit (TE)
  {
  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-DeltaAngle;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(CSpeed-Correction,CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(180,msec);}
  else CStop();
}

void MaxTimePIDTurnOneSide(PIDDataSet KVals,double DeltaAngle,double TE, bool brake)//Turn using one side of the chassis
{
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0;
  double LGV=0;
  PrevE=0;
  double Correction=0;
  double LV,RV;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
  SensorVals=ChassisUpdate();
  LGV=SensorVals.HDG-DeltaAngle;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;
LV=-CSpeed+Correction;
RV=-CSpeed-Correction;
if(LV>=0)LV=0;
if(RV>=0)RV=0;
  Move(LV,RV);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(200,msec);}
  else CStop();
}


void MoveTimePID(PIDDataSet KVals, int Speed, double TE,double AccT,double ABSHDG, bool brake){
  double CSpeed=0;
  Zeroing(true,false);
  ChassisDataSet SensorVals;
  SensorVals=ChassisUpdate();
  double PVal=0;
  double IVal=0;
  double DVal=0;
  double LGV=0;
  PrevE=0;
  double Correction=0;
  Brain.Timer.reset();

  while(Brain.Timer.value() <= TE)
  {
if(fabs(CSpeed)<fabs((double)Speed))
{
  CSpeed+=Speed/AccT*0.02;
}

  SensorVals=ChassisUpdate();
    LGV=SensorVals.HDG-ABSHDG;
  if(LGV>180) LGV=LGV-360;
  PVal=KVals.kp*LGV;
  IVal=IVal+KVals.ki*LGV*0.02;
  DVal=KVals.kd*(LGV-PrevE);

  Correction=PVal+IVal+DVal/0.02;

  Move(-CSpeed-Correction,-CSpeed+Correction);
  PrevE=LGV;
  wait(20, msec);
  }
  if(brake){BStop();
  wait(200,msec);}
  else CStop();
}
