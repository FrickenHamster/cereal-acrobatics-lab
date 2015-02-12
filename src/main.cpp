#include <iostream>
#include <fstream>
#include <math.h>
#include "Station.h"
#include "Tree.h"

using namespace std;


void ACSF(Station **stations, int num, int source)
{
	long long int *rates = new long long int[num];
	long long int *p = new long long int[num];
	long long int *q = new long long int[num];
	//unmark stations

	Station **markedStations = new Station *[num];
	int *markedIndex = new int[num];
	int markedNum = 0;

	bool *mark = new bool[num];

	for (int i = 0; i < num; ++i)
	{
		mark[i] = false;
	}

	mark[source] = true;
	markedStations[markedNum] = stations[source];
	markedIndex[markedNum] = source;
	markedNum++;

	for (int i = 1; i < num; ++i)
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
			cout << "set p" << l << "to " << tt->getLowestPower();
			for (int j = 0; j < markedNum; ++j)
			{
				cout << "p" << j << ":" << p[j] << "\n";
			}
			
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
			break;
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


void ACSet(Station **stations, int num, int source)
{
	bool *mark = new bool[num];
	long long int *rates = new long long int[num];
	Station **markedStations = new Station *[num];
	int markedNum = 0;
	int *markedIndex = new int[num];
	
	int totalPower;

	for (int i = 0; i < num; ++i)
	{
		mark[i] = false;
		rates[i] = 0;
	}

	mark[source] = true;
	markedStations[markedNum] = stations[source];
	markedIndex[markedNum] = source;
	markedNum++;

	for (int i = 1; i < num; ++i)
	{
		int lowd = -1;
		int lowj = -1;
		int lowe = -1;
		long long int *q = new long long int[markedNum];
		long long int *p = new long long int[markedNum];

		for (int j = 0; j < num; ++j)
		{
			p[j] = 0;
			q[j] = 0;
			if (mark[j])
				continue;
			for (int k = 0; k < num; ++k)
			{
				if (!mark[k])
					continue;
				long long int dd = pow(stations[j]->getX() - stations[k]->getX(), 2) + pow(stations[j]->getY() - stations[k]->getY(), 2);
				if (lowd == -1 || dd < lowd)
				{
					lowj = j;
					lowe = k;
					lowd = dd;
				}
			}
		}
		
		cout << "picked station" << lowj << "\n";
		//mark lowj
		mark[lowj] = true;
		rates[lowj] = 0;
		markedStations[markedNum] = stations[lowj];
		markedIndex[markedNum] = lowj;
		markedNum++;
	
		
		int lowp = -1;

		for (int l = 0; l < markedNum; ++l)
		{
			int lind = markedIndex[l];
			if (lind == lowj)
				continue;
			cout << "going lind:" << lind << "\n";
			for (int k = 0; k < markedNum; ++k)
			{
				cout << "q[" << k << "] is" << rates[markedIndex[k]] <<"\n";
				q[k] = rates[markedIndex[k]];
			}
			
			long long int dd = pow(stations[lind]->getX() - stations[lowj]->getX(), 2) + pow(stations[lind]->getY() - stations[lowj]->getY(), 2);
			q[l] = max(q[l], dd);
			cout << "jess" << "\n";
			Tree *tt = new Tree(q, markedStations, markedNum, 0);
			p[lind] = tt->getLowestPower();
			cout << "set p" << l << "to " << tt->getLowestPower() << "\n";
			for (int j = 0; j < num; ++j)
			{
				cout << "p" << j << ":" << p[j] << "\n";
			}
			
			if (lowp == -1 || p[lind] < lowp)
				lowp = p[lind];
		}

		cout << "lowp" << lowp << "\n";
		
		int lowl = -1;
		for (int l = 0; l < markedNum; ++l)
		{
			//if (l == lowj)
			//	continue;
			cout << "searching " << p[markedIndex[l]] << "\n";
			if (p[markedIndex[l]] == lowp)
			{
				lowl = l;
				break;
			}
		}

		cout << "lowl" << lowl << "\n";
		
		int lind = markedIndex[lowl];
		cout << "low l " << lind <<"\n";
		
		long long int dd = pow(stations[lind]->getX() - stations[lowj]->getX(), 2) + pow(stations[lind]->getY() - stations[lowj]->getY(), 2);
		cout << "dd:" << dd << "\n";
		rates[lind] = max(rates[lind], dd);
		for (int m = 0; m < num; ++m)
		{
			cout << "rate is:" << rates[m] << "\n";
		}

		for (int l = 0; l < markedNum; ++l)
		{
			q[l] = rates[markedIndex[l]];
		}
		
		Tree *tt = new Tree(q, markedStations, markedNum, 0);

		for (int l = 0; l < markedNum; ++l)
		{
			int ind = markedIndex[l];
			cout << "setting " << ind << " to " << tt->getLowTransSchedule()[l] << "\n";
			rates[ind] = tt->getLowTransSchedule()[l];
		}
		totalPower = tt->getLowestPower();
		for (int n = 0; n < num; ++n)
		{
			cout << "end iter rate" << n << ":" << rates[n] << "\n";
		}
	}
	cout << totalPower << "\n";
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

	Station **stations = new Station *[stationNum];

	for (int i = 0; i < stationNum; ++i)
	{
		int x, y;
		cin >> x;
		cin >> y;
		stations[i] = new Station(x, y);
		cout << "added " << x << "," << y << "\n";
	}

	switch(method)
	{
		case 1:
			ACSF(stations, stationNum, sourceStation);
			
			break;
		case 2:
			ACSet(stations, stationNum, sourceStation);
			
			break;
	}
	


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