
#include "Test.h"
#include "Driver.h"
#include "NoiseGenerator.h"
#include "NoiseRemover.h"

#include "cpgplot.h"


void Driver::valideRMSE(double * input, double * input_noise, int size)
{
	Test * tester = new Test();
	
	
	for(int i =0; i<size; i++)
	{
		input[i]=1;
		input_noise[i]=0;
	}
	
	cout<<"Testting RMSE: "<<tester->calculateRMSE(input, input_noise, size)<<endl;
	
	for(int i =0; i<size; i++)
	{
		input[i]=1;
		input_noise[i]=1;
	}
	
	cout<<"Testting RMSE: "<<tester->calculateRMSE(input, input_noise, size)<<endl;
	
	for(int i =0; i<size; i++)
	{
		input[i]=0.5;
		input_noise[i]=1;
	}
	
	cout<<"Testting RMSE: "<<tester->calculateRMSE(input, input_noise, size)<<endl;
	
}



void Driver::generateData(double * input, double * input_noise, int size, double RFI_strength, double RFI_spread, int RFI_position, int spannedChannels)
{
	NoiseGenerator * generator = new NoiseGenerator();
	Test * tester = new Test();
	
	//Generate Gaussian Noise of Mean O and standard deviation 2
	double mean=0;
	double std_deviation=2;
	cout<<"Inserting Gaussian White Noise..."<<endl;
	generator->generateGaussianNoise(input, size, mean, std_deviation);
	cout<<"The actual noise properties: "<<endl; 
	cout<<"Mean parameter: "<<mean<<" | "<<"Standard Deviation Parameter: "<<std_deviation<<endl;
	cout<<"The actual noise properties: "<<endl; 
	tester->calculateStatistics(input, size);
	
	//Populate copy of the data set with identical noise properties
	for(int i=0; i<size; i++)
	{
		input_noise[i]=input[i];
	}
	
	//Validate the created Gaussian data sets
	if((tester->calculateRMSE(input, input_noise, size)))
	{
		cout<<"Critical Error: Data not generated correctly."<<endl;
		exit(0); 
	}

	
	//Creat source at known location
	cout<<"Inserting RFI Source..."<<endl<<endl;
	generator->insertRFISource(input, size, RFI_strength, RFI_spread, spannedChannels, RFI_position);
	
	
	
	
	//Display the RFi injected noise with GNU plot
	cout<<"Generating Automated Removal Graph..."<<endl;
	double xvals[size];
	double yvals[size];
	
	for(long long i=0; i<size; i++)
	{
		xvals[i]=i;
		yvals[i]=input[i];
	}
	
	char * commandsForGnuplot[] = {"set title \"RFI infected Noise\"", "plot 'data.temp'"};

    FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;
    for (i=0; i < size; i++)
    {
    fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
    }

    for (i=0; i < 2; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    fflush(gnuplotPipe);
    
	
}




void Driver::removeNoise(double * input, int size, double approximate_mean, double stddev, int position, int spannedChannels)
{
	//Remove RFI source (Standard Deviation Known) from the data set
	NoiseRemover * removal = new NoiseRemover();
	cout<<"Removing RFI from model with known RFI parameters..."<<endl;
	removal->removeGaussianRFI(input, size, approximate_mean, stddev, position);
	
	
	
	// Display resultant array with GNU Plot
	// Source: http://stackoverflow.com/questions/3521209/making-c-code-plot-a-graph-automatically
	cout<<"Generating Automated Removal Graph..."<<endl;
	double xvals[size];
	double yvals[size];
	
	for(long long i=0; i<size; i++)
	{
		xvals[i]=i;
		yvals[i]=input[i];
	}
	
	
	char * commandsForGnuplot[] = {"set title \"Perfect Removal Output\"", "plot 'data2.temp'"};
    FILE * temp = fopen("data2.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");  //-persistent keeps plot window open after program exit
    int i;
    for (i=0; i < size; i++)
    {
		fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
    }

    for (i=0; i < 2; i++)
    {
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot.
    }
	
}


void Driver::removeNoise_Unknowns(double * input, int size, double approximate_mean, double stddev, int position, int spannedChannels)
{
	//Remove RFI source (Standard Deviation Unknown) from the data set
	NoiseRemover * removal = new NoiseRemover();
	cout<<"Removing RFI from model with unknown RFI parameters..."<<endl;
	removal->removeGaussianRFIAdjusting(input, size, approximate_mean, stddev, position);
	
	
	
	// Display resultant array with GNU Plot
	// Source: http://stackoverflow.com/questions/3521209/making-c-code-plot-a-graph-automatically
	cout<<"Generating Automated Removal Graph..."<<endl;
	double xvals[size];
	double yvals[size];
	
	for(long long i=0; i<size; i++)
	{
		xvals[i]=i;
		yvals[i]=input[i];
	}
	
	char * commandsForGnuplot[] = {"set title \"Automated Removal Output\"", "plot 'data2.temp'"};

    FILE * temp = fopen("data2.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w"); //-persistent keeps plot window open after program exit
    int i;
    for (i=0; i < size; i++)
    {
    fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
    }

    for (i=0; i < 2; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
	
}

