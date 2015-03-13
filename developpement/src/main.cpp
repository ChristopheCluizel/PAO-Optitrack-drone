#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>



#include "stdafx.h"
#include "ARdrone.h"
#include "ClientOptitrack.h"

using namespace std;

ARdrone* drone;
void my_handler(int s){
           printf("Arret D'urgence\n",s);
		   drone->clearEmergencySignal();
}

int _tmain(int argc, _TCHAR* argv[])
{
	signal(SIGINT,my_handler);
	
	drone = new ARdrone();
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

	/*ClientOptiTrack *client = new ClientOptiTrack();
	int resultat = client->CreateClient(ConnectionType_Multicast);
	if(resultat != ErrorCode_OK)
    {
        printf("Error initializing client. See log for details. Exiting");
		Sleep(20000);
        return 0;
    }
    else
    {
        printf("Client initialized and ready.\n");
    }
	Sleep(3000);
	cout << client->getRigidBody(1).x << endl;
	Sleep(3000);
	cout << client->getRigidBody(1).x << endl;

	Sleep(3000);*/

	return 0;
}

