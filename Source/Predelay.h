
#include <cmath>
#include "JuceHeader.h"
#include "Junction.h"
#include "Position.h"
#include "Absorption.h"
class Predelay {
    
public:
    
    // Constructor function (special function - no return type, name = Class name)
    Predelay();
    
    Predelay(float delay);
    
    // Destructor
    ~Predelay();
    
    void processBlock(dsp::AudioBlock<float> inputBlock, dsp::AudioBlock<float> & outputBlock);
    
    void setSampleRate(double sampleRate);
    void update(float predelayLength);

    void prepare(dsp::ProcessSpec spec);


private:
    
    double Fs;
   // int speedOfSound = 343; // m/sec
    
    
    // DSP DELAY LINE FOR BLOCK PROCESSING
    static const auto delaySamples = 48000*4;
    dsp::DelayLine<float,dsp::DelayLineInterpolationTypes::Linear> predelayLine {delaySamples};
    
};



