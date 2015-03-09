#include "StdAfx.h"
#include "Robot.h"

using namespace std;

Robot::Robot(string nom, int id) : m_nom(nom), m_id(id), m_position(0,0,0,0,0,0)
{
}

void Robot::updateTrajectoire(ClientOptiTrack* client)
{
	RigidBody rigidBody = client->getRigidBody(m_id);
	m_position.setX(rigidBody.x);
	m_position.setY(rigidBody.y);
	m_position.setZ(rigidBody.z);
	m_position.setYaw(rigidBody.qy);
	m_position.setPitch(rigidBody.qx);
	m_position.setRoll(rigidBody.qz);
}
