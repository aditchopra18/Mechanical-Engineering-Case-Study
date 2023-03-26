/*
Author- Adit Chopra
Date created- 21 October, 2021
Assignment 2: Mechanical Engineering Case Study- Flight Speed Wind Simulator
ENGR-UH-1000 Computer Programming for Engineers
Problem:
To develop a software to generate a computer simulation of wind speed for a flight simulator. 
The wind speed can be assumed as an average value and a gust value added to this average. 
The software also incorporates storms (high speed winds) and microbursts (very high speed but short-timed storms which increase the wind speed dramatically). 
The software reads the data of wind simulation and on the basis of storm probability creates storms and stores it in a file. 
Same is done for microbursts and another file is created. Finally, an output file is created which displays the final wind speeds with time.
*/

// Importing all the Header Files needed
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<cmath>

// Using standard namespace standard
using namespace std;

//Declaring Function Prototypes
void generate_wind(double wind[]);
void generate_storm(double wind[], double storm[]);
void generate_burst(double wind[], double storm[], double burst[]);
void generate_wind_simulator(double wind[], double storm[], double burst[]);

// Main Function
int main()
{
	// Declaring variable "i"
	int i;   
	
	// Opening a configuration file
	ifstream DataFile;
	
	// Opening a File and checking if it is able to open or not
	DataFile.open("simulationConfiguration.txt", ios::in);
	if (DataFile.fail())
	{
		cerr<<"File simulationConfiguration.txt can't be opened";
		exit(1); // end execution of the program
	}
	// Initializing arrays for storing data
	double wind[4], storm[4], burst[5];
   
	// Reading data from file and storing it in 3 different arrays with the help of for loop
	for(i=0;i<4;i++)
	{
		DataFile>>wind[i];
   	}

	for(i=0;i<5;i++)
	{
		DataFile>>storm[i];
	}

	for(i=0;i<5;i++)
	{
		DataFile>>burst[i];
	}
	/* 
	The Following arrays have the data-
	Wind- Average Wind Speed, gust value, simulation duration, step size
	Storm- Storm probability, min and max storm amplitude, and min and max storm duration
	Microburst probability, min and max microburst amplitude, min and max microburst duration 
	*/
	
	// Calling all the needed functions
	generate_wind(wind);
	generate_storm(wind, storm);
	generate_burst(wind, burst, burst);
	generate_wind_simulator(wind, storm, burst);
	return 0;
}

// Creating a function for the Wind Data
void generate_wind(double wind[])
{
	// Opening the file and checking if found or not
	ofstream WindSpeedData;
	WindSpeedData.open("WindSpeedData.txt");
	if(WindSpeedData.fail())
	{
		cerr<<"WindSpeedData not found";
		exit(1); // Exit The process 
	}
	else
	{
	// Initializing j to be used as counter 
	int j;
	// Defining what are the maximum values of the wind with gust values
	int max_wind=wind[0]+wind[1];
	int min_wind=wind[0]-wind[1];
	for(j=0;j<=wind[2];j=j+wind[3])
	{
		// Making a random wind speed between the min and max wind speed
		double wind_speed=rand()%(max_wind-min_wind+1) + min_wind;
		
		// Writing Data into the File
		WindSpeedData<<j<<"\t"<<wind_speed<<endl;
	}
	// Closing the file
	WindSpeedData.close();
	}
}

// Creating a function for the storm and burst data
void generate_storm(double wind[], double storm[])
{
	// Initializing Max And Min Storm Amplitude 
	int max_storm = storm[2];
	int min_storm = storm[1];
	
	// Opening 2 new files and checking if found or not
	ofstream StormData;
	StormData.open("StormData.txt");
	
	if(StormData.fail())
	{
		cerr<<"StormData not found";
		exit(1); // Exit The process 
	}
	// Code which gets executed if file exists 
	else
	{
		// Initializing 'k' to serve as counter for time 
		int k=0;
		
		// Begining the loop from time 0 to the actual duration of wind
		for(k=0;k<=wind[2];k+=wind[3])
		{
			// Choosing a random number between 0 and 10 and then dividing it by 10 to give us a random probability that storm occurs 
			double prob_storm=(rand() % 10);
			double probability_1=prob_storm/10;
			
			// Applying condition that if random probability is greater than our storm probability, storm occurs else, storm speed is 0
			if (probability_1<storm[0])
			{
				// Defining minimum and maximum duration of Storm
				int min_dur_storm=storm[3];
				int max_dur_storm=storm[4];
								
				// Finding a random storm duration
				double storm_duration=rand()%(max_dur_storm-min_dur_storm) + min_dur_storm;
				double count=0; // Defining counter variable for storm speed loop
				
				// Running a loop until our count variable becomes greater than storm_duration
				while(count<=storm_duration)
				{
					// Applying condition that the counter is less than the duration of simulation
 					if (k<=wind[2])
					{
						// Finding a random storm speed
						double storm_speed=(rand() % (max_storm-min_storm+1) + min_storm);
						// Inputing the storm speed in file
						StormData<<k<<"\t"<<storm_speed<<endl;
						// Increment the counters
						k+=wind[3];
						count+=wind[3];
					}						
					// If the counter variable exceed the simulation duration, loop breaks to avoid extra storm values
					else
					{
						break;
					}
				}
			}
			// Applying condition that if the random probability generated is less than storm probability, 
			// then storm speed is 0  
			else
			{
				int a=0;
				// Inputing that data in file  
				StormData<<k<<"\t"<<a<<endl;
				continue;
			}
		}
	}
	StormData.close();
}

