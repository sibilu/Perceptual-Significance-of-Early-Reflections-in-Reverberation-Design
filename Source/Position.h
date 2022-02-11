
#pragma once
#include <cmath>
#include <iostream>


	class Position
	{
		private:
			float x, y, z;
		
		public:
		float getX();
		void setX(float x);
		
		float getY();
		void setY(float y);
		
		float getZ();
		void setZ(float z);
		
		float distanceTo(Position position); //
		float azimuthFrom(Position position);
		float elevationFrom(Position position);
		
		Position() {};
		Position(float x, float y, float z);
		~Position() {};
	};

