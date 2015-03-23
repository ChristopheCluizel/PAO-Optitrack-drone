#pragma once
#include <string>

#include "ClientOptiTrack.h"
#include "Position.h"

class Robot
{
public:
	Robot(std::string nom, int id);
	void updateTrajectoire(ClientOptiTrack* client);
	void updatePosition(Position position);

protected:
	std::string m_nom;
	Position m_position;
	int m_id;
};
