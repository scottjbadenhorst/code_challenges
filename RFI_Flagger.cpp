
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>

#include "Driver.h"
#include "Test.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



//#include "python2.7/Python.h"
//#include <Python.h>

#define NUM_POINTS 5
#define NUM_COMMANDS 2

using namespace std;


int main(int argc,char *argv[])
{
	Driver * driver = new Driver();
	Test * tester = new Test();
	
	//set size of dataset
	long long size=1000;
	
	//create 1D spectral line	
	double * input;
	input=(double*)malloc(size*sizeof(double));
	memset(input, 0, (size)*sizeof(double));
	
	
	//create 1D spectral line	
	double * auto_input;
	auto_input=(double*)malloc(size*sizeof(double));
	memset(auto_input, 0, (size)*sizeof(double));
	
	//(COPY) 1D spectral array
	//Stores initial Gaussian Noise in the dataset
	double * input_noise;
	input_noise=(double*)malloc(size*sizeof(double));
	memset(input_noise, 0, (size)*sizeof(double));
	
	double originalRMSE=0;
	double finalRMSE=0;
	
	if(argc>1){		
		for(int i=1; i<2;i++)
		{			
			//INPUT Paramaters: 1 = flag, 2= Char*
			if(!strcmp(argv[i],"USERMODE"))
			{
				cout<<"UserMode:" <<endl;
				cout<<"=================================================="<<endl;
				cout<<"Functions identically to Test mode run"<<endl;
				cout<<"Values for RFI strength and position promted from user."<<endl<<endl;
				
				
				double RFI_strength=20;
				double RFI_spread=0.5;
				int RFI_channelsSpanned=5;
				
				//Test mode: RFI source position known
				double RFI_position=size/2;
				
				//Generate data with Gaussian white noise (Box-Muller) and a single RFI source
				driver->generateData(input, input_noise,size, RFI_strength, RFI_spread ,RFI_position, RFI_channelsSpanned);  //insert Gaussian noise and 
				originalRMSE=tester->calculateRMSE(input, input_noise,size);
				
				//generate a second copy for the automated noise removal
				for(int i=0; i<size; i++){
					auto_input[i]=input[i];
				}
				
				 cout<<"Consult the generated GNU Plot (RFI infected noise)"<<endl;
				 cout << "Please enter a double for the maximum value of the identified noise in GNU Plot (RFI Infected Noise): ";
				 cin >> RFI_strength;
				 cout << "Please enter an integer for the middle position of the identified noise in GNU Plot (RFI Infected Noise): ";
				 cin >> RFI_position;
				 
				 //Perfect solution: All parameters known
				//Display Root Mean Square Error against data set containing white noise only
				driver->removeNoise(input,size, RFI_strength, RFI_spread, RFI_position, RFI_channelsSpanned);
				finalRMSE=tester->calculateRMSE(input, input_noise,size);
				cout<<"Final RMSE for Perfect Removal: "<<finalRMSE<<endl<<endl;
				
				//Automated Soloution: RFI Spread (Shape) unknown
				//Writes generated fitted Gaussian kernel to file for future automated detection
				//Display Root Mean Square Error against data set containing white noise only
				
				driver->removeNoise_Unknowns(auto_input,size, RFI_strength, RFI_spread, RFI_position, RFI_channelsSpanned);
				finalRMSE=tester->calculateRMSE(auto_input, input_noise,size);
				cout<<"Final RMSE for Automated Removal: "<<finalRMSE<<endl;
				 
			}
			else if(!strcmp(argv[i],"TESTMODE"))
			{
				cout<<"TestMode:" <<endl;
				cout<<"=================================================="<<endl<<endl;
				
				double RFI_strength=20;
				double RFI_spread=0.5;
				int RFI_channelsSpanned=5;
				
				//Test mode: RFI source position known
				double RFI_position=size/2;
				
				//Generate data with Gaussian white noise (Box-Muller) and a single RFI source
				driver->generateData(input, input_noise,size, RFI_strength, RFI_spread ,RFI_position, RFI_channelsSpanned);  //insert Gaussian noise and 
				originalRMSE=tester->calculateRMSE(input, input_noise,size);
				
				//generate a second copy for the automated noise removal
				for(int i=0; i<size; i++){
					auto_input[i]=input[i];
				}
				
				
				/* Future development:
				 * Implement Smoothing function to increase chances of accurate RFI profile extraction
				 * No time constraint: Wavelete Reconstruction
				 * Time constraint: Simple Box or Gaussian smoothing
				 */
				
				
				//Perfect solution: All parameters known
				//Display Root Mean Square Error against data set containing white noise only
				driver->removeNoise(input,size, RFI_strength, RFI_spread, RFI_position, RFI_channelsSpanned);
				finalRMSE=tester->calculateRMSE(input, input_noise,size);
				cout<<"Final RMSE for Perfect Removal: "<<finalRMSE<<endl<<endl;
				
				//Automated Soloution: RFI Spread (Shape) unknown
				//Writes generated fitted Gaussian kernel to file for future automated detection
				//Display Root Mean Square Error against data set containing white noise only
				
				driver->removeNoise_Unknowns(auto_input,size, RFI_strength, RFI_spread, RFI_position, RFI_channelsSpanned);
				finalRMSE=tester->calculateRMSE(auto_input, input_noise,size);
				cout<<"Final RMSE for Automated Removal: "<<finalRMSE<<endl;
				
				
				
			}
			else
			{
				cout<<"No parameter given"<<endl;
				cout<<"Suggested: TESTMODE"<<endl;
			}
		}
	
	}
	
	
	
	//driver->valideRMSE(input, input_noise,size);
	
	//driver->TestRun(input, input_noise,size);

	//std::cout<<"RMSE Before Removal: "<<tester->calculateRMSE(input, input_noise,size)<<std::endl;
	
	//driver->removeNoise(input,size, 20, 0.5, 100);
	
    //std::cout<<"RMSE After Removal: "<<tester->calculateRMSE(input, input_noise,size)<<std::endl;
	
  
	
}
