
#include "stdafx.h"
#include "ARdrone.h"
#include "ClientOptitrack.h"

int _tmain(int argc, _TCHAR* argv[])
{
	/*ARdrone* drone = new ARdrone();
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
	drone->disconnect();*/

	ClientOptiTrack *client = new ClientOptiTrack();
	int resultat = client->CreateClient(ConnectionType_Multicast);
	if(resultat != ErrorCode_OK)
    {
        printf("Error initializing client.  See log for details.  Exiting");
		Sleep(2000000);
        return 0;
    }
    else
    {
        printf("Client initialized and ready.\n");
    }
	Sleep(2000000);
	return 0;
}

