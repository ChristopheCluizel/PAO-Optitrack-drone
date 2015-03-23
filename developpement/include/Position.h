#pragma once
class Position
{
public:
	Position(float x=0, float y=0, float z=0, float yaw=0, float pitch=0, float roll=0);
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
	float m_x;
	float m_y;
	float m_z;
	float m_yaw;
	float m_pitch;
	float m_roll;
};

