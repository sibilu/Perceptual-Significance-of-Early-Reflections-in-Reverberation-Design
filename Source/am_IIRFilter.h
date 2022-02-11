/*
  ==============================================================================

    am_IIRFilter.h
    Created: 30 May 2019 3:31:29pm
    Author:  Emanuele Parravicini

  ==============================================================================
*/

#pragma once

/**
 y[0] = x[0] * b[0] + x[1] * b[1] + x[2] * b[2] ... - (y[1] * a[1] + y[2] * a[2] + y[3] * a[3] + ...)
 where:
   x[0] = x0 = most recent input sample
   a[0] must be 1, i.e. a and b must be already normalized
 */

class am_IIRFilter
{
public:
    
    am_IIRFilter();
    ~am_IIRFilter();
    
    void setCoeff(double _b[], int _Nb, double _a[], int _Na);
    double process(double x0);
    
    void printCoeff();
    
private:
    
    double* a = nullptr;
    double* b = nullptr;
    int Na = 0;
    int Nb = 0;
    
    // internal state
    
    double* x = nullptr;
    double* y = nullptr;
};
