#include "StdAfx.h"
#include "Position.h"


Position::Position(float x, float y, float z, float yaw, float pitch, float roll) : m_x(x), m_y(y), m_z(z), m_yaw(yaw), m_pitch(pitch), m_roll(roll)
{
}

float Position::getX()
{
	return m_x;
}

float Position::getY()
{
	return m_y;
}

float Position::getZ()
{
	return m_z;
}

float Position::getYaw()
{
	return m_yaw;
}

float Position::getPitch()
{
	return m_pitch;
}

float Position::getRoll()
{
	return m_roll;
}

void Position::setX(float x)
{
	m_x = x;
}

void Position::setY(float y)
{
	m_y = y;
}

void Position::setZ(float z)
{
	m_z = z;
}

void Position::setYaw(float yaw)
{
	m_yaw = yaw;
}

void Position::setPitch(float pitch)
{
	m_pitch = pitch;
}

void Position::setRoll(float roll)
{
	m_roll = roll;
}
