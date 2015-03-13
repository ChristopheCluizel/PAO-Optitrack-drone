#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>



#include "stdafx.h"
#include "ARdrone.h"
#include "ClientOptitrack.h"

using namespace std;

ARdrone* drone;
bool urgence = 0;

void my_handler(int s){
		if(urgence)
		{
           printf("Arret D'urgence\n");
		   drone->clearEmergencySignal();
		}
		else
		{
            printf("Atterissage\n");
			drone->land();
			urgence=1;
			signal(SIGINT,my_handler);
		}
		   
}

int _tmain(int argc, _TCHAR* argv[])
{
	signal(SIGINT,my_handler);// gestion de l'arret d'urgence
	
	ClientOptiTrack *client = new ClientOptiTrack();
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

	/*drone = new ARdrone();
	drone->connect();
	drone->config();
	//drone->clearEmergencySignal();
	drone->flatTrim();
	drone->takeOff();*/
	
	
	/*Sleep(6000);
	drone->move(0,-0.1,0,0);
	Sleep(1000);
	drone->move(0,0.1,0,0);
	Sleep(1000);
	drone->land();
	drone->disconnect();*/

	while(1)
	{

	}
	
	Sleep(3000);
	cout << client->getRigidBody(1).x << endl;
	Sleep(3000);
	cout << client->getRigidBody(1).x << endl;

	Sleep(3000);

	return 0;
}

