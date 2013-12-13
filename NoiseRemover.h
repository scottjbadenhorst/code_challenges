
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>

#include "math.h"

#ifndef NOISEREMOVER_H
#define NOISEREMOVER_H

class NoiseRemover
{
  public:
      void removeGaussianRFI(double * input, int size, double approximate_mean, double std_deviation, int position);
      void removeGaussianRFIAdjusting(double * input, int size, double approximate_mean, double std_deviation, int position);
  
};

#endif //TESTING_H
