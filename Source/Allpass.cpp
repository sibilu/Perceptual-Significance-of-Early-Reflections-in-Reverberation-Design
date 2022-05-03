
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
    apf14.prepare(spec);
    apf15.prepare(spec);
    apf16.prepare(spec);
    apf17.prepare(spec);
    apf18.prepare(spec);
    apf19.prepare(spec);
    apf20.prepare(spec);
    apf21.prepare(spec);
    apf22.prepare(spec);
    apf23.prepare(spec);
    apf24.prepare(spec);
    apf25.prepare(spec);
    apf26.prepare(spec);
    apf27.prepare(spec);
    apf28.prepare(spec);
    apf29.prepare(spec);
    apf30.prepare(spec);
    apf31.prepare(spec);
    

    
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
    apf14.reset();
    apf15.reset();
    apf16.reset();
    apf17.reset();
    apf18.reset();
    apf19.reset();
    apf20.reset();
    apf21.reset();
    apf22.reset();
    apf23.reset();
    apf24.reset();
    apf25.reset();
    apf26.reset();
    apf27.reset();
    apf28.reset();
    apf29.reset();
    apf30.reset();
    apf31.reset();



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
    apf14.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf15.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf16.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf17.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf18.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf19.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf20.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf21.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf22.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf23.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf24.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf25.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf26.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf27.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf28.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf29.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf30.process(dsp::ProcessContextReplacing<float> (inputBlock));
    apf31.process(dsp::ProcessContextReplacing<float> (inputBlock));

}


void Allpass::setSampleRate(double sampleRate){
    Fs = sampleRate;
}






void Allpass::updateFilter(){
    *apf1.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    /*
    auto coeffss = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    auto N = coeffss.getFilterOrder();
    DBG(N);
     */
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
    *apf14.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf15.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf16.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf17.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf18.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf19.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf20.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf21.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf22.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf23.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf24.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf25.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf26.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf27.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf28.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf29.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf30.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
    *apf31.state = *dsp::IIR::Coefficients<float>::makeAllPass(Fs, 240);
   
}

