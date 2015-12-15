#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   // Main competition background code
#include "sensors.c" // Sensor methods

// ##################
// # Pre Autonomous #
// ##################

void pre_auton()
{

}

// ##############
// # Autonomous #
// ##############

task autonomous()
{

}

// ################
// # User Control #
// ################

task usercontrol()
{
	// Main loop
	while(true)
	{
		updateBatteryIndicators(); // Update battery lights
		break; // TODO: Remove
	}
}
