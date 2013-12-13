#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "iomanip"
#include <ostream>
#include <iostream>

#include <algorithm>
#include "NoiseGenerator.h"
#include <typeinfo>

#include <iostream>
#include <fstream>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double NoiseGenerator::BoxMuller(double mean, double stddev)
{
	static double n2 = 0.0;
    static int n2_cached = 0;
	
	 if (!n2_cached)
	{	 
		double x, y, r;
		do 
		{
			x = 2.0*rand()/RAND_MAX - 1;
			y = 2.0*rand()/RAND_MAX - 1;
			
			r = x*x + y*y;
		}while (r == 0.0 || r > 1.0);
		
		double d = sqrt(-2.0*log(r)/r);
		double n1 = x*d;
		n2 = y*d;
	
		double result = n1*stddev + mean;
		
		n2_cached = 1;
        return result;
	}
	else
	{
		n2_cached = 0;
        return n2*stddev + mean;
	}
	
}

void NoiseGenerator::generateGaussianNoise(double * input, long long size, double mean, double std_deviation)
{	
	srand(time(NULL));
	
	for (int i = 1; i < size; i++)
    {
		input[i]+= BoxMuller(mean, std_deviation);
	}
  
}


void NoiseGenerator::insertRFISource(double * input, long long size, double RFI_strength, double RFI_spread, int spannedChannels, int channelPosition)
{
	
	double * source;
	int source_width=spannedChannels;
	
	double mean=RFI_strength;
	double sigma=RFI_spread;
	
	source=(double*)malloc(size*sizeof(double));
	memset(source, 0, (size)*sizeof(double)); 
	
    double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization
    double sum = 0.0;
 
    // generate 5x5 kernel
    for (int x = -2; x <= 2; x++)
    {
            r = sqrt(x*x);
            source[x + 2] = (exp(-(r*r)/s))/(M_PI * s);
            sum += source[x + 2];   
    }
 
    // normalize the Kernel
    for(int i = -2; i < 3; ++i)
    {        
		source[i+2]/= sum;
		source[i+2]*=RFI_strength;
		//cout<<"Original values: "<<input[channelPosition+i]<<endl;
		input[channelPosition+i]+=source[i+2];
		//cout<<"Updated values: "<<input[channelPosition+i]<<endl;
    }
	
	
	
	
	
	
	//Write filter to file
	ofstream myfile;
	myfile.open ("filter.txt", ios::out | ios::app);
  
	for(int i=0; i<source_width; i++)
	{
		myfile << source[i]<<" ";
	}
	myfile<<endl;
	myfile.close();
	
	
	
	////how to read in the filters
	//ifstream fin("filter.txt");
    //string str;
    ////read a line into 's' from 'fin' each time
    //for(int i=0; i<3 && getline(fin,str); i++){
        ////use the string 's' as input stream, the usage of 'sin' is just like 'cin'
           //istringstream sin(str);
           //double sum = 0.0, tmp;
           //while(sin>>tmp){
              ////cout<<tmp<<endl;
           //}

    //}
	
	

	
	
}
