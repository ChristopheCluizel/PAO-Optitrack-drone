#include "StdAfx.h"
#include "Quadricoptere.h"
#include <iostream>
using namespace std;

Quadricoptere::Quadricoptere(string nom, int id) : Robot(nom, id) , m_drone()
{
	m_drone.connect();
	m_drone.config();
	m_drone.flatTrim();
}

void Quadricoptere::allerA(Position objectif, Position erreur)
{
		float Ycoef = 0.0004; // Y proportionnal coef
		float objectifY = objectif.getY();
		float droneY= m_position.getY();
		float consigneY = (objectifY-droneY)*Ycoef;

		float Xcoef = -0.00005; // X proportionnal coef
		float objectifX = objectif.getX();
		float droneX= m_position.getX();
		float consigneX = (objectifX-droneX)*Xcoef;

		float Zcoef = -0.00005; // Z proportionnal coef
		float objectifZ = objectif.getZ();
		float droneZ= m_position.getZ();
		float consigneZ = (objectifZ-droneZ)*Zcoef;

		float QYcoef = -0.0006; // QY proportionnal coef
		float objectifQY = objectif.getYaw();
		float droneQY =m_position.getYaw();
		float consigneQY = (objectifQY-droneQY)*QYcoef;
			
		if(consigneX < -1) consigneX = -1;
		if(consigneX > 1) consigneX = 1;
		if(consigneY < -1) consigneY = -1;
		if(consigneY > 1) consigneY = 1;
		if(consigneZ < -1) consigneZ = -1;
		if(consigneZ > 1) consigneZ = 1;
		if(consigneQY < -1) consigneQY = -1;
		if(consigneQY > 1) consigneQY = 1;

		if(consigneX > -0.01 && consigneX < 0.01) consigneX = 0;
		if(consigneZ > -0.01 && consigneZ < 0.01) consigneZ = 0;
		if(consigneY > -0.01 && consigneY < 0.01) consigneY = 0;
		if(consigneQY > -0.01 && consigneQY < 0.01) consigneQY = 0;

		m_drone.move(consigneX,consigneZ,consigneY,consigneQY);

		printf("\n\n axe \t objectif \t position \t consigne");
		printf("\n X \t\t %g \t %g \t %g", objectifX, droneX, consigneX);
		printf("\n Z \t\t %g \t %g \t %g", objectifZ, droneZ, consigneZ);
		printf("\n Y \t\t %g \t %g \t %g", objectifY, droneY, consigneY);
		printf("\n Yaw \t\t %g \t %g \t %g", objectifQY, droneQY, consigneQY);
}

void Quadricoptere::takeOff()
{
	m_drone.takeOff();
}

void Quadricoptere::land()
{
	m_drone.land();
}

void Quadricoptere::emergency()
{
	m_drone.clearEmergencySignal();
}