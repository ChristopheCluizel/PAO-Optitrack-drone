#pragma once
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <winsock2.h>
#include <vector>

#include "NatNetTypes.h"
#include "NatNetClient.h"

#pragma warning( disable : 4996 )

typedef struct RigidBody
{
    int ID;                                 // RigidBody identifier
    float x, y, z;                          // Position
    float qx, qy, qz, qw;                   // Orientation
    int nMarkers;							// Number of markers associated with this rigid body
	RigidBody(){ID=0;}
    RigidBody(int m_ID,float m_x,float m_y,float m_z,float m_qx,float m_qy,float m_qz,float m_qw,int m_nMarkers)
    {
		ID= m_ID;
		x= m_x;
		y= m_y;
		z= m_z;
		qx= m_qx;
		qy= m_qy;
		qz= m_qz;
		qw= m_qw;
		nMarkers= m_nMarkers;
    }
} RigidBody;

class ClientOptiTrack
{
public:
	ClientOptiTrack(void);
	~ClientOptiTrack(void);
	
	RigidBody ClientOptiTrack::getRigidBody(int id);
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
	static RigidBody rigidBodies[10];
	NatNetClient* theClient;
	//FILE* fp;

	char* szMyIPAddress;
	char* szServerIPAddress;
};


