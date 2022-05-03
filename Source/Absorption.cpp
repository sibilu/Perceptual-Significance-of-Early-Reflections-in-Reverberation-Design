

#include "Absorption.h"
#include <iostream>



Absorption::Absorption() {}


void Absorption::prepareFilter(dsp::ProcessSpec spec){
    filter.prepare(spec);
    filter.reset();
    
}




void Absorption::updateFilter(int material) {
    
    
    
    switch (material) {
        case 1:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(   0.36506,-0.98224,0.91615,-0.29506,1,-2.7729,2.6578,-0.87931));// Carpet coefficients

            *filter.state = *coeffs;

        break;
        }
        case 2:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.27696,-0.7732,0.74334,-0.24574,1,-2.8415,2.7776,-0.93362));// Carpet coefficients

            *filter.state = *coeffs;        break;
        }
        case 3:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.35781,-0.64455,0.403,-0.079873,1,-1.7897,1.1156,-0.2204));// Carpet coefficients

            *filter.state = *coeffs;        break;
        }
        case 4:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.74316,-1.6734,1.339,-0.37964,1,-2.234,1.7782,-0.50149));// Carpet coefficients

            *filter.state = *coeffs;            break;}
        case 5:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.92974,-2.3478,2.0974,-0.67107,1,-2.5247,2.2552,-0.72151));// wood

            *filter.state = *coeffs;        break;
        }
        case 6:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.97909,-2.8058,2.7643,-0.93571,1,-2.8639,2.8198,-0.95391));// Carpet coefficients

            *filter.state = *coeffs;        break;
        }
            
        case 7:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.88943,-2.3347,2.1179,-0.66912,1,-2.6237,2.3793,-0.75151));// Carpet coefficients

            *filter.state = *coeffs;        break;
        }
            
        case 8:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.88908,-2.389,2.2315,-0.72371,1,-2.6631,2.4684,-0.79436));// Carpet coefficients

            *filter.state = *coeffs;        break;
        }
        default:{
            dsp::IIR::Coefficients<float>::Ptr coeffs (new dsp::IIR::Coefficients<float>(0.36094,-0.050902,-0.19755,0.073891,1,-1.0925,0.37591,-0.021316));// Carpet coefficients

            *filter.state = *coeffs;        }
  
    }
    
    
    }

void Absorption::processBlock(dsp::AudioBlock<float> & inputBlock) {
    
    filter.process(dsp::ProcessContextReplacing<float> (inputBlock));
    
}



