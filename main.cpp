#include <iostream>
#include <fstream>
#include "Station.h"

using namespace std;


void procedureTree(Station **stations, int size)
{
	bool mark[size];
	for (int i = 0; i < size; ++i)
	{
		mark[i] = false;
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