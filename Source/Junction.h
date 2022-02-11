
#pragma once
#include <cmath>
#include <iostream>
#include "Position.h"


	class Junction
	{
    public:
        Junction();
        Junction(Position sourcePos, Position listenerPos);
        ~Junction() {};

        Position getReflectPos(Position sourcePos, Position listenerPos, int faceIndex,float roomX, float roomY, float roomZ); //
        Position getReflectPosFace1(Position sourcePos, Position listenerPos);
        float getReflectPosOneDim(float x1, float y1, float x2, float y2);
            
        Position position;

    private:
        Position junctionPos;
        Position sourcePosT;
        Position listenerPosT;
        Position posT;
        
        
        Position reflectionPosFace1;
        float reflectionPosOneDim;
        
 
	};

