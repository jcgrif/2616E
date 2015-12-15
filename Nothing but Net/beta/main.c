#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
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
	startTask( lcdRunAutoRefresh );
	// Main loop
	bool buttonReleased = true;
	while(true)
	{
		// Check lcd buttons
		if (nLCDButtons == 0) { // Left button pressed
			buttonReleased = true;
		} else
		if (buttonReleased) {
			lcdResetAutoRefresh();
			if (nLCDButtons == 1) { // Left button pressed
				lcdLastPage();
				buttonReleased = false;
				} else if (nLCDButtons == 2) { // Center button pressed
				lcdHome();
				buttonReleased = false;
				} else if (nLCDButtons == 4) { // Right button pressed
				lcdNextPage();
				buttonReleased = false;
			}
		}
	}
}
