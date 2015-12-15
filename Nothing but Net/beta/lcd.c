int currentPage = 1;
int minPage = 1;
int maxPage = 2;
int secondsSinceRefresh = 0;

// TODO: Create task to update page every 5 seconds if page not changed?
void lcdUpdatePage()
{
	clearLCDLine(0);
	clearLCDLine(1);
	// Pages are defined here. Messy, but it works.
	if (currentPage == 1) { // General status
		displayLCDString(0,6,"Home");
		if ((getBackupBatteryStatus() >= 2) || (getCortexBatteryStatus() >= 2) || (getCortexBatteryStatus() >= 2)) { // Battery page needs attention
			displayLCDChar(1,0,'!');
		}
		displayLCDString(1,1,"Bat");
	}
	else if (currentPage == 2) { // Battery status
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
