#pragma once
#include <string>
#include "include\optitrack\ClientOptiTrack.h"
#include "Position.h"

class Robot
{
public:
	Robot(std::string nom, int id);
	void updateTrajectoire(ClientOptiTrack* client);

protected:
	std::string m_nom;
	Position m_position;
	int m_id;


};

