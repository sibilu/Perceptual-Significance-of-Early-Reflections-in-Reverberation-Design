
#pragma once
#include "am_std_libs.h"
#include "am_IIRFilter.h"

using namespace std;

class RandomAPF
{
    
public:
    
    RandomAPF() { seed = 0; }
    ~RandomAPF() {}
    
    // Function to calculate polynomial coefficients.
    void vietaFormula(complex<double> coeff[], complex<double> roots[], int n);
    
    void generateRandAllPassIR(double irOut[], int irLength, int allPassOrder, double dump, int seed);
    
    void generateRandAllPassFilterCoeffs(double b[], double a[], int allPassOrder, double dump, int seed);
    
    void printRoots(complex<double> r[], int size);
    
    void setFilterParams();
    int seed;
};
