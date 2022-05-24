
#include "Predelay.h"


Predelay::Predelay(){

}

// Destructor
Predelay::~Predelay(){
}

void Predelay::prepare(dsp::ProcessSpec spec){
    predelayLine.prepare(spec);
    predelayLine.reset();
}




void Predelay::processBlock(dsp::AudioBlock<float> inputBlock, dsp::AudioBlock<float> & outputBlock){
    predelayLine.process(juce::dsp::ProcessContextNonReplacing<float> (inputBlock, outputBlock));
}


void Predelay::setSampleRate(double sampleRate){
    Fs = sampleRate;
}



void Predelay:: update(float predelayLength){
    predelayLine.setDelay(20000);
}

