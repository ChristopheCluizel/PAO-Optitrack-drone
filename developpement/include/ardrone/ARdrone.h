#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <sstream>
#include <string>
#include <iostream>

#include "SafeQueue.h"
//#include <queue>
/*#include <thread>*/
using namespace std;
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library
 
#define SERVER "192.168.1.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 5556   //The port on which to listen for incoming data

enum etat{
	SOL,
	VOL,
	MOVE};

class ARdrone
{
public:
	ARdrone(void);
	~ARdrone(void);
	void connect();
	void disconnect();
	void config();
	void clearEmergencySignal();
	void flatTrim();
	void takeOff();
	void land();
	void move(float left_right_tilt,float front_back_tilt,float vertical_speed,float angular_speed);


private:
	void send(string cmd);
	void senderThread();
	static DWORD senderLauncher(LPVOID*param);
	//void navDataThread();

	SafeQueue<string> messageQueue;
	etat state;
	HANDLE  sender;//,navData;
	int s,slen,count;
	unsigned int value;
	struct sockaddr_in si_other;

};