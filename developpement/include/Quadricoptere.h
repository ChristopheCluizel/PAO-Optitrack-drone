#pragma once
#include "robot.h"
#include "ARdrone.h"
/*
struct vitesse {
	float x;
	float z;
	vitesse(float _x=0,float _z=0)
		{x=_x; z=_z;};
};
*/
class Quadricoptere : public Robot
{
public:
	Quadricoptere(std::string nom, int id);
	bool allerA(Position position, Position erreur, bool isNewObjectif);
	void takeOff();
	void land();
	void emergency();
	void updateHistorique(Position pos);
	Position getErreurRetardee();
	Position getMoyenneErreur();
private:
	ARdrone m_drone;
	Position errorSum;
	Position lastError;
	vector<Position> m_historique;
};

