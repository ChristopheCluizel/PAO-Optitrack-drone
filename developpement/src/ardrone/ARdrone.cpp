#include "stdafx.h"
#include "ARdrone.h"


ARdrone::ARdrone(void) : sender(NULL)//, navData(NULL)
{
	count=1;
	value=0;
}


ARdrone::~ARdrone(void)
{
}

void ARdrone::connect() 
{
    slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    WSADATA wsa;
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR){
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
	state = SOL;

	sender = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)senderLauncher, this, 0, 0);
}


void ARdrone::disconnect()
{
	ostringstream os;
	os << "QUIT";
	send(os.str());
	while(messageQueue.size() != 0);
	CloseHandle(sender);
	//close(si_other);
}

/*void ARdrone::navDataThread()
{
	while(count < 15000);
	struct sockaddr_in si_otherNav;
    int s, slen=sizeof(si_otherNav);
    char buf[BUFLEN];
    char message[BUFLEN];
    WSADATA wsa;
 
    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");
     
    //create socket
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
     
    //setup address structure
    memset((char *) &si_otherNav, 0, sizeof(si_otherNav));
    si_otherNav.sin_family = AF_INET;
    si_otherNav.sin_port = htons(5554);
    si_otherNav.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while(1)
    {
		
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_otherNav, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            //exit(EXIT_FAILURE);
        }
        
        puts(buf);
		Sleep(100);
    }
 
    closesocket(s);
    WSACleanup();
}*/

DWORD ARdrone::senderLauncher(LPVOID*param)
{
	ARdrone *drone = (ARdrone*)param;
    drone->senderThread();
    return 0;
}

void ARdrone::senderThread()
{
	while(1)
	{
		if(!messageQueue.empty())
		{
			string cmd = messageQueue.front();
			messageQueue.pop();
			if(cmd == "QUIT")
				break;
			char* msg = new char[cmd.length()+1];
			strcpy_s(msg,cmd.length()+1,cmd.c_str());
			if(sendto(s, msg, strlen(msg) , 0 , (struct sockaddr *) &si_other, slen)==SOCKET_ERROR)
				printf("sendto() failed with error code : %d" , WSAGetLastError());
			cout << cmd << endl;
		}
		else if(state == VOL)
		{
			value = 0;
			value |= (1<<18) | (1<<20) | (1<<22) | (1<<24) | (1<<28);
			value |= (1<<9);
			ostringstream os;
			os << "AT*REF=" << count << "," << value << '\r';
			send(os.str());
		}
		else if(state == MOVE)
		{
			move(0,0,0,0);
		}
		else if(state == SOL)
		{
			ostringstream os3;
			os3 << "AT*COMWDG=" << count << '\r';
			send(os3.str());
		}
		Sleep(30);
	}
}

void ARdrone::send(string cmd)
{
	messageQueue.push(cmd);
	count++;
}

void ARdrone::config()
{
	ostringstream os3;
	os3 << "AT*COMWDG=" << count << '\r';
	send(os3.str());
	ostringstream os2;
	os2 << "AT*CONFIG=" << count << "," << "\"general:navdata_demo\",\"TRUE\"" << '\r';
	send(os2.str());
}

void ARdrone::clearEmergencySignal()
{
	value = 0;
	value |= (1<<18) | (1<<20) | (1<<22) | (1<<24) | (1<<28);
	value |= (1<<8);
	ostringstream os;
	os << "AT*REF=" << count << "," << value << '\r';
	send(os.str());
}

void ARdrone::flatTrim()
{
	ostringstream os;
	os << "AT*FTRIM=" << count << '\r';
	send(os.str());
	/*ostringstream os1;
	os1 << "AT*COMWDG=" << count << '\r';
	send(os1.str());
	ostringstream os2;
	os2 << "AT*COMWDG=" << count << '\r';
	send(os2.str());
	ostringstream os3;
	os3 << "AT*COMWDG=" << count << '\r';
	send(os3.str());*/
}

void ARdrone::takeOff()
{
	value = 0;
	value |= (1<<18) | (1<<20) | (1<<22) | (1<<24) | (1<<28);
	value |= (1<<9);
	ostringstream os;
	os << "AT*REF=" << count << "," << value << '\r';
	send(os.str());
	state=VOL;
}

void ARdrone::land()
{
	for(int i=0;i<50;i++){
		value = 0;
		value |= (1<<18) | (1<<20) | (1<<22) | (1<<24) | (1<<28);
		ostringstream os;
		os << "AT*REF=" << count << "," << value << '\r';
		send(os.str());
	}
	/*ostringstream os;
	os << "AT*COMWDG=" << count << '\r';
	send(os.str());*/
	state=SOL;
}

void ARdrone::move(float left_right_tilt,float front_back_tilt,float vertical_speed,float angular_speed)
{
		ostringstream os;
		os << "AT*PCMD=" << count;
		if(!left_right_tilt && !front_back_tilt && !vertical_speed && !angular_speed)
			os << "," << 0;
		else
			os << "," << 3;
		os << "," << *(int*)(&left_right_tilt);
		os << "," << *(int*)(&front_back_tilt);
		os << "," << *(int*)(&vertical_speed);
		os << "," << *(int*)(&angular_speed);
		os << '\r';
		send(os.str());
		state=MOVE;
}