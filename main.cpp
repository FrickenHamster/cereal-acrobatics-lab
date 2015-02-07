#include <iostream>
#include <fstream>
#include "Station.h"

using namespace std;



void ACSF(int* xlist, int* ylist, int num, Station * start)
{
	long long int * rates = new long long int[num];
	//unmark stations

	bool * mark = new bool[num];
	
	for (int i = 0; i < num; ++i)
	{
		
	}
	for (int i = 2; i < num; ++i)
	{

		for (int j = 0; j < num; ++j)
		{
			
		}
	}
}


int main(int argc, char **argv)
{
	int method, stationNum, sourceStation;

	fstream file;
	file.open(argv[0]);
	
	file >> method;
	file >> stationNum;
	file >> sourceStation;


	for (int i = 0; i < stationNum; ++i)
	{
		
	}

	return 0;
}