
#include <cmath>
#include "JuceHeader.h"
#include "Junction.h"
#include "Position.h"
#include "Absorption.h"
class Reflections {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Reflections();
    
    Reflections(float delay, float modSpeed);
    
    // Destructor
    ~Reflections();
    
    void processBlock(dsp::AudioBlock<float> inputBlock, dsp::AudioBlock<float> & outputBlock0, dsp::AudioBlock<float> & outputBlock1, dsp::AudioBlock<float> & outputBlock2, dsp::AudioBlock<float> & outputBlock3, dsp::AudioBlock<float> & outputBlock4, dsp::AudioBlock<float> & outputBlock5);
    
    void update(int materialFrontBack, int materialLeftRight, int materialCeilingFloor);
    void setPositions(float sourceX, float sourceY, float micX, float micY);
    void setSampleRate(double sampleRate);
    void setSize(float roomX, float roomY, float roomZ);
    float setSpeedOfSound(int temp);
    
    void prepare(dsp::ProcessSpec spec);
    float junctionMicStereoGain(int junctionIndex, int channel);
    float sourceMicStereoGain(int channel);
    float invDistLaw(int channel);
    float getDist(int junctionIndex);
    
    float getWallDelay(int wallIndex);
    const static int junctionCount = 6;

    int firstReflectionTimes[junctionCount];
    float micToSourceDelay;
    bool filtersOnOff = true;

    float largestDelay();
     
private:
    Position sourcePos;
    Position listenerPos;

    Junction junction[junctionCount] = {};


    float roomX; float roomY; float roomZ;
    float speedOfSound;
    
    float junctionAzimuth;
    float junctionGain;
    float inputGain;
    
    double Fs;
   // int speedOfSound = 343; // m/sec
    
    const static int order = junctionCount-1;
    
    float outFirstReflections[junctionCount];
    float outSourceToJunction[junctionCount];
    float outJunctionToMic[junctionCount];
    float sourceToJunctionDistances[junctionCount];
    float combinedDistances[junctionCount];
    float junctionToMicDistances[junctionCount];
    float sourceToJunctionToMicDelayTimes[junctionCount];

    
    // DSP DELAY LINE FOR BLOCK PROCESSING
    static const auto delaySamples = 48000*4;
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> micSourceDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallFrontDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallBackDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallRightDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallLeftDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallCeilingDelay {delaySamples};
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> wallFloorDelay {delaySamples};
    
    Absorption wallFrontAbsorption;
    Absorption wallBackAbsorption;
    Absorption wallRightAbsorption;
    Absorption wallLeftAbsorption;
    Absorption wallCeilingAbsorption;
    Absorption wallFloorAbsorption;

  // auto wallFrontBlock = dsp::AudioBlock<float>();

    

};



