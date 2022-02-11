
#include "RandomAPF.h"
#include <iostream>
#include "am_std_libs.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif
using namespace std;


    
    // Function to calculate polynomial
    // coefficients.
    void RandomAPF::vietaFormula(complex<double> coeff[], complex<double> roots[], int n)
    {
        for (int i = 1; i <= n; i++) {
            for (int j = n - i - 1; j < n; j++) {
                coeff[j] = coeff[j] -1.0 * roots[i - 1] * coeff[j + 1];
            }
        }
        
    }
    
    void RandomAPF::generateRandAllPassFilterCoeffs(double b[], double a[], int allPassOrder, double dump, int seed)
    {
        int N = allPassOrder;
        
        // Declare an array for polynomial coefficient
        complex<double>* coeff = new complex<double>[N];
        
        // Set all coefficients as zero initiall
        memset(coeff, 0, N * sizeof(complex<double>));
        
        // Set highest order coefficient as 1
        coeff[N-1] = 1;
        
        // Initialise an array by root of polynomial
        complex<double>* roots = new complex<double>[N-1];
        
        
        // generates random complex conjugate pole pairs
        for(int k = 0; k < (N-1)/2; k++)
        {

            srand(seed);
            double rnd = (double)rand() / RAND_MAX;
            double rndDump = dump * (1.0 +  (((double)rand() / RAND_MAX)*0.02) - 0.01);
            
            double theta = M_PI * rnd;
            complex<double> p1 = rndDump * exp(1i * theta);
            complex<double> p2 = rndDump * exp(-1i * theta);
            
            roots[k] = p1;
            roots[k+(N-1)/2] = p2;
            
            // Print Roots
            // std::cout<< "p1: " << real(p1) << " + " << imag(p1) << "i \n";
            // std::cout<< "p2: " << real(p2) << " + " << imag(p2) << "i \n";
            
        }
        
        // find coeff from roots
        vietaFormula(coeff, roots, N-1);
        
        for (int i = N-1; i >= 0; i--)
        {
            b[i] = real(coeff[i]);
            a[N-1-i] = b[i];
        }
        
        // Print Roots
        printRoots(roots, N-1);
        
        delete [] coeff;
        delete [] roots;
        
    }
    
    void RandomAPF::printRoots(complex<double> r[], int size)
    {
        std::cout<< "roots:  ";
        for (int i = 0; i<size; i++)
        {
            std::cout<< real(r[i]) << " + " << imag(r[i]) << "i ";
        }
        std::cout<< "\n\n";
    }
    
    
    void RandomAPF::generateRandAllPassIR(double irOut[], int irLength, int allPassOrder, double dump, int seed)
    {
        int N = allPassOrder;
        
        // All-Pass transfer function
        double* a = new double[N];
        double* b = new double[N];
        
        generateRandAllPassFilterCoeffs(b, a, N, dump, seed);
        
        // generates Impulse Response
        
        am_IIRFilter filter;
        filter.setCoeff(b, N, a, N);
        
        for(int n = 0; n < irLength; n++)
        {
            if(n == 0) irOut[0] = filter.process(1.0);
            else irOut[n] = filter.process(0.0);
        }
        
        delete [] b; b = nullptr;
        delete [] a; a = nullptr;
    }


