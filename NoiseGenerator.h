
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>

#include "math.h"

#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

class NoiseGenerator
{
  public:
      void generateGaussianNoise(double * input, long long size, double mean, double std_deviation);
      double BoxMuller(double mean, double std_deviation);
	  void insertRFISource(double * input, long long size, double RFI_strength, double RFI_spread, int spannedChannels, int channelPosition);
  
};

#endif
