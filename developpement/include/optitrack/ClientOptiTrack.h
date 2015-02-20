#pragma once
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <winsock2.h>

#include "NatNetTypes.h"
#include "NatNetClient.h"

#pragma warning( disable : 4996 )

class ClientOptiTrack
{
public:
	ClientOptiTrack(void);
	~ClientOptiTrack(void);

	int ClientOptiTrack::CreateClient(int iConnectionType);
	static void __cdecl ClientOptiTrack::DataHandler(sFrameOfMocapData* data, void* pUserData);
	static void __cdecl ClientOptiTrack::MessageHandler(int msgType, char* msg);
	void ClientOptiTrack::_WriteHeader(FILE* fp, sDataDescriptions* pBodyDefs);
	void ClientOptiTrack::_WriteFrame(FILE* fp, sFrameOfMocapData* data);
	void ClientOptiTrack::_WriteFooter(FILE* fp);
	void ClientOptiTrack::resetClient();
	static void Callback(int msgType, char* msg, void * this_pointer);

public:
	unsigned int MyServersDataPort;
	unsigned int MyServersCommandPort;

	NatNetClient* theClient;
	//FILE* fp;

	char* szMyIPAddress;
	char* szServerIPAddress;
};

