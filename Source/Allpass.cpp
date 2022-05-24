
#include "Allpass.h"


Allpass::Allpass(){

}

// Destructor
Allpass::~Allpass(){
}

void Allpass::prepareFilter(dsp::ProcessSpec spec){
 
    
    apf1.prepare(spec);
    apf2.prepare(spec);
    apf3.prepare(spec);
    apf4.prepare(spec);
    apf5.prepare(spec);
    apf6.prepare(spec);
    apf7.prepare(spec);
    apf8.prepare(spec);
    apf9.prepare(spec);
    apf10.prepare(spec);
    apf11.prepare(spec);
    apf12.prepare(spec);
    apf13.prepare(spec);

    
    apf1.reset();
    apf2.reset();
    apf3.reset();
    apf4.reset();
    apf5.reset();
    apf6.reset();
    apf7.reset();
    apf8.reset();
    apf9.reset();
    apf10.reset();
    apf11.reset();
    apf12.reset();
    apf13.reset();
 

}



void Allpass::processBlock(dsp::AudioBlock<float> &inputBlock){
    apf1.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf2.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf3.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf4.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf5.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf6.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf7.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf8.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf9.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf10.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf11.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf12.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf13.process(dsp::ProcessContextReplacing<float> (inputBlock));
   

}


void Allpass::setSampleRate(double sampleRate){
    Fs = sampleRate;
}






void Allpass::updateFilter(){
    // CASCADING APFS. FILTER ORDER = 26
    *apf1.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf2.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf3.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf4.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf5.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf6.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf7.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf8.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf9.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf10.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf11.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf12.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf13.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
   
}

