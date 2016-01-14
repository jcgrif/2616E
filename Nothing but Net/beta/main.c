#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    powerExpander,  sensorNone)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motorBar,      tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           motorFrontLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motorBackLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           motorFrontRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           motorBackRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           motorLauncherOne, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motorLauncherTwo, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           motorLauncherThree, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           motorLauncherFour, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,           ,             tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   // Main competition background code
#include "bar.c" // Launcher bar control
#include "sensors.c" // Sensor methods
#include "autonomous.c" // Autonomous handler
#include "lcd.c" // LCD methods
#include "controller.c" // Controller methods

// ##################
// # Pre Autonomous #
// ##################

void pre_auton()
{
	bLCDBacklight = true;
	resetBar();
}

// ##############
// # Autonomous #
// ##############

task autonomous()
{
	runAutonomous();
}

// ################
// # User Control #
// ################

task usercontrol()
{
	// Hold time currently not used
	//startTask( countHoldTime );
	startTask( lcdRunAutoRefresh );
	// Main loop
	bool buttonReleased = true;
	int highestCombination = 0;
	while(true)
	{
		// LCD Button Handling
		if (nLCDButtons == 0) { // A button wasn't pressed
			if (buttonReleased == false) {
				// Button was pressed then released, calculate what to do
				if (highestCombination == 1) { // Left button pressed
					lcdLastPage();
					buttonReleased = false;
				}
				else
					if (highestCombination == 2) { // Center button pressed
					lcdHome();
					buttonReleased = false;
				}
				else
					if (highestCombination == 4) { // Right button pressed
					lcdNextPage();
					buttonReleased = false;
				}
				else
					if (highestCombination == 3) { // Left & center pressed
						lcdNext();
				}
				else
					if (highestCombination == 6) { // Right & center pressed
						lcdBack();
				}
				buttonReleased = true;
				highestCombination = 0;
			} // Else: Nothing was pressed
		}
		else // A button was pressed
		{
			lcdResetAutoRefresh();
			if (buttonReleased) {
				buttonReleased = false;
				lcdResetHoldTime();
			}

			if (nLCDButtons > highestCombination) {
				highestCombination = nLCDButtons;
			}
		}

		// Controller
		runCalculation();
	}
}
