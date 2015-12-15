#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   // Main competition background code
#include "sensors.c" // Sensor methods
#include "lcd.c" // LCD methods

// ##################
// # Pre Autonomous #
// ##################

void pre_auton()
{
	bLCDBacklight = true;
}

// ##############
// # Autonomous #
// ##############

task autonomous()
{
	// TODO: Make me :D
}

// ################
// # User Control #
// ################

task usercontrol()
{
	// Main loop
	while(true)
	{
		// Check lcd buttons
		if (nLCDButtons == 1) { // Left button pressed
			lcdLstPage();
			} else if (nLCDButtons == 2) { // Center button pressed
			lcdHome();
			} else if (nLCDButtons == 4) { // Right button pressed
			lcdNextPage();
		}
		break; // TODO: Remove
	}
}
