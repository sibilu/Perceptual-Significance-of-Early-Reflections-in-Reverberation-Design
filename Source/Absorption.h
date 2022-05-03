


#pragma once
#include <cmath>
#include <iostream>
#include "JuceHeader.h"

class Absorption
{
    

	public:
    
    void processBlock(dsp::AudioBlock<float> & inputBlock);
	
    void prepareFilter(dsp::ProcessSpec spec);
	
    void updateFilter(int material);
    
	Absorption();
	~Absorption() {}
    
private:

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;

};

