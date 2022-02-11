/*
 ==============================================================================
 
 am_IIRFilter.cpp
 Created: 30 May 2019 3:31:29pm
 Author:  Emanuele Parravicini
 
 ==============================================================================
 */

#include "am_std_libs.h"
    
#include "am_IIRFilter.h"
    
    am_IIRFilter::am_IIRFilter()
    {
        x = nullptr;
        y = nullptr;
    }
    
    am_IIRFilter::~am_IIRFilter()
    {
        if(x) delete [] x;
        if(y) delete [] y;
        
        x = nullptr;
        y = nullptr;
        
        Na = 0;
        Nb = 0;
    }
    
    
    void am_IIRFilter::setCoeff(double _b[], int _Nb, double _a[], int _Na)
    {
        a = _a;
        b = _b;
        Na = _Na;
        Nb = _Nb;
        
        if(x) delete [] x;
        if(y) delete [] y;
        
        y = new double[Na];
        x = new double[Nb];
        
        for(int i=0; i<Na; i++) y[i] = 0;
        for(int i=0; i<Nb; i++) x[i] = 0;
    }
    
    double am_IIRFilter::process(double x0)
    {
        if(!x || !y) return 0.0;
        
        double B = 0;
        double A = 0;
        
        for(int i = Nb-1; i > 0; i--)
        {
            // shift
            x[i] = x[i-1];
            
            // zeros processing
            B += b[i] * x[i];
        }
        x[0] = x0;
        B += b[0] * x[0];
        
        for(int i = Na-1; i > 0; i--)
        {
            // shift
            y[i] = y[i-1];
            
            // poles proccessing
            A += a[i] * y[i];
        }
        
        y[0] = B - A;
        
        return y[0];
        
    }
    
    void am_IIRFilter::printCoeff()
    {
        std::cout << "b(n): ";
        for(int i = 0; i < Nb; i++)
        {
            std::cout << b[i] << " ";
        }
        std::cout << "\n\n";
        
        
        std::cout << "a(n): ";
        for(int i = 0; i < Na; i++)
        {
            std::cout << a[i] << " ";
        }
        std::cout << "\n\n";
        
    }

