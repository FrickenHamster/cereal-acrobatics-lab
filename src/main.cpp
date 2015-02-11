#include <iostream>
#include <fstream>
#include <math.h>
#include "Station.h"
#include "Tree.h"

using namespace std;



void ACSF(Station ** stations, int num, int source)
{
	long long int * rates = new long long int[num];
	long long int * p = new long long int[num];
	long long int * q = new long long int[num];
	//unmark stations
	
	Station ** markedStations = new Station*[num];
	int * markedIndex = new int[num];
	int markedNum = 0;

	bool * mark = new bool[num];
	
	for (int i = 0; i < num; ++i)
	{
		mark[i] = false;
	}
	
	mark[source] = true;
	markedStations[markedNum] = stations[source];
	markedIndex[markedNum] = source;
	markedNum++;
	
	for (int i = 2; i < num; ++i)
	{
		long long int lowd = -1;
		int lowid = -1;
		for (int j = 0; j < num; ++j)
		{
			if (j == source || mark[j])
				continue;
			long long int dd = pow(stations[source]->getX() - stations[j]->getX(), 2) + pow(stations[source]->getY() - stations[j]->getY(), 2);
			if (lowd == -1 || dd < lowd)
			{
				lowid = j;
				lowd = dd;
			}
		}
		mark[lowid] = true;
		markedStations[markedNum] = stations[lowid];
		markedIndex[markedNum] = lowid;
		markedNum++;
		rates[lowid] = 0;
		long long int lowp = -1;
		/*for (int j = 0; j < num; ++j)
		{
			if (!mark[j] || j == lowid)
				continue;
			for (int k = 0; k < num; ++k)
			{
				q[k] = rates[k];
			}
			int dd = pow(stations[j]->getX() - stations[lowid]->getX(), 2) + pow(stations[j]->getY() - stations[lowid]->getY(), 2);
			q[j] = max(q[j], (long long int) dd);
			
			Tree *tt = new Tree(q, markedStations, markedNum, 0);
			p[j] = tt->getLowestPower();
			if (lowp == -1 || p[j] < lowp)
			{
				lowp = p[j];
			}
		}*/
		for (int l = 0; l < markedNum; ++l)
		{
			int ind = markedIndex[l];
			if (ind == lowid)
				continue;
			for (int k = 0; k < markedNum; ++k)
			{
				int qind = markedIndex[k];
				q[k] = rates[qind];
			}
			int dd = pow(stations[ind]->getX() - stations[lowid]->getX(), 2) + pow(stations[ind]->getY() - stations[lowid]->getY(), 2);
			q[l] = max(q[l], (long long int) dd);
			cout << "jess" << "\n";
			Tree *tt = new Tree(q, markedStations, markedNum, 0);
			cout << "lin" << "\n";
			p[ind] = tt->getLowestPower();
			if (lowp == -1 || p[ind] < lowp)
				lowp = p[ind];
		}
		/*for (int l = 0; l < num; ++l)
		{
			if (!mark[l] || l == lowid)
				continue;
			for (int k = 0; k < num; ++k)
			{
				q[k] = rates[k];
			}
			int dd = pow(stations[l]->getX() - stations[lowid]->getX(), 2) + pow(stations[l]->getY() - stations[lowid]->getY(), 2);
			q[l] = max(q[l], (long long int) dd);
			Tree *tt = new Tree(q, stations, num, source);
			p[l] = tt->getLowestPower();
		}*/
		for (int l = 0; l < num; ++l)
		{
			if (l == lowid || !mark[l] || p[l] > lowp)
			continue;
			long long int dd = pow(stations[l]->getX() - stations[lowid]->getX(), 2) + pow(stations[l]->getY() - stations[lowid]->getY(), 2);
			cout << "up p";
			rates[l] = max(rates[l], dd);
		}
		for (int m = 0; m < markedNum; ++m)
		{
			int qind = markedIndex[m];
			q[m] = rates[qind];
		}
		Tree *tt = new Tree(q, markedStations, markedNum, 0);
		for (int l = 0; l < markedNum; ++l)
		{
			int ind = markedIndex[l];
			
			rates[ind] = tt->getLowTransSchedule()[l];
		}
	}

	for (int i = 0; i < num; ++i)
	{
		cout << i << "," << rates[i] << "\n";
	}
}


int main(int argc, char **argv)
{
	int method, stationNum, sourceStation;

	
	cin >> method;
	cin >> stationNum;
	cin >> sourceStation;
	sourceStation--;

	Station ** stations = new Station*[stationNum];
	
	for (int i = 0; i < stationNum; ++i)
	{
		int x, y;
		cin >> x;
		cin >> y;
		stations[i] = new Station(x, y);
		cout << "added " << x << "," << y << "\n";
	}

	ACSF(stations, stationNum, sourceStation);
	
	
	/*Station ** burning = new Station*[10];
	burning[0] = new Station(-4, 0);
	burning[1] = new Station(3, 4);
	burning[2] = new Station(-2, 4);
	burning[3] = new Station(-2, 6);
	burning[4] = new Station(7, 0);
	burning[5] = new Station(5, 0);
	burning[6] = new Station(0, -4);
	burning[7] = new Station(0, -7);
	burning[8] = new Station(0, -8);
	burning[9] = new Station(0, 0);
	
	
	long long int * rates = new long long int[10];
	rates[0] = 0;
	rates[1] = 0;
	rates[2] = 4;
	rates[3] = 0;
	rates[4] = 0;
	rates[5] = 4;
	rates[6] = 9;
	rates[7] = 1;
	rates[8] = 0;
	rates[9] = 30;

	Tree * tree = new Tree(rates, burning, 10, 9);

	cout << tree->getLowestPower();
	for (int j = 0; j < stationNum; ++j)
	{
		cout << tree->getLowTransSchedule()[j] << ",";
	}*/
	
	return 0;
}