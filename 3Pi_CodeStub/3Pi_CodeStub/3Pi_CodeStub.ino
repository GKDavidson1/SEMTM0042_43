/******************************************

	______      _           _   _              
	| ___ \    | |         | | (_)             
	| |_/ /___ | |__   ___ | |_ _  ___ ___     
	|    // _ \| '_ \ / _ \| __| |/ __/ __|    
	| |\ \ (_) | |_) | (_) | |_| | (__\__ \    
	\_| \_\___/|_.__/ \___/ \__|_|\___|___/    
											   
											   
	 _____      _                              
	/  ___|    (_)                       ___   
	\ `--.  ___ _  ___ _ __   ___ ___   ( _ )  
	 `--. \/ __| |/ _ \ '_ \ / __/ _ \  / _ \/\
	/\__/ / (__| |  __/ | | | (_|  __/ | (_>  <
	\____/ \___|_|\___|_| |_|\___\___|  \___/\/
											   
											   
	 _____           _                         
	/  ___|         | |                        
	\ `--. _   _ ___| |_ ___ _ __ ___  ___     
	 `--. \ | | / __| __/ _ \ '_ ` _ \/ __|    
	/\__/ / |_| \__ \ ||  __/ | | | | \__ \    
	\____/ \__, |___/\__\___|_| |_| |_|___/    
			__/ |                              
		   |___/                               


 SEMTM0042/43: University of Bristol.
 https://github.com/paulodowd/SEMTM0042_43
*******************************************/


// These #include commands essentially "copy and paste" 
// the above .h files (tabs above) into your code here.

// Labsheet 1: Build a class to operate your motors.
#include "Motors.h"         

// Labsheet 1: Tune PID to control wheel speed.
#include "PID.h"            

// Labsheet 2: Build a class to read the line sensors.
#include "LineSensors.h"    

// Labsheet 2: Operate the magnetometer to detect the 
//             puck.  You will need to follow the steps
//             to install the software library.
//#include "Magnetometer.h" // Labsheet 2 

// Labsheet 3: Calibrate and use kinematics to allow 
//             your robot to turn and travel between
//             locations.
#include "Kinematics.h"  

// Encoders.h does not need modifying.
#include "Encoders.h"     // For encoder counts


// If you want to use one of the Display modules for
// your robot, please read Supplementary Labsheet 4.
// You can only use one of the following.  Uncomment
// the correct one for your display module.  If you
// have not followed Supplementary Labsheet 4, these 
// will cause a compile error in your code.  

// Uncomment the next two lines if you will use
// the GREEN display with 2 rows of pins.
//#include "lcd.h"
//LCD_c display(0, 1, 14, 17, 13, 30);

// Uncomment the next two lines if you will use
// the BLUE display with 1 row of pins.
//#include "oled.h"
//OLED_c display(1, 30, 0, 17, 13);


// Used for Labsheet 0. Defines which pin the buzzer
// is attached to. #define works like a 
// find-and-replace through your code.
// See Labsheet 0.
#define BUZZER_PIN 6

// Instance of a class to operate motors.
// A class is like a template, and we name
// an "instance" to use.
// You can recognise a class type in the
// code by the convention of "_c"
// You will need to complete the class.
// See Labsheet 1.
Motors_c motors;    

// Instance of a class to operate the line
// sensors to measure the surface reflectance.
// You will need to complete the class.
// See Labsheet 2.
LineSensors_c line_sensors; 

// Instance of a class to operate the magnetometer.
// Completing the class is a later exercise in 
// Labsheet 2, so you can leave this commented
// out.
// See Labsheet 2.
//Magnetometer_c magnetometer;

// Instance of a class to estimate the pose
// of the robot.  You will need to calibrate
// this, and potentially improve it.
// See Labsheet 3.
Kinematics_c pose; 

// The setup() function runs only once when the
// robot is powered up (either by plugging in
// the USB cable, or activating the motor power.
// Use this function to do "once only" setup 
// and configuration of your robot.
void setup() {

  // Setup up the buzzer as an output for
  // This is used in Labsheet 0
  pinMode( BUZZER_PIN, OUTPUT );

  // Setup motors.  This is calling a function
  // from within the Motors_c class. You can 
  // review this inside Motors.h
  // Complete by working through Labsheet 1.
  motors.initialise();

  // Setup the line sensors.  This is calling a 
  // function from within the LineSensors_c 
  // class. You can review this inside 
  // LineSensors.h.  
  // Complete by working through Labsheet 2.
  line_sensors.initialiseForADC();

  // These two functions are in encoders.h and
  // they activate the encoder sensors to 
  // measure the wheel rotation.  You do not 
  // need to change or update these.
  // These are used in Labsheet 4.
  // Encoder counts are counted automatically.
  setupEncoder0();
  setupEncoder1();

  // Setup the pose (kinematics). This is calling 
  // a function within the Kinematics_c class.
  // You can review this within Kinematics.h
  // This is used in Labsheet 4.
  pose.initialise(0, 0, 0);

  // Activates the Serial port, and the delay 
  // is used to wait for the connection to be
  // established.
  Serial.begin(9600);
  delay(2000);
  Serial.println(" *** READY *** ");
  
  // If you are using an OLED or LCD display, 
  // the following will set up a count down 
  // timer to be displayed.
  // display.setMaxMinutes(4);
  // display.startStopwatch();

}


// put your main code here, to run repeatedly:
void loop() {

  // Used for Labsheet 0
  analogWrite( BUZZER_PIN, 120 ); // on
  delay(5);
  analogWrite( BUZZER_PIN, 0 ); // off
  delay(5);

  // The below is used for Labsheet 1.
  // using .setPWM() on `motors` means that we
  // are calling a function defined within 
  // "motors".  "motors" is just the name we 
  // have given to an instance (a copy) of the
  // class (i.e the class is like a template).  
  //
  // Here we are sending to the "setPWM()" function
  // inside the Motors_c class instance "motors"
  // We pass setPWM the arguments (values) +25 and 
  // 0.  This should cause your robot to rotate 
  // around 1 wheel. You will need to review 
  // Motors.h and fix the code to for other motor 
  // control to work properly.
  // See Labsheet 1
  motors.setPWM( 25.0, 0.0 );


  // If you are using an OLED or LCD display, 
  // the following will update the display with
  // the time remaining in seconds. You can also 
  // check the return value to see if the time 
  // has finished.
  //display.timeRemaining();
  

  // Do nothing for half a second
  delay(500);
}
