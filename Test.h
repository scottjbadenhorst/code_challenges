
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <time.h>
#include <cstdlib>
#include <string>

#include <string.h>
#include <iostream>

using namespace std;


class Test
{
	public: 
		void calculateStatistics(double * input, long long size);
		double calculateRMSE(double * input, double * input_noise, int size);
		
	
};

#endif //TESTING_H
