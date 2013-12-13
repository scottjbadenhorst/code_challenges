
#include "Test.h"
#include "math.h"


void Test::calculateStatistics(double * input, long long size)
{
	double mean=0;
	double std_deviation=0;
	double variance=0;
	
	for(long long i=0; i<size; i++)
	{
		mean+=input[i];
	}
	mean/=size;
	
	for(long long i=0; i<size; i++)
	{
		//square_diff=local_mean-map[i];	
		
		variance+=((mean-input[i])*(mean-input[i]));
	} 
	double stddev= sqrt(variance/size);
	
	std::cout<<"Mean: "<<mean<<" | Standard deviation: "<<stddev<<std::endl;
	
}

double Test::calculateRMSE(double * input, double * input_noise, int size)
{
	double rmse=0;
	
	for(long long i=0; i<size; i++)
	{
		rmse+=((input[i]-input_noise[i])*(input[i]-input_noise[i]));
		
	}
	 rmse/=(double)size;
	 
	 return sqrt(rmse);
}
