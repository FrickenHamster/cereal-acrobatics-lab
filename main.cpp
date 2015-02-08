#include <iostream>
#include <fstream>
#include <math.h>
#include "Station.h"

using namespace std;



void ACSF(int* xlist, int* ylist, int num, int start)
{
	long long int * rates = new long long int[num];
	//unmark stations

	bool * mark = new bool[num];
	
	for (int i = 0; i < num; ++i)
	{
		mark[i] = false;
	}
	mark[start] = true;
	for (int i = 2; i < num; ++i)
	{
		long long int lowd = -1;
		int lowid = -1;
		for (int j = 0; j < num; ++j)
		{
			if (j == start || mark[j])
				continue;
			long long int dd = pow(xlist[start] - xlist[j], 2) + pow(ylist[start] - ylist[j], 2);
			if (lowd == -1 || dd < lowd)
			{
				lowid = j;
				lowd = dd;
			}
		}
		
		rates[lowid] = 0;
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