void generate_burst(double wind[], double storm[], double burst[])
{
	// Initializing Max And Min Storm Amplitude and Burst Amplitude 
	int max_burst = burst[2];
	int min_burst = burst[1];
	
	// Opening 2 new files (one in output stream and one in input stream) and checking if found or not
	ifstream StormData;
	StormData.open("StormData.txt");
	
	ofstream BurstData;
	BurstData.open("BurstData.txt");
	
	if (StormData.fail() || BurstData.fail())
	{
		cerr<<"StormData or BurstData not found";
		exit(1); // Exit The process 
	}
	
	// Code which gets executed if file exists 
	else
	{
		// Finding the size of the array which will include storm data
		int size=2*wind[2];
		
		// Defining storm_array time and speed with a length of integer variable "size"
		double storm_array_time[size], storm_array_speed[size];
		
		// Initializing counters
		int i=0, j=0;
		// Running two nested loops so that data can be respectively entered into the respective Storm Arrays
		for(i=0;i<=size;i=i+wind[3])
		{
			for(j=0;j<2;j++)
			{
				if (j%2==0)
				{
					// Inputing Data from file to array storm_array_time
					StormData>>storm_array_time[i];
				}
				else
				{
					// Inputing Data from file to array storm_array_speed
					StormData>>storm_array_speed[i];
				}
			}
		}
		// Closing the storm Data File 
		StormData.close();

		// Running a loop so that Burst Data is generated according to Storm Data
		while (j<=wind[2])
		{
			if (storm_array_speed[j]!=0)
			{
				// Finding a random probability 
				double prob_burst=(rand() % 10);
				double probability_2=prob_burst/10;	
				
				// Defining Minimum and Maximum values of Burst Duration
				int min_dur_burst=burst[3];
				int max_dur_burst=burst[4];				
				
				if (probability_2<burst[0])
				{
					// Finding a random burst duration
					double burst_duration=rand()%(max_dur_burst-min_dur_burst) + min_dur_burst;
					double iter=0; // Defining counter variable for burst speed loop
					
					// Running loop for inputting Microburst Data to file 
					for (iter=0;iter<=burst_duration;iter+=wind[3])
					{
						if(storm_array_speed[j]!=0)
						{
							double burst_speed=rand()%(max_burst-min_burst+1) + min_burst;
							BurstData<<j<<"\t"<<burst_speed<<endl;
							j+=wind[3];
						}
						else
						{
							BurstData<<j<<"\t"<<0<<endl;	
							j+=wind[3];
						}
					}
				}
				else
				{
					int z=0;
					// Inputing zero values to burst speed
					BurstData<<j<<"\t"<<z<<endl;
					j+=wind[3];		
				}		
			}
			else 
			{
				j+=wind[3];
				continue;
			} 	
		} 
	}
	BurstData.close();	
}


void generate_wind_simulator(double wind[], double storm[], double burst[])
{
	int size=2*wind[2];
	double storm_array_time[size], storm_array_speed[size];
	ifstream StormData;
	StormData.open("StormData.txt");
	int i=0, j=0;
	// Running two nested loops so that data can be respectively entered into the respective Storm Arrays
	for(i=0;i<=size;i=i+wind[3])
	{
		for(j=0;j<2;j++)
		{
			if (j%2==0)
			{
				// Inputing Data from file to array storm_array_time
				StormData>>storm_array_time[i];
			}
			else
			{
				// Inputing Data from file to array storm_array_speed
				StormData>>storm_array_speed[i];
			}
		}
	}
	// Closing the storm Data File 
	StormData.close();
	
	double wind_array_time[size], wind_array_speed[size];
	ifstream WindData;
	WindData.open("WindSpeedData.txt");
	// Running two nested loops so that data can be respectively entered into the respective Storm Arrays
	for(i=0;i<=size;i=i+wind[3])
	{
		for(j=0;j<2;j++)
		{
			if (j%2==0)
			{
				// Inputing Data from file to array storm_array_time
				WindData>>wind_array_time[i];
			}
			else
			{
				// Inputing Data from file to array storm_array_speed
				WindData>>wind_array_speed[i];
			}
		}
	}
	// Closing the storm Data File 
	WindData.close();
		
	double burst_array_time[size], burst_array_speed[size];
	ifstream BurstData;
	BurstData.open("BurstData.txt");
	// Running two nested loops so that data can be respectively entered into the respective Storm Arrays
	for(i=0;i<=size;i=i+wind[3])
	{
		for(j=0;j<2;j++)
		{
			if (j%2==0)
			{
				// Inputing Data from file to array storm_array_time
				BurstData>>burst_array_time[i];
			}
			else
			{
				// Inputing Data from file to array storm_array_speed
				BurstData>>burst_array_speed[i];
			}
		}
	}
	// Closing the storm Data File 
	BurstData.close();
	
	ofstream WindSimulator;
	WindSimulator.open("WindSimulator.txt");
	for(i=0;i<=wind[2];i=i+wind[3])
	{
		WindSimulator<<i<<"\t"<<burst_array_speed[i]+storm_array_speed[i]+wind_array_speed[i]<<endl;
	}
	WindSimulator.close();	
}
