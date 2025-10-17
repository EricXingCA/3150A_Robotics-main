#include "vex.h"
#include <math.h>

#include <iostream>
/** Gets the distance travelled in a linear path by the robot
 * 
 * @param degreesTravelled the degrees travelled
 * @return the distance travelled by the motors, in inches
 */
double get_dist_travelled(double degreesTravelled) {
    std::cout << "gear ratio " << wheelToMotorRatio << M_PI*wheelDiam << std::endl;
    /*Explanation:
Prints the text "gear ratio " followed by the value of wheelToMotorRatio, then the value of M_PI * wheelDiam, and then a newline.
std::cout is used for console output in C++.
M_PI is the mathematical constant π (pi).
wheelDiam is your wheel diameter variable.
This is a debug statement to help you see the current gear ratio and wheel circumference (π × diameter) when get_dist_travelled is called.
It helps verify that your calculations use the correct values.
    */
    std::cout << degreesTravelled * wheelToMotorRatio / 360 * (M_PI*wheelDiam) << std::endl;
    return fabs(degreesTravelled * wheelToMotorRatio / 360 * (M_PI*wheelDiam));
}