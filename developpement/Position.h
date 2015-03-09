#pragma once
class Position
{
public:
	Position(float x, float y, float z, float yaw, float pitch, float roll);
	float getX();
	float getY();
	float getZ();
	float getYaw();
	float getPitch();
	float getRoll();
	void setX(float x);
	void setY(float x);
	void setZ(float x);
	void setYaw(float x);
	void setPitch(float x);
	void setRoll(float x);

private:
	float m_x, m_y, m_z, m_yaw, m_pitch, m_roll;
};

