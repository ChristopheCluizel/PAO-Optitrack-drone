#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>

#include "stdafx.h"
#include "ClientOptitrack.h"
#include "Quadricoptere.h"

using namespace std;

Quadricoptere* quadri;
bool urgence = 0;

void my_handler(int s){
		if(urgence)
		{
           printf("Arret D'urgence\n");
		   quadri->emergency();
		}
		else
		{
            printf("Atterissage\n");
			quadri->land();
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

	quadri = new Quadricoptere("ARdrone1",1);

	printf("ClearEmergency [y/n]");
	char c='a';
	scanf("%c",&c);
	if(c=='y')
		quadri->emergency();
	Sleep(200);
	quadri->takeOff();

	Sleep(6000);

	queue<Position*> trajectoire;
	trajectoire.push(new Position(0,1500,0,0,0,0));
	trajectoire.push(new Position(0,1500,1500,0,0,0));
	trajectoire.push(new Position(1200,1500,-550,0,0,0));
	trajectoire.push(new Position(0,1500,0,0,0,0));

	while(1)
	{
		if(trajectoire.empty()) {
			quadri->land();
			Sleep(2000);
			break;
		}

		Position* temp = new Position(
			client->getRigidBody(1).x * 1000
			, client->getRigidBody(1).y * 1000
			, client->getRigidBody(1).z * 1000
			, client->getRigidBody(1).qy * 180
			, client->getRigidBody(1).qx * 180
			, client->getRigidBody(1).qz  * 180);
		quadri->updatePosition(*temp);
		Position *objectif = trajectoire.front();
		Position *erreur = new Position(100,100,100,5,5,5);
		if(quadri->allerA(*objectif,*erreur))
			trajectoire.pop();
		free(temp);
		free(erreur);

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
		/*float Ycoef = 0.0004; // Y proportionnal coef
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

		if(consigneX > -1 && consigneX < 1
			&& consigneY > -1 && consigneY < 1
			&& consigneZ > -1 && consigneZ < 1
			&& consigneQY > -1 && consigneQY < 1) 
		{
			drone->move(consigneX,consigneZ,consigneY,consigneQY);
			//drone->move(0,0,0,consigneQY);
			Sleep(30);
		}*/
		Sleep(30);
	}
	
	

	return 0;
}

