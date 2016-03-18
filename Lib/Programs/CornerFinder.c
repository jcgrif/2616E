#pragma config(Sensor, in1,    gyroRadar,      sensorGyro)
#pragma config(Sensor, dgtl1,  rangeRadar,     sensorSONAR_cm)
#pragma config(Motor,  port5,           motorRadar,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This is a test for the ultrasonic sensor.
// It will take in distances for all possible of the 3,600 values of the gyroscope
// -> map them to an array, and *try* to determine if there's corners
//    -> Threshold will need to be modified to correctly determine a corner
//      versus a wall's edge

// "radar" is used to describe the rotating piece with the sensor on it

int threshold = 25; // How much of a gap is considered a reasonable change
int checkWith = 1; // How many 1/10 degrees to check change
int radarMovementSpeed = 60; // Max of 127, minimum of 1 (but realisticly, above 20)
short distances[3600]; // Array to store a distance every 1/10 degree
int initCheckTime = 100; // Ms to run the intital check for the gyro
int checkTime = 25; // Ms to check the ultrasonic sensor. Pretty sure below 20 is too fast
// for a cortex
bool includeRadarSetupDelay = true; // Includes a 6 second delay to clear the field before
// the program starts scanning with it's radar. Good idea to disable if you're remotely starting,
// good idea to enable if you're manually turning it on

// ######################
// # Sensor interaction #
// ######################
// These are mainly here incase we want to change how we read the sensor.
// That way, we don't need to search through the code and change every read.

// Returns abs of current radar gyro sensor's value
short getGyroValue() {
	// Abs of the value so we always get positives
	return abs(SensorValue[gyroRadar]);
}

// Returns the current radar range sensor's value
short getRadarValue() {
	return SensorValue[rangeRadar];
}

// ##########
// # Output #
// ##########

// Outputs all keys and values for the distances array
void printValues() {
	writeDebugStreamLine("---- Printing all degrees! ----");
	for(short degree = 0; 3600; degree++)
	{
		short distance = distances[degree];
		if (distance == NULL || distance <= 0)
			writeDebugStreamLine("Degree: %i. No distance set or less than/equal to 0.",degree);
		else
			writeDebugStreamLine("Degree: %i. Distance: %i.",degree,distance);
	}
	writeDebugStreamLine("---- End of degrees! ----");
}

// Clears whole LCD
void clearLCD() {
	clearLCDLine(0);
	clearLCDLine(1);
}

// Basically the same as printValues(), but only printing those missing a value
// If this prints out a lot, you should probably move slower or fix something else.
// The goal is to have no naked degrees
void printNakedValues() {
	writeDebugStreamLine("---- Printing all naked degrees! ----");
	for(short degree = 0; 3600; degree++)
	{
		short distance = distances[degree];
		if (distance == NULL || distance < 0)
			writeDebugStreamLine("Degree: %i. No distance set or less than 0.",degree);
	}
	writeDebugStreamLine("---- End of naked degrees! ----");
}

// ##########################################
// # Methods for interacting with distances #
// ##########################################

// Checks if posOne is greater or less than pos two and returns it's results
// True for moving positive, false for moving negative
bool isMovingPositive(short posOne, short posTwo) {
	if (posOne < posTwo) // Position one is greater than pos two, moving up.
		return false;
	else // Position one is less than pos two, moving down.
		return true;
}

// ##################
// # Radar movement #
// ##################

// Sets the radar to spinning it's normal direction
void startRadar() {
	motor[motorRadar] = radarMovementSpeed;
}

// Sets the radar to spinning reverse it's normal direction
void moveRadarReverse() {
	motor[motorRadar] = radarMovementSpeed * -1;
}

// Stops the radar's movement
void stopRadar() {
	motor[motorRadar] = 0;
}

// ################
// # Main control #
// ################
task printSensorValues() {
	clearLCD();
	// Simply displaying number after text to avoid the annoyance
	// of concatenating a number to a string
	displayLCDString(0,0,"RNG:");
	displayLCDNumber(0,4,getRadarValue());
	displayLCDString(1,0,"GYRO:");
	displayLCDNumber(1,5,getRadarValue());
}

task main()
{
	bLCDBacklight = true;
	clearLCD();
	displayLCDString(0,0,"Gyro setup");
	displayLCDCenteredString(1,"DONT TOUCH ROBOT");

	// Give sensors like the gyro time to calibrate themselves,
	// and give pretty ellipse on the lcd
	wait1Msec(500);
	displayLCDString(0,10,".");
	wait1Msec(500);
	displayLCDString(0,11,".");
	wait1Msec(500);
	displayLCDString(0,12,".");
	wait1Msec(500);

	// If we want this delay...
	if (includeRadarSetupDelay) {
		clearLCD();
		displayLCDString(0,0,"Radar setup");
		displayLCDCenteredString(1,"CLEAR THE FIELD");

		// Give people time to clear the field
		// and give pretty ellipse on the lcd
		wait1Msec(1500);
		displayLCDString(0,11,".");
		wait1Msec(1500);
		displayLCDString(0,12,".");
		wait1Msec(1500);
		displayLCDString(0,13,".");
		wait1Msec(1500);
	}

	clearLCD();
	displayLCDString(0,0,"Scanning field");
	// This is the loop that gathers the values. It runs every checkTime ms,
	// and checks the current gyro degree. It then sets the distance for distance[gyroDegree]
	// if one does not already exist
	short lastPos = -1;
	while (true) {
		// Check if we've done a full rotation. If so, break the loop
		short gyroPos = getGyroValue();
		// If we're above or at our start pos
		if (gyroPos >= lastPos) {
			// If we've already gone to 0 and up again
			lastPos = gyroPos;
			} else { // We're back to 0!
			stopRadar();
			break;
		}

		// Check if this degree has a distance yet. If not, set it
		short thisValue = distances[getGyroValue()]; // Get the current value for this degree
		if (thisValue == NULL || thisValue <= 0) { // If this value hasn't been properly set
			distances[getGyroValue()] = getRadarValue();
			clearLCDLine(1);
			displayLCDCenteredString(1,"->");
			displayLCDNumber(1,0,getGyroValue());
			displayLCDNumber(1,10,getRadarValue());
		}

		// Delay so we don't read too fast
		wait1Msec(checkTime);
	}

	// Analyze the data we gathered and get the corner's degrees from us
	// TODO: Actually analyze the data for corners. Waiting to check the data returned before doing this
	short currentPos = startPos; // Used to track our current pos since we're not using the real gyro anymore

	for (short i = startPos; i < 3600; i++) { // Read data from startPos -> end of array

	}
	for (short i = 0; i < startPos+1; i++) { // Read data from 0 -> startPos

	}

	// Print out our results
	printValues();
	printNakedValues();

	// Give user control and print sensor values so they can check the data to real life
	// 8L -> Turn left, 8R -> Turn right (Radar)
	startTask(printSensorValues);
	while (true) {
		if (vexRT[Btn8R]) {
			startRadar();
			} else if (vexRT[Btn8L]) {
			moveRadarReverse();
			} else {
			stopRadar();
		}
	}
}
