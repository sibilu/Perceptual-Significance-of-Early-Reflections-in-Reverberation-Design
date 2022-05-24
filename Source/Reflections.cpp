
#include "Reflections.h"


Reflections::Reflections(){

}

// Destructor
Reflections::~Reflections(){
}

void Reflections::prepare(dsp::ProcessSpec spec){
 
    // PREPARE DELAYS
    micSourceDelay.prepare(spec);
    wallFrontDelay.prepare(spec);
    wallBackDelay.prepare(spec);
    wallRightDelay.prepare(spec);
    wallLeftDelay.prepare(spec);
    wallCeilingDelay.prepare(spec);
    wallFloorDelay.prepare(spec);
   
    // RESET DELAYS
    micSourceDelay.reset();
    wallFrontDelay.reset();
    wallBackDelay.reset();
    wallRightDelay.reset();
    wallLeftDelay.reset();
    wallCeilingDelay.reset();
    wallFloorDelay.reset();

    // PREPARE ABSORPTION FILTERS
    wallFrontAbsorption.prepareFilter(spec);
    wallBackAbsorption.prepareFilter(spec);
    wallRightAbsorption.prepareFilter(spec);
    wallLeftAbsorption.prepareFilter(spec);
    wallCeilingAbsorption.prepareFilter(spec);
    wallFloorAbsorption.prepareFilter(spec);


}


float Reflections::getDist(int junctionIndex){
    return combinedDistances[junctionIndex];
}

void Reflections::processBlock(dsp::AudioBlock<float> inputBlock, dsp::AudioBlock<float> & outputBlock0, dsp::AudioBlock<float> & outputBlock1, dsp::AudioBlock<float> & outputBlock2, dsp::AudioBlock<float> & outputBlock3, dsp::AudioBlock<float> & outputBlock4, dsp::AudioBlock<float> & outputBlock5){
    
    
    // PROCESS BLOCK USING NON REPLACING METHOD
    wallFrontDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock0));
    wallBackDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock1));
    wallRightDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock2));
    wallLeftDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock3));
    wallCeilingDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock4));
    wallFloorDelay.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock5));

    // FILTER ON/OFF BUTTON
    if(filtersOnOff){
    wallFrontAbsorption.processBlock(outputBlock0);
    wallBackAbsorption.processBlock(outputBlock1);
    wallRightAbsorption.processBlock(outputBlock2);
    wallLeftAbsorption.processBlock(outputBlock3);
    wallCeilingAbsorption.processBlock(outputBlock4);
    wallFloorAbsorption.processBlock(outputBlock5);
    } else {
        
    }
}


void Reflections::setSampleRate(double sampleRate){
    Fs = sampleRate;
}

float Reflections::junctionMicStereoGain(int junctionIndex, int channel){

    // reference: Pulkki, V. (1997) Virtual Sound Source Positioning Using Vector Base Amplitude Panning AES
    
    float x = junction[junctionIndex].position.getX() - listenerPos.getX();
    float y = junction[junctionIndex].position.getY() - listenerPos.getY();
    
    
    float junctionAzimuth = atan2(x,y);
    float sinAzimuth = sin(junctionAzimuth);
    float denom = 1 / sqrt(2 * (1 + pow(sinAzimuth, 2)));
    
    switch (channel){
        case 0:
            junctionGain = (1 + sinAzimuth) * denom;
            break;
        case 1: junctionGain = (1 - sinAzimuth) * denom;
            break;
    }
    return junctionGain;
}


float Reflections::invDistLaw(int channel){
    float distAtt = 1/fmax(listenerPos.distanceTo(sourcePos),0.4);
    return distAtt;
}


float Reflections::sourceMicStereoGain(int channel){

    // reference: Pulkki, V. (1997) Virtual Sound Source Positioning Using Vector Base Amplitude Panning AES

    float distAtt = 1/fmax(listenerPos.distanceTo(sourcePos),0.4);
   
    float x = listenerPos.getX() - sourcePos.getX();
    float y = listenerPos.getY() - sourcePos.getY();
    
    float sourceAzimuth = atan2(x,y);
    float sinAzimuth = sin(sourceAzimuth);
    float denom = sqrt(2 * (1 + pow(sinAzimuth, 2)));
    
    
    switch (channel){
        case 0:
            inputGain = (1 + sinAzimuth) * denom;
            break;
        case 1: inputGain = (1 - sinAzimuth) * denom;
            break;
    }
    return inputGain*distAtt;
    
    
}

