// ##################
// # Battery Checks #
// ##################

void updateBatteryIndicators() {
	int cortexBatteryRaw = nAvgBatteryLevel;
	float cortexBatteryPercentage = (nAvgBatteryLevel/1000)/7.2;
	float expanderBatteryPercentage = 0; // TODO Read value from actual battery

	if (cortexBatteryPercentage < 100) { // TODO Change to dangerous level, not just over 100
		// Cortex battery overvolted to dangerous level!
		// TODO Turn on red level, turn on mutual overvolt warning.
		} else {
		if (cortexBatteryPercentage <= 50) {
			if (cortexBatteryPercentage <= 20) {
				// Cortex battery at or less than 20%
				// TODO Turn on red battery level
				} else {
				// Cortex battery at or less than 50% greater than 20%
				// TODO Turn on yellow battery level
			}
		}
	}

	if (expanderBatteryPercentage < 100) { // TODO Change to dangerous level, not just over 100
		// Expander battery overvolted to dangerous level!
		// TODO Turn on red level, turn on mutual overvolt warning.
		} else {
		if (expanderBatteryPercentage <= 50) {
			if (expanderBatteryPercentage <= 20) {
				// Expander battery at or less than 20%
				// TODO Turn on red battery level
				} else {
				// Expander battery at or less than 50% greater than 20%
				// TODO Turn on yellow battery level
			}
		}
	}

}
