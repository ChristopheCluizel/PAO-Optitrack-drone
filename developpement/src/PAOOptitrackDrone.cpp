// PAOOptitrackDrone.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ardrone/ARdrone.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ARdrone* drone = new ARdrone();
	drone->connect();
	drone->config();
	//drone->clearEmergencySignal();
	drone->flatTrim();
	drone->takeOff();
	Sleep(6000);
	drone->move(0,-0.1,0,0);
	Sleep(1000);
	drone->move(0,0.1,0,0);
	Sleep(1000);
	drone->land();
	drone->disconnect();
	return 0;
}