void Reflections:: update(int materialFrontBack, int materialRightLeft, int materialCeilingFloor){
    
    wallFrontAbsorption.updateFilter(materialFrontBack);
    wallBackAbsorption.updateFilter(materialFrontBack);
    wallRightAbsorption.updateFilter(materialRightLeft);
    wallLeftAbsorption.updateFilter(materialRightLeft);
    wallCeilingAbsorption.updateFilter(materialCeilingFloor);
    wallFloorAbsorption.updateFilter(materialCeilingFloor);
    

    for (int i = 0; i < junctionCount; i++){
        // POSITIONS OF ALL JUNCTIONS
        junction[i].position = junction[i].getReflectPos(sourcePos, listenerPos, i, roomX, roomY, roomZ);
        
        // DISTANCES BETWEEN SOURCE AND JUNCTION
        sourceToJunctionDistances[i] =sourcePos.distanceTo(junction[i].position);
        
        // DISTANCES BETWEEN JUNCTION AND LISTENER
        junctionToMicDistances[i] = junction[i].position.distanceTo(listenerPos);
        
        // COMBINED DISTANCE TRAVELLED
        combinedDistances[i] = sourceToJunctionDistances[i] + junctionToMicDistances[i];
        // DELAY LENGTH FOR DELAY LINES FROM SOURCE TO JUNCTION TO LISTENER
        
        // FIRST REFLECTION TIMES
        firstReflectionTimes[i] =  combinedDistances[i]/speedOfSound*Fs;
        
    }
    
    micToSourceDelay = listenerPos.distanceTo(sourcePos)/speedOfSound*Fs;

    wallFrontDelay.setDelay(jmax(firstReflectionTimes[0] - micToSourceDelay, 0.0f));
    wallBackDelay.setDelay(jmax(firstReflectionTimes[1]-micToSourceDelay, 0.0f));
    wallRightDelay.setDelay(jmax(firstReflectionTimes[2] - micToSourceDelay, 0.0f));
    wallLeftDelay.setDelay(jmax(firstReflectionTimes[3] - micToSourceDelay, 0.0f));
    wallCeilingDelay.setDelay(jmax(firstReflectionTimes[4] - micToSourceDelay, 0.0f));
    wallFloorDelay.setDelay(jmax(firstReflectionTimes[5] - micToSourceDelay, 0.0f));
}


float Reflections::largestDelay()
{
    int i;
    int n = sizeof(firstReflectionTimes) / sizeof(firstReflectionTimes[0]);

     
    // Initialize maximum element
    float max = firstReflectionTimes[0];
 
    // Traverse array elements
    // from second and compare
    // every element with current max
    for (i = 1; i < n; i++)
        if (firstReflectionTimes[i] > max)
            max = firstReflectionTimes[i];
 

    return max;


}

void Reflections::setPositions(float sourceX, float sourceY, float micX, float micY){
    
    // SET SOURCE POSITION
    sourcePos.setY(sourceY);
    sourcePos.setX(sourceX);
    sourcePos.setZ(1.1f);
    
    // SET LISTENER POSITION
    listenerPos.setY(micY);
    listenerPos.setX(micX);
    listenerPos.setZ(1.1f);
    
}



void Reflections::setSize(float roomX, float roomY, float roomZ){
    // SET ROOM SIZE
    this->roomX = roomX;
    this->roomY = roomY;
    this->roomZ = roomZ;
    
}

float Reflections::setSpeedOfSound(int temp){
//  SET SPEED OF SOUND BASED ON ROOM TEMEPRATURE USING TRUNCATED TAYLOR EXPANSION TO ESTIMATE V AT DIFFERENT TEMPERATURES
    
    speedOfSound = 331+(0.6)*temp;
    return speedOfSound;
}
