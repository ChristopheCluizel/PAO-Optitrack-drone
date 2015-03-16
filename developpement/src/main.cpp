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
	client->szServerIPAddress = "192.168.1.2";
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

	drone = new ARdrone();
	drone->connect();
	drone->config();
	printf("ClearEmergency [y/n]");
	char c='a';
	scanf("%c",&c);
	if(c=='y')
		drone->clearEmergencySignal();
	drone->flatTrim();
	Sleep(200);
	drone->takeOff();
	
	
	/*Sleep(6000);
	drone->move(0,-0.1,0,0);
	Sleep(1000);
	drone->move(0,0.1,0,0);
	Sleep(1000);
	drone->land();
	drone->disconnect();*/

	while(1)
	{
		//controle avec coque
		/*float tangage = client->getRigidBody(2).qx;
		float roulis = client->getRigidBody(2).qz;
		cout << tangage << ", " << roulis<< endl;
		if(tangage >-0.5 && tangage<0.5 &&
			roulis >-0.5 && roulis<0.5)
		{
			drone->move(roulis,-tangage,0,0);
		}
		Sleep(30);*/
		float Ycoef = 0.0004; // Y proportionnal coef
		float objectifY = client->getRigidBody(2).y * 1000;//convert to millimeters
		float droneY= client->getRigidBody(1).y * 1000;
		float consigneY = (objectifY-droneY)*Ycoef;

		float Xcoef = -0.00005; // X proportionnal coef
		float objectifX = client->getRigidBody(2).x * 1000;//convert to millimeters
		float droneX= client->getRigidBody(1).x * 1000;
		float consigneX = (objectifX-droneX)*Xcoef;
		//cout << objectifX << " - " << droneX << " = " << consigneX << endl;

		float Zoffset = 2000;
		float Zcoef = -0.00005; // Z proportionnal coef
		float objectifZ = client->getRigidBody(2).z * 1000 - Zoffset;//convert to millimeters
		float droneZ= client->getRigidBody(1).z * 1000;
		float consigneZ = (objectifZ-droneZ)*Zcoef;
		//cout << objectifZ << " - " << droneZ << " = " << consigneZ << endl;

		float QYcoef = -0.0006; // QY proportionnal coef
		float objectifQY = client->getRigidBody(2).qy * 1000;//convert to millimeters
		float droneQY = client->getRigidBody(1).qy * 1000;
		float consigneQY = (objectifQY-droneQY)*QYcoef;
		cout << objectifQY << " - " << droneQY << " = " << consigneQY << endl;


		drone->move(consigneX,consigneZ,consigneY,consigneQY);
		//drone->move(0,0,0,consigneQY);
		Sleep(30);
	}
	
	

	return 0;
}

