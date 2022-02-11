
#include "Junction.h"
#include <iostream>


	
Junction::Junction() {}
	

	Position Junction::getReflectPos(Position sourcePos, Position listenerPos, int faceIndex, float roomX, float roomY, float roomZ)
	{
        switch (faceIndex){
            case 0:
                    junctionPos = getReflectPosFace1(sourcePos, listenerPos);
                break;
            case 1:
                    // x'=y, y'=xr-x, z'=z
                    sourcePosT = Position(sourcePos.getY(), roomX-sourcePos.getX(), sourcePos.getZ());
                    listenerPosT = Position(listenerPos.getY(), roomX-listenerPos.getX(), listenerPos.getZ());
                    posT = getReflectPosFace1(sourcePosT, listenerPosT);
                    
                
                    // y=x',x=xr-y', z=z'
                junctionPos = Position(roomX-posT.getY(), posT.getX(), posT.getZ());
                
                break;

            case 2:
                        //x'=xr-x,y'=yr-y,z'=z
                        sourcePosT = Position(roomX- sourcePos.getX(), roomY- sourcePos.getY(),  sourcePos.getZ());
                        listenerPosT = Position(roomX- listenerPos.getX(), roomY- listenerPos.getY(),  listenerPos.getZ());
                        posT = getReflectPosFace1(sourcePosT, listenerPosT);
                        
                       // % x=xr-x',y=yr-y',z=z'
                junctionPos = Position(roomX-posT.getX(), roomY-posT.getY(), posT.getZ());
                
                break;

            case 3:
                      //  % x'=yr-y, y'=x, z'=z
                        sourcePosT = Position(roomY- sourcePos.getY(),  sourcePos.getX(),  sourcePos.getZ());
                        listenerPosT = Position(roomY- listenerPos.getY(),  listenerPos.getX(),  listenerPos.getZ());
                        posT = getReflectPosFace1(sourcePosT, listenerPosT);
                        
                       // % y=yr-x', x=y', z=z'
                junctionPos = Position(posT.getY(), roomY-posT.getX(), posT.getZ());
                
                
                break;

            case 4:
                       // % x'=x, y'=zr-z, z'=y
                        sourcePosT = Position( sourcePos.getX(), roomZ- sourcePos.getZ(),  sourcePos.getY());
                        listenerPosT = Position( listenerPos.getX(), roomZ- listenerPos.getZ(),  listenerPos.getY());
                        posT = getReflectPosFace1(sourcePosT, listenerPosT);
                        
                       // % x=x',z=zr-y', y=z'
                junctionPos = Position(posT.getX(), posT.getZ(), roomZ-posT.getY());
                
                
                break;

            case 5:
                        //% x'=x, y'=z, z'=yr-y
                        sourcePosT = Position( sourcePos.getX(),  sourcePos.getZ(), roomY- sourcePos.getY());
                        listenerPosT = Position( listenerPos.getX(),  listenerPos.getZ(), roomY- listenerPos.getY());
                        posT = getReflectPosFace1(sourcePosT, listenerPosT);
                        
                      //  % x=x', z=y', y=yr-z'
                junctionPos = Position(posT.getX(), roomY-posT.getZ(), posT.getY());
                
                break;

        }
        return junctionPos;
	}

Position Junction::getReflectPosFace1(Position sourcePos, Position listenerPos){
// Solve the same problem, but only for the surface 1

    reflectionPosFace1.setY(0);

// For the following conversions, see Enzo's notes.
    reflectionPosFace1.setX(getReflectPosOneDim(sourcePos.getX(), sourcePos.getY(), listenerPos.getX(), listenerPos.getY()));
    
    reflectionPosFace1.setZ(getReflectPosOneDim(sourcePos.getZ(), sourcePos.getY(), listenerPos.getZ(), listenerPos.getY()));
    
    return reflectionPosFace1;
}


float Junction::getReflectPosOneDim(float x1, float y1, float x2, float y2){

    if (x1 == x2){
        reflectionPosOneDim = x1;
    } else{
        reflectionPosOneDim = (x1*y2 + x2*y1)/(y1+y2);
    }
  
    return reflectionPosOneDim;
}

