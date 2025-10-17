#ifndef MOVEMENT_H //checks if the macro MOVEMENT_H has not been defined yet.
#define MOVEMENT_H //defines the macro if it hasn’t been defined.
/*This prevents the contents of the header file from being included multiple times during compilation, avoiding redefinition errors.
It is a standard practice in C/C++ header files.*/

extern int turninverse;//The extern keyword tells the compiler that these variables are defined elsewhere (usually in a .cpp file).
extern int JB;
extern int PB;
extern int PX;
extern int JX;

//This code defines a structure named ChassisDataSet to hold data related to the robot's chassis movement:
struct ChassisDataSet{
  int Left;
  int Right;
  double Avg;   // Average between left and right of the drive train
  int Diff;     // Left - Right
  double HDG;   // Robot heading
};

//This code defines a structure named PIDDataSet to hold the PID controller parameters:
struct PIDDataSet{
  double kp;// Proportional gain
  double ki;// Integral gain
  double kd;// Derivative gain
};

extern void Zeroing(bool dist, bool HDG);
extern ChassisDataSet ChassisUpdate();
/*This declares the function ChassisUpdate() as returning a ChassisDataSet structure.
The extern keyword tells the compiler the function is defined elsewhere (usually in a .cpp file).
When you call ChassisUpdate(), it will return a ChassisDataSet containing updated drive train and heading data.
*/
extern void Move(int left, int right);
extern void BStop();//Braking Stop
extern void CStop();//Coasting Stop
extern void RunRoller(int val);
extern int PrevE;
extern void MoveEncoderPID(PIDDataSet KVals, int Speed, double dist,double AccT, double ABSHDG,bool brake);
extern void TurnMaxTimePID(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
void MaxTimePIDTurnOneSide(PIDDataSet KVals,double DeltaAngle,double TE, bool brake);
void MoveTimePID(PIDDataSet KVals, int Speed, double TE,double AccT,double ABSHDG, bool brake);
/*In C++, function declarations without extern are already treated as external by default.
extern is optional for function prototypes, but required for variables.
Using extern for functions is optional in C++ headers.
For clarity and consistency, you can use extern, but it is not necessary for function declarations.
*/


#endif //This ends the include guard started with #ifndef MOVEMENT_H and #define MOVEMENT_H at the top of your header file.