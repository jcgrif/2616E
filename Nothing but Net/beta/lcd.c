// Page vars
int currentPage = 1;
int minPage = 1;
int maxPage = 3;

// Data vars
int secondsSinceRefresh = 0;
float holdDownTime = 0.0;

// Menu vars
int autoMode = getAutonomousMode();
int autoMin = 1;
int autoMax = 3;

// TODO: Create task to update page every 5 seconds if page not changed?
void lcdUpdatePage()
{
	clearLCDLine(0);
	clearLCDLine(1);
	// Pages are defined here. Messy, but it works.

	// General status
	if (currentPage == 1) {
		displayLCDCenteredString(0,"2616E Equinox");
		if ((getBackupBatteryStatus() >= 2) || (getCortexBatteryStatus() >= 2) || (getExpanderBatteryStatus() >= 2)) { // Battery page needs attention
			displayLCDChar(1,0,'!');
		}
		displayLCDString(1,1,"Bat");
	}

	// Battery status
	else if (currentPage == 2) {
		displayLCDString(0,0,"BatStat|");
		if (getBackupBatteryStatus() >= 2) { // Backup bat needs attention
			displayLCDChar(0,8,'!');
		}
		// Nasty string handling for backup status
		string backupNumber;
		string backupText = "Bck:";
		sprintf(backupNumber, "%i", ((int) getBackupBatteryLevel()));
		strcat(backupText,backupNumber);
		// Displaying backup status
		displayLCDString(0,9,backupText);
		if (getCortexBatteryStatus() >= 2) { // Cortex bat needs attention
			displayLCDChar(1,0,'!');
		}
		// Nasty string handling for cortex status
		string cortexNumber;
		string cortexText = "Ctx:";
		sprintf(cortexNumber, "%i", ((int) getCortexBatteryLevel()));
		strcat(cortexText,cortexNumber);
		// Displaying cortex status
		displayLCDString(1,1,cortexText);
		if (getExpanderBatteryStatus() >= 2) { // Expander bat needs attention
			displayLCDChar(1,8,'!');
		}
		// Nasty string handling for backup status
		string expanderNumber;
		string expanderText = "Exp:";
		sprintf(expanderNumber, "%i", ((int) getExpanderBatteryLevel()));
		strcat(expanderText,expanderNumber);
		// Displaying expander status
		displayLCDString(1,9,expanderText);
	}

	// Autonomous Selector
	else if (currentPage == 3) {
		displayLCDCenteredString(0, "Autonomous");
		if (autoMode == 1) {
			displayLCDCenteredString(1, "< Mode 1 >");
			} else if (autoMode == 2) {
			displayLCDCenteredString(1, "< Mode 2 >");
			}else if (autoMode == 3) {
			displayLCDCenteredString(1, "< Mode 3 >");
		}
	}
}

void lcdHome()
{
	currentPage = minPage;
	lcdUpdatePage();
}

void lcdNextPage()
{
	if (currentPage+1 <= maxPage) { // Theres another page to go to
		currentPage += 1;
		} else { // Go to the start of the loop
		currentPage = minPage;
	}
	lcdUpdatePage();
}

void lcdLastPage()
{
	if (currentPage-1 >= minPage) { // Theres another page to go back to
		currentPage -= 1;
		} else { // Go to the end of the loop
		currentPage = maxPage;
	}
	lcdUpdatePage();
}

void lcdNext() {
	// Autonomous selector
	if (currentPage == 3) {
		if (autoMode > autoMin) {
			autoMode -= 1;
			} else {
			autoMode = autoMax;
		}
		setAutonomousMode(autoMode);
		lcdUpdatePage();
	}
}

void lcdBack() {
	// Autonomous selector
	if (currentPage == 3) {
		if (autoMode < autoMax) {
			autoMode += 1;
			} else {
			autoMode = autoMin;
		}
		setAutonomousMode(autoMode);
		lcdUpdatePage();
	}
}

void lcdResetAutoRefresh() {
	secondsSinceRefresh = 0;
}

task lcdRunAutoRefresh() {
	lcdUpdatePage();
	while (true)
	{
		wait1Msec(1000);
		secondsSinceRefresh += 1;
		if (secondsSinceRefresh >= 10) {
			lcdUpdatePage();
			lcdResetAutoRefresh();
		}
	}
}

void lcdResetHoldTime() {
	holdDownTime = 0.0;
}

task countHoldTime() {
	while (true) {
		holdDownTime += 0.1;
		wait1Msec(100);
	}
}
