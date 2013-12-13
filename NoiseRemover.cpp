

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "iomanip"
#include <ostream>
#include <iostream>

#include <algorithm>
#include "NoiseRemover.h"
#include "Test.h"
#include <typeinfo>

#include <iostream>
#include <fstream>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


void NoiseRemover::removeGaussianRFI(double * input, int size, double approximate_mean, double stddev, int position)
{
	
	double * source;
	double * source_compare;
	int source_width=5;//spannedChannels;
	
	double mean=approximate_mean;
	double sigma=stddev;
	
	source=(double*)malloc(size*sizeof(double));
	memset(source, 0, (size)*sizeof(double)); 
	
	
    double r, s = 2.0 * sigma * sigma;
 
    //sum kernel values
    double sum = 0.0;
 
	Test * tester = new Test();
 
		// generate kernel (5x5) to represent RFI
		for (int x = -2; x <= 2; x++)
		{
				r = sqrt(x*x);
				source[x + 2] = (exp(-(r*r)/s))/(M_PI * s);
				sum += source[x + 2];	
		}
		
		//Normalise kernel
		//Remove scaled kernel from the data
		for(int i = -2; i < 3; ++i)
		{        
			source[i+2]/= sum;
			source[i+2]*=approximate_mean;
			input[position+i]-=source[i+2];
		}
}


void NoiseRemover::removeGaussianRFIAdjusting(double * input, int size, double approximate_mean, double stddev, int position)
{
	Test * tester = new Test();
	
	double * source;
	double * source_compare;
	int source_width=5; //spannedChannels;
	size=source_width;
	
	double mean=approximate_mean;
	double sigma=stddev;
	
	source=(double*)malloc(size*sizeof(double));
	memset(source, 0, (size)*sizeof(double)); 
	
	source_compare=(double*)malloc(size*sizeof(double));
	memset(source_compare, 0, (size)*sizeof(double)); 
	

    double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization

 
	double best_sigma=0;
	double best_mean=-1000;
	double best_rmse=1000;
	//int best_position=1000;
	

		
	//generate 1000 5x5 kernels 	
	for( int z=1; z<1000; z++)
	{	
		sigma=z/(double)1000;
		double sum = 0.0;
		
		r=2.0 * sigma * sigma;
		s=2.0 * sigma * sigma;
		for (int x = -2; x <= 2; x++)
		{
			
				r = sqrt(x*x);
				source[x + 2] = (exp(-(r*r)/s))/(M_PI * s);
				sum += source[x + 2];
			
		}
		
		
		for(int i = -2; i < 3; ++i)
		{        
			source[i+2]/= sum;
			source[i+2]*=approximate_mean;       
			source_compare[i+2]=input[position+i];			
		}
		
		double rmse= tester->calculateRMSE(source, source_compare, size);
		
		
		if(rmse<best_rmse)
		{
			best_sigma=sigma;	
			best_rmse=rmse;
		
		}
		
	}
	
	sigma=best_sigma;
    cout<<"Calculated Sigma: "<<sigma<<endl;
    
    

    //Generate fitted kernel
    double sum = 0.0;
    r=2.0 * sigma * sigma;
	s=2.0 * sigma * sigma;
    //// generate 5x5 kernel
    for (int x = -2; x <= 2; x++)
    {
            r = sqrt(x*x);
            source[x + 2] = (exp(-(r*r)/s))/(M_PI * s);
            sum += source[x + 2]; 
    }
    
    // normalize fitted kernel
    // Remove scaled fitted kernel from data
    for(int i = -2; i < 3; ++i)
    {        
		source[i+2]/= sum;
		source[i+2]*=approximate_mean;
		
		input[position+i]-=source[i+2];
    }
	
	
	
	
}
