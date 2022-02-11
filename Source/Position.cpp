
#include "Position.h"
#include <iostream>

	
	Position::Position(float x, float y, float z) : x(x), y(y), z(z) {}
	
	float Position::distanceTo(Position position)
	{
		float dx = getX() - position.getX();
		float dy = getY() - position.getY();
		float dz = getZ() - position.getZ();
		return sqrt(dx*dx + dy*dy + dz*dz);
	}
	
	float Position::azimuthFrom(Position position)
	{
		
		float x = getX() - position.getX();
		float y = -(getY() - position.getY());
		return atan2(y,x);
	}
	
	float Position::elevationFrom(Position position)
	{
		float z = getZ() - position.getZ();
		return asin(z/distanceTo(position));
	}
	
	void Position::setX(float x){
		this->x = x;
	}
	
	float Position::getX(){
		return x;
	}
	
	void Position::setY(float y){
		this->y = y;
	}
	
	float Position::getY(){
		return y;
	}
	
	void Position::setZ(float z){
		this->z = z;
	}
	
	float Position::getZ(){
		return z;
	}	

