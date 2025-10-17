#include "screen_gui.hpp"
#include "vex.h"


void DisplayAutoSelector(void)
/*
Clears the V5 Brain screen.
Draws several rectangles in neon green (#39FF14) at specific positions, which are used as buttons or indicators 
for your autonomous routine selector.
Sets font, fill color, pen width, and pen color for consistent appearance.
This function is called to display the autonomous selection interface before a match.
*/

{

  Brain.Screen.clearScreen();

//auton selector
Brain.Screen.setFont(monoM);
Brain.Screen.setFillColor(black);
Brain.Screen.setCursor(1,1);
Brain.Screen.setPenWidth(3);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(1,25,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(375,25,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(1,100,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(375,100,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(1,175,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(375,175,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(187,5,100,50);

Brain.Screen.setPenColor("#39FF14");
Brain.Screen.drawRectangle(187,175,100,50);
}

void DisplayWords(void)
/*
Sets the pen color and font for the Brain screen.
Prints the names of the autonomous routines at specific screen positions.
These labels correspond to the options in your autonomous selector GUI, helping the user identify each routine.
*/
{
  Brain.Screen.setPenColor("#39FF14");
  Brain.Screen.setFont(monoM);

  // AutoSelectorVal==1
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print("L-Side-1");

  // AutoSelectorVal==2
  Brain.Screen.setCursor(7,3);
  Brain.Screen.print("L-Side-2");

  // AutoSelectorVal==3
    Brain.Screen.setCursor(11,3);
  Brain.Screen.print("N/A");

  // AutoSelectorVal==4
    Brain.Screen.setCursor(3,40);
  Brain.Screen.print("R-Side-1");

  // AutoSelectorVal==5
  Brain.Screen.setCursor(7,40);
  Brain.Screen.print("R-Side-2");

  // AutoSelectorVal==6
    Brain.Screen.setCursor(11,40);
  Brain.Screen.print("N/A");

  // AutoSelectorVal==7
      Brain.Screen.setCursor(11,22);
  Brain.Screen.print("Skills");
}

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
int AutoSelectorVal;//global variable for auton selector

void UpdateDynamic(void)
/*
Calls DisplayAutoSelector() and DisplayWords() to draw the base GUI and routine names.
Highlights and displays extra info for the currently selected autonomous routine (AutoSelectorVal).
Uses different rectangles, text, and formatting to show which routine is selected and provide details about it.
This function is called whenever you want to update the Brain screen with the current autonomous selection.
*/
{
  DisplayAutoSelector();
  DisplayWords();
  Brain.Screen.setFillColor("#39FF14");
Brain.Screen.setPenColor(black);
if(AutoSelectorVal==1){
Brain.Screen.drawRectangle(1,25,100,50);
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print("L-Side-1");

Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("HIGH BAR");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");

}

if(AutoSelectorVal==2){
Brain.Screen.drawRectangle(375,25,100,50);
    Brain.Screen.setCursor(3,40);
  Brain.Screen.print("L-Side-2");

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("LEFT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("HIGH AND LOW");
Brain.Screen.setFont(monoM);
  Brain.Screen.setFillColor("#39FF14");
}

if(AutoSelectorVal==3){
  Brain.Screen.drawRectangle(1,100,100,50);
  Brain.Screen.setCursor(7,3);
  Brain.Screen.print("N/A");

Brain.Screen.setFillColor(black);

    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("NOT DEFINED");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("NOT DEFINED");
Brain.Screen.setFont(monoM);  
  Brain.Screen.setFillColor("#39FF14");
}

if(AutoSelectorVal==4){
Brain.Screen.drawRectangle(375,100,100,50);
  Brain.Screen.setCursor(7,40);
  Brain.Screen.print("R-Side-1");

Brain.Screen.setFillColor(black);

  Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("RIGHT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("HIGH BAR");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(AutoSelectorVal==5){
  Brain.Screen.drawRectangle(1,175,100,50);
      Brain.Screen.setCursor(11,3);
  Brain.Screen.print("R-Side-2");

Brain.Screen.setFillColor(black);
    Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("RIGHT SIDE");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("HIGH AND LOW");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

}

if(AutoSelectorVal==6){
Brain.Screen.drawRectangle(375,175,175,50);
Brain.Screen.setCursor(11,40);
Brain.Screen.print("N/A");
Brain.Screen.setFillColor(black);
Brain.Screen.setFont(monoXL);
Brain.Screen.setPenColor("#39FF14");
Brain.Screen.setCursor(3,10);
Brain.Screen.print("NOT DEFINED");
Brain.Screen.setCursor(4,10);
Brain.Screen.print("NOT DEFINED");
Brain.Screen.setFont(monoM); 
  Brain.Screen.setFillColor("#39FF14");

  }

if(AutoSelectorVal==7){
  Brain.Screen.drawRectangle(187,175,100,50);
  Brain.Screen.setCursor(11,22);
  Brain.Screen.print("Skills");

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

}
