#ifndef DRIVER_H
#define DRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <cstdlib>
#include <string>
#include <limits>
#include <time.h>


#include "NoiseGenerator.h"
#include "Test.h"


using namespace std;

class Driver
{
	public:
		void valideRMSE(double * input, double * input_noise, int size);
		void generateData(double *input, double * input_noise, int size, double RFI_strength, double RFI_spread, int RFI_position, int spannedChannels);
		void removeNoise(double * input, int size, double RFI_strength, double RFI_spread, int RFI_position, int spannedChannels);
		void removeNoise_Unknowns(double * input, int size, double approximate_mean, double stddev, int position, int spannedChannels);

};

#endif //DRIVER_H
