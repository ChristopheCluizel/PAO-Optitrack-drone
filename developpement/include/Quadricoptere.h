#pragma once
#include "robot.h"
#include "ARdrone.h"

class Quadricoptere : public Robot
{
public:
	Quadricoptere(std::string nom, int id);
	void allerA(Position position, Position erreur);
	void takeOff();
	void land();
	void emergency();
private:
	ARdrone m_drone;
};

