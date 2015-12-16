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
	int highestCombination = 0;
	while(true)
	{
		// Check lcd buttons
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
				buttonReleased = true;
				highestCombination = 0;
			} // Else: Nothing was pressed
		}
		else // A button was pressed
		{
			lcdResetAutoRefresh();
			if (buttonReleased) {
				buttonReleased = false;
			}

			if (nLCDButtons > highestCombination) {
				highestCombination = nLCDButtons;
			}
		}
	}
}
