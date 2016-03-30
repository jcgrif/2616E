#pragma config(Sensor, in1,    gyroRadar,      sensorGyro)
#pragma config(Sensor, dgtl1,  rangeRadar,     sensorSONAR_cm)
#pragma config(Motor,  port5,           motorRadar,    tmotorVex393_MC29, openLoop)

// Sets the radar to spinning it's normal direction
void startRadar(int degree) {



	int d=0;
	int x;
	d = abs(SensorValue[gyroRadar]);
	motor[motorRadar] = 20;
	x = abs(SensorValue[gyroRadar]);
	while (x  < d + degree)
	{x = abs(SensorValue[gyroRadar]);}
	motor[motorRadar] = 0;

}
task main()
{
	string s;
	resetSensor(gyroRadar);
	wait1Msec(2000);

	for(int t=0;t<=360;t++){
		int a;
		a= SensorValue[gyroRadar];
		startRadar(500);
		sprintf(s,"%i",t);
		writeDebugStreamLine(s);
		wait10Msec(10);
		sprintf(s,"%i",a-SensorValue[gyroRadar]);
		writeDebugStreamLine(s);
		wait10Msec(200);


	}

}
