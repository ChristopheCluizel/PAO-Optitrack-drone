#include "StdAfx.h"
#include "Quadricoptere.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

Quadricoptere::Quadricoptere(string nom, int id) : Robot(nom, id) , m_drone()
{
	m_drone.connect();
	m_drone.config();
	m_drone.flatTrim();
}

void Quadricoptere::updateHistorique(Position pos){
	m_historique.push_back(pos);
	if(m_historique.size() > 33)
		m_historique.erase(m_historique.begin());
}

Position Quadricoptere::getErreurRetardee(){
	if(m_historique.size() == 0)
		return m_position;
	return m_historique.at(0);
}
Position Quadricoptere::getMoyenneErreur(){
	Position moyenne;
	for(int i=0; i< m_historique.size();i++)
	{
		moyenne.setX( moyenne.getX() + m_historique.at(i).getX()/m_historique.size());
		moyenne.setY( moyenne.getY() + m_historique.at(i).getY()/m_historique.size());
		moyenne.setZ( moyenne.getZ() + m_historique.at(i).getZ()/m_historique.size());
		moyenne.setYaw( moyenne.getYaw() + m_historique.at(i).getYaw()/m_historique.size());
	}
	return moyenne;

}
bool Quadricoptere::allerA(Position objectif, Position erreur, bool isNewObjectif)
{

	FILE* file = fopen("C:\\Users\\asi\\Desktop\\courbe.csv","a");


		if(isNewObjectif)
			errorSum.setX(0);
		float coeffDeStabilite = 0.6;
		float consigneY = 0;
		float consigneX = 0;
		float consigneZ = 0;
		float consigneQY = 0;

		/* ============  Y  ============= */
		float YP = -0.000004*coeffDeStabilite; // Y proportionnal coef for P
		float YI = -0.00000; // Y proportionnal coef for I
		float YD = -0.00000; // Y proportionnal coef for D
		float objectifY = objectif.getY();
		float droneY= m_position.getY();
		//lastError.setY(abs(droneY - objectifY));
		//errorSum.setY(errorSum.getY()+ objectifY - droneY);
		if(abs(droneY - objectifY) > erreur.getY())
			consigneY =   YP * (objectifY-droneY) ;
						+ YI * errorSum.getY() 
						+ YD * getErreurRetardee().getY() ;
		printf("\n\nYP -> %g * %g  = %g",YP,(objectifY-droneY),YP*(objectifY-droneY));
		printf("\nYI -> %g * %g  = %g",YI,errorSum.getY(),YI*errorSum.getY());
		printf("\nYD -> %g * %g  = %g",YD,lastError.getY(),YD*lastError.getY());
		printf("\nConsigne -> %g",consigneY);

		/* ============  X  ============= */
		float XP = -0.00005*coeffDeStabilite; // X proportionnal coef for P
		float XI = 0.0000001; // X proportionnal coef for I
		float XD = -0.000015; // X proportionnal coef for D
		float objectifX = objectif.getX();
		float droneX= m_position.getX();
		lastError.setX(droneX - objectifX);
		errorSum.setX(errorSum.getX()+ objectifX - droneX);
		if(abs(droneX - objectifX) > erreur.getX())
			consigneX =   XP * (objectifX-droneX) 
						//+ XI * errorSum.getX() 
						+ XD * getMoyenneErreur().getX() ;
		/*printf("\n\nXP -> %g * %g  = %g",XP,(objectifX-droneX),XP*(objectifX-droneX));
		printf("\nXI -> %g * %g  = %g",XI,errorSum.getX(),XI*errorSum.getX());
		printf("\nXD -> %g * %g  = %g",XD,lastError.getX(),XD*lastError.getX());
		printf("\nConsigne -> %g",consigneX);*/

		/* ============  Z  ============= */
		float ZP = -0.00005*coeffDeStabilite; // Z proportionnal coef for P
		float ZI = 0.0000001; // Z proportionnal coef for I
		float ZD = -0.000015; // Z proportionnal coef for D
		float objectifZ = objectif.getZ();
		float droneZ= m_position.getZ();
		lastError.setZ(droneZ - objectifZ);
		errorSum.setZ(errorSum.getZ()+ objectifZ - droneZ);
		if(abs(droneZ - objectifZ) > erreur.getZ())
			consigneZ =   ZP * (objectifZ-droneZ)
						//+ ZI * errorSum.getZ()
						+ ZD * getMoyenneErreur().getZ() ;
		printf("\n\nZP -> %g * %g  = %g",ZP,(objectifZ-droneZ),ZP*(objectifZ-droneZ));
		printf("\nZI -> %g * %g  = %g",ZI,errorSum.getZ(),ZI*errorSum.getZ());
		printf("\nZD -> %g * %g  = %g",ZD,lastError.getZ(),ZD*lastError.getZ());
		printf("\nConsigne -> %f",consigneZ);
		fprintf(file,"\"%g\";\"%g\";\"%g\";\"%g\";\n"
			,droneZ
			,ZP * (objectifZ-droneZ) * 10000
			//,ZI * errorSum.getZ() * 10000
			,ZD *  getMoyenneErreur().getZ() * 10000 );
		
		/* ============  QY  ============= */
		float QYcoef = -0.004 * coeffDeStabilite; // QY proportionnal coef
		float objectifQY = objectif.getYaw();
		float droneQY =m_position.getYaw();
		if(abs(droneQY - objectifQY) > erreur.getYaw())
			consigneQY = (objectifQY-droneQY)*QYcoef;
			
		if(consigneX < -1) consigneX = -1;
		if(consigneX > 1) consigneX = 1;
		if(consigneY < -1) consigneY = -1;
		if(consigneY > 1) consigneY = 1;
		if(consigneZ < -1) consigneZ = -1;
		if(consigneZ > 1) consigneZ = 1;
		if(consigneQY < -1) consigneQY = -1;
		if(consigneQY > 1) consigneQY = 1;
		
		/*if(consigneX > -0.01 && consigneX < 0.01) consigneX = 0;
		if(consigneZ > -0.01 && consigneZ < 0.01) consigneZ = 0;
		if(consigneY > -0.01 && consigneY < 0.01) consigneY = 0;
		if(consigneQY > -0.01 && consigneQY < 0.01) consigneQY = 0;*/

		m_drone.move(consigneX, consigneZ, consigneY, consigneQY);

		/*printf("\n\n axe \t objectif \t position \t consigne");
		printf("\n X \t\t %g \t %g \t %g", objectifX, droneX, consigneX);
		printf("\n Z \t\t %g \t %g \t %g", objectifZ, droneZ, consigneZ);
		printf("\n Y \t\t %g \t %g \t %g", objectifY, droneY, consigneY);
		printf("\n Yaw \t\t %g \t %g \t %g", objectifQY, droneQY, consigneQY);*/

		/*printf("\n\nsin(%g) = %g",(unsigned int) droneQY,sin(droneQY/180));
		printf("\ncos(%g) = %g",droneQY,cos(droneQY/180));
		printf("\ntan(%g) = %g",droneQY,tan(droneQY/180));*/

		fclose(file);
		updateHistorique(lastError);
		return (consigneY == 0 && consigneZ == 0 && consigneX ==  0 && consigneQY == 0);
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