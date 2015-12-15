int currentPage = 1;
int minPage = 1;
int maxPage = 3;

void lcdUpdatePage()
{
	clearLCDLine(0);
	clearLCDLine(1);
	// Pages are defined here. Messy, but it works.
	if (currentPage == 1) { // General status
		// TODO Make page with if a page needs attention
	}
	else if (currentPage == 2) { // Battery status
		displayLCDString(0,0,"BatStat|");
		char numText[15];
		if (getBackupBatteryStatus() >= 2) { // Backup bat needs attention
			displayLCDChar(0,8,'!');
		}
		sprintf(numText,"%d", (int) getBackupBatteryLevel());
		string backupText = "Bck:";
		strcat(backupText,numText);
		displayLCDString(0,9,backupText);
		if (getCortexBatteryStatus() >= 2) { // Cortex bat needs attention
			displayLCDChar(1,0,'!');
		}
		sprintf(numText,"%d", (int) getCortexBatteryLevel());
		string cortexText = "Ctx:";
		strcat(cortexText,numText);
		displayLCDString(0,9,backupText);
		if (getExpanderBatteryStatus() >= 2) { // Expander bat needs attention
			displayLCDChar(1,8,'!');
		}
		sprintf(numText,"%d", (int) getExpanderBatteryLevel());
		string expanderText = "Exp:";
		strcat(expanderText,numText);
		displayLCDString(0,9,backupText);
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
