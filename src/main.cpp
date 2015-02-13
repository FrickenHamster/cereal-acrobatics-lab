#include <iostream>
#include <fstream>
#include <math.h>
#include "Station.h"
#include "Tree.h"

using namespace std;


void ACSF(Station **stations, int num, int source)
{
	long long int *rates = new long long int[num];
	long long int *q = new long long int[num];
	Tree *tt = 0;
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
		int lowpid = - 1;
		for (int l = 0; l < num; ++l)
		{
			//int ind = markedIndex[l];
			if (!mark[l] || l == lowid)
				continue;
			for (int k = 0; k < num; ++k)
			{
				//int qind = markedIndex[k];
				q[k] = rates[k];
			}
			long long int dd = pow(stations[l]->getX() - stations[lowid]->getX(), 2) + pow(stations[l]->getY() - stations[lowid]->getY(), 2);
			q[l] = max(q[l], dd);

			
			tt = new Tree(q, stations, num, 0);
			delete tt;

			long long int pp = tt->getLowestPower();

			if (lowp == -1 || pp < lowp)
			{
				lowp = pp;
				lowpid = l;
			}
		}

		long long int dd = pow(stations[lowpid]->getX() - stations[lowid]->getX(), 2) + pow(stations[lowpid]->getY() - stations[lowid]->getY(), 2);
		rates[lowpid] = max(rates[lowpid], dd);

		for (int m = 0; m < num; ++m)
		{
			//int qind = markedIndex[m];
			q[m] = rates[m];
		}
		tt = new Tree(q, stations, num, 0);
		for (int l = 0; l < num; ++l)
		{
			//int ind = markedIndex[l];

			rates[l] = tt->getLowTransSchedule()[l];
		}
		if (i < num - 1)
			delete tt;
			
	}

	cout << tt->getLowestPower() << "\n";
	int *pp = tt->getParentsClean();
	for (int i = 0; i < num; ++i)
	{
		if (rates[i] != 0)
		{
			if (pp[i] == -1)
				cout << i + 1 << " " << rates[i] << " " << -1 << "\n";
			else
				cout << i + 1 << " " << rates[i] << " " << pp[i] + 1 << "\n";
		}
	}
	delete tt;
}


void ACSet(Station **stations, int num, int source)
{
	bool *mark = new bool[num];
	long long int *rates = new long long int[num];
	Station **markedStations = new Station *[num];
	int markedNum = 0;
	int *markedIndex = new int[num];

	int totalPower;
	
	Tree *tt;

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
		//int lowe = -1;
		long long int *q = new long long int[num];
		long long int *p = new long long int[num];

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
					//lowe = k;
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
		int lowpid = -1;

		for (int l = 0; l < num; ++l)
		{
			if (!mark[l] || l == lowj)
				continue;
			for (int k = 0; k < num; ++k)
			{
				q[k] = rates[k];
			}

			long long int dd = pow(stations[l]->getX() - stations[lowj]->getX(), 2) + pow(stations[l]->getY() - stations[lowj]->getY(), 2);
			q[l] = max(q[l], dd);
			cout << "jess" << "\n";
			tt = new Tree(q, stations, num, 0);
			long long int pp = tt->getLowestPower();
			cout << "set p" << l << "to " << pp << "\n";

			if (lowp == -1 || pp < lowp)
			{
				cout << "set low to" << pp;
				lowp = pp;
				lowpid = l;
			}
		}

		cout << "lowp" << lowp << "id" << lowpid << "\n";

		int lowl = lowpid;


		int lind = lowl;

		long long int dd = pow(stations[lind]->getX() - stations[lowj]->getX(), 2) + pow(stations[lind]->getY() - stations[lowj]->getY(), 2);
		cout << "dd:" << dd << "\n";
		rates[lind] = max(rates[lind], dd);
		for (int m = 0; m < num; ++m)
		{
			cout << "rate is:" << rates[m] << "\n";
		}

		for (int l = 0; l < num; ++l)
		{
			q[l] = rates[l];
		}

		tt = new Tree(rates, stations, num, 0);

		for (int l = 0; l < num; ++l)
		{
			rates[l] = tt->getLowTransSchedule()[l];
		}
		totalPower = tt->getLowestPower();
		if (i < num - 1)
			delete tt;
	}
	cout << tt->getLowestPower() << "\n";
	int *pp = tt->getParentsClean();
	for (int i = 0; i < num; ++i)
	{
		if (rates[i] != 0)
		{
			if (pp[i] == -1)
				cout << i + 1 << " " << rates[i] << " " << -1 << "\n";
			else
				cout << i + 1 << " " << rates[i] << " " << pp[i] + 1 << "\n";
		}
	}
	delete tt;
}

void ACF(Station **stations, int num, int source)
{
	bool *mark = new bool[num];
	long long int *rates = new long long int[num];

	Station **markedStations = new Station *[num];
	int markedNum = 0;
	int *markedIndex = new int[num];

	long long int lowp = -1;
	int lowpj = -1;
	int lowpl = -1;

	long long int *q = new long long int[markedNum];
	long long int *p = new long long int[markedNum];

	Tree *tt = 0;

	for (int i = 0; i < num; ++i)
	{
		mark[i] = false;
		rates[i] = 0;
	}

	mark[source] = true;
	markedIndex[markedNum] = source;
	markedStations[markedNum] = stations[source];
	markedNum++;

	for (int i = 1; i < num; ++i)
	{
		lowp = -1;
		lowpj = -1;
		lowpl = -1;
		for (int j = 0; j < num; ++j)
		{
			p[j] = 0;
			q[j] = 0;
		}
		for (int j = 0; j < num; ++j)
		{
			if (mark[j])
				continue;
			for (int m = 0; m < markedNum; ++m)
			{
				//cout << "marked" << markedIndex[m] << "\n";
			}
			mark[j] = true;
			markedIndex[markedNum] = j;
			markedStations[markedNum] = stations[j];
			markedNum++;
			rates[j] = 0;

			for (int l = 0; l < markedNum; ++l)
			{
				int lind = markedIndex[l];
				if (lind == j)
					continue;
				for (int y = 0; y < num; ++y)
				{
					p[y] = 0;
					q[y] = 0;
				}
				for (int k = 0; k < markedNum; ++k)
				{
					q[k] = rates[markedIndex[k]];
				}
				long long int dd = pow(stations[lind]->getX() - stations[j]->getX(), 2) + pow(stations[lind]->getY() - stations[j]->getY(), 2);
				q[l] = max(q[l], dd);
				//cout << "tree " << j << "," << markedIndex[l] << "lind:" << lind << "\n";
				tt = new Tree(q, markedStations, markedNum, 0);
				long long int pp = (long long int) tt->getLowestPower();
				if (lowp == -1 || pp < lowp)
				{

					lowpj = j;
					lowpl = lind;
					lowp = pp;
				}
			}
			//unmark j
			mark[j] = false;
			/*for (int l = j; l < markedNum - 1; ++l)
			{
				markedStations[l] = markedStations[l + 1];
				markedIndex[l] = markedIndex[l + 1];
			}*/
			markedNum--;

		}

		mark[lowpj] = true;
		markedStations[markedNum] = stations[lowpj];
		markedIndex[markedNum] = lowpj;
		markedNum++;

		long long int dd = pow(stations[lowpl]->getX() - stations[lowpj]->getX(), 2) + pow(stations[lowpl]->getY() - stations[lowpj]->getY(), 2);
		rates[lowpl] = max(rates[lowpl], dd);
		for (int m = 0; m < markedNum; ++m)
		{
			p[m] = rates[markedIndex[m]];
		}
		tt = new Tree(p, markedStations, markedNum, 0);
		for (int l = 0; l < markedNum; ++l)
		{
			int ind = markedIndex[l];
			rates[ind] = tt->getLowTransSchedule()[l];
		}
		if (i < num - 1)
			delete tt;
	}
	cout << tt->getLowestPower() << "\n";
	int *pp = tt->getParents(markedIndex, markedNum);
	for (int i = 0; i < num; ++i)
	{
		if (rates[i] != 0)
		{
			cout << i + 1 << " " << rates[i] << " " << pp[i] + 1 << "\n";
		}
	}
}

class MS
{
public:
	MS(long long int dd, Station * ss, int ii)
	{
		dist = dd;
		station = ss;
		index = ii;
	}
	long long int dist;
	Station * station;
	int index;
};

MS **mergeSort(MS **array, int start, int end)
{
	if (start == end)
	{
		MS **rr = new MS*[1];
		rr[0] = array[start];
		return rr;
	}
	int size = end - start + 1;
	int mid = start + floor((end - start) / 2);
	int li = 0;
	int ri = 0;
	int ls = mid - start + 1;
	int rs = end - mid;
	MS **left = mergeSort(array, start, mid);
	MS **right = mergeSort(array, mid + 1, end);

	MS **rr = new MS*[size];
	//return rr;
	int jes = 0;
	//cout << "rs " << rs << "ls" << ls << "\n";
	while (li < ls || ri < rs)
	{
		if (li > ls || ri > rs)
		{
			//cout << "fail" << rs << "," << ls << "\n";
			return rr;
		}
		if (ri == rs)
		{
			rr[jes] = left[li];
			li++;
			jes++;
		}
		else if (li == ls)
		{
			rr[jes] = right[ri];
			ri++;
			jes++;
		}
		else if (left[li]->dist <= right[ri]->dist)
		{
			rr[jes] = left[li];
			li++;
			jes++;
		}
		else
		{
			rr[jes] = right[ri];
			ri++;
			jes++;
		}
	}
	delete left;
	delete right;
	return rr;
}

typedef struct DCF
{
	long long int *rates;
	
}DCF;

Tree * DCACF(Station **stations, int mmn, long long int * rates, int num, int source, int * markedIndex)
{
	bool *mark = new bool[num];

	Station **markedStations = new Station *[num];
	int markedNum = mmn;
	//int *markedIndex = new int[num];

	long long int lowp = -1;
	int lowpj = -1;
	int lowpl = -1;

	long long int *q = new long long int[num];
	long long int *p = new long long int[num];

	Tree *tt = 0;
	cout << "total:" << num << "marked:" << mmn << "iters" << (num - mmn) << "\n";
	for (int i = 0; i < num; ++i)
	{
		cout << "new rates" << rates[i] << "\n";
		if (i < mmn)
		{
			cout << "marked" << i << "\n";
			mark[i] = true;
			markedStations[i] = stations[i];
			markedIndex[i] = i;
		}
		else
			mark[i] = false;
	}
	
	for (int i = 0; i < (num - mmn); ++i)
	{
		lowp = -1;
		lowpj = -1;
		lowpl = -1;
		if (mark[0] == false)
			cout <<"love" << i << "\n";
		if (i == 0 && num == 9)
			cout <<"start";
		
		for (int j = 0; j < num; ++j)
		{
			//cout << "wat" << mark[0] << "\n";
			if (mark[j])
				continue;
			mark[j] = true;
			markedIndex[markedNum] = j;
			markedStations[markedNum] = stations[j];
			markedNum++;
			rates[j] = 0;

			for (int l = 0; l < markedNum; ++l)
			{
				int lind = markedIndex[l];
				if (lind == j)
					continue;
				for (int y = 0; y < num; ++y)
				{
					p[y] = 0;
					q[y] = 0;
				}
				for (int k = 0; k < markedNum; ++k)
				{
					//cout << "setting q" << k << "," << markedIndex[k] << "rr " << rates[markedIndex[k]] << "\n";
					q[k] = rates[markedIndex[k]];
				}
				long long int dd = pow(stations[lind]->getX() - stations[j]->getX(), 2) + pow(stations[lind]->getY() - stations[j]->getY(), 2);
				q[l] = max(q[l], dd);
				cout << "tree " << j << "," << markedIndex[l] << "lind:" << lind << "\n";
				flush(cout);
				tt = new Tree(q, markedStations, markedNum, 0);
				if (mark[0] == false)
					cout <<"here " << i << j << lind << "\n";
				long long int pp = (long long int) tt->getLowestPower();
				if (lowp == -1 || pp < lowp)
				{
					lowpj = j;
					lowpl = lind;
					lowp = pp;
					cout << "lowp wtf " << lowp << "\n";
				}
			}
			//unmark j
			mark[j] = false;
			cout << "unmarked " << j << "\n";
			/*for (int l = j; l < markedNum - 1; ++l)
			{
				markedStations[l] = markedStations[l + 1];
				markedIndex[l] = markedIndex[l + 1];
			}*/
			
			markedNum--;
		}
		
		mark[lowpj] = true;
		markedStations[markedNum] = stations[lowpj];
		markedIndex[markedNum] = lowpj;
		markedNum++;
		cout << "lowp" << lowpj << "\n";
		flush(cout);
		long long int dd = pow(stations[lowpl]->getX() - stations[lowpj]->getX(), 2) + pow(stations[lowpl]->getY() - stations[lowpj]->getY(), 2);
		rates[lowpl] = max(rates[lowpl], dd);
		for (int m = 0; m < markedNum; ++m)
		{
			p[m] = rates[markedIndex[m]];
		}
		tt = new Tree(p, markedStations, markedNum, 0);
		for (int l = 0; l < markedNum; ++l)
		{
			int ind = markedIndex[l];
			rates[ind] = tt->getLowTransSchedule()[l];
		}
		
		

		if (i <= num - 1)
			delete tt;
		
	}
	cout << tt->getLowestPower() << "\n";
	int *pp = tt->getParents(markedIndex, markedNum);
	for (int i = 0; i < num; ++i)
	{
		if (rates[i] != 0)
		{
			cout << i + 1 << " " << rates[i] << " " << pp[i] << "\n";
		}
	}
	for (int i = 0; i < num; ++i)
	{
		cout << i << "," << rates[i] << "\n";
	}
	return tt;
	
}

void DC(Station **stations, int num, int source)
{

	MS **dists = new MS*[num];
	for (int i = 0; i < num; ++i)
	{
		
		long long int dd = pow(stations[source]->getX() - stations[i]->getX(), 2) + pow(stations[source]->getY() - stations[i]->getY(), 2);
		MS * ms = new MS(dd, stations[i], i);
		dists[i] = ms;
		
		cout << dd << "\n";
	}
	MS **sort = mergeSort(dists, 0, num - 1);
	long long int * rates = new long long int[num];
	Station ** sortStation = new Station*[num];
	for (int i = 0; i < num; ++i)
	{
		cout << sort[i]->dist << "\n";
		sortStation[i] = sort[i]->station;
		rates[i] = 0;
	}
	
	Tree * tt;
	
	int * markedIndex = new int[num];
	
	int dn = num / 4;
	tt = DCACF(sortStation, 1, rates, dn, source, markedIndex);
	delete tt;
	tt = DCACF(sortStation, dn, rates, dn * 2, source, markedIndex);
	delete tt;
	tt = DCACF(sortStation, dn * 2, rates, dn * 3, source, markedIndex);
	delete tt;
	tt = DCACF(sortStation, dn * 3, rates, num, source, markedIndex);
	cout << tt->getLowestPower() << "\n";
	int *pp = tt->getParents(markedIndex, num);
	int * rp = new int[num];
	for (int i = 0; i < num; ++i)
	{
		if (pp[i] == -1)
			rp[i] = -2;
		else
		rp[i] = sort[pp[i]]->index;
	}
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			if (sort[j]->index == i)
			{
				if (rates[j] != 0)
				{
					cout << i + 1 << " " << rates[j] << " " << rp[j] + 1 << "\n";
				}
				break;
			}
		}
	}
	
	delete tt;
}


int main(int argc, char **argv)
{
	/*long long int * test = new long long int[5];
	test[0] = 3;
	test[1] = 32;
	test[2] = 1;
	test[3] = 7;
	test[4] = 6;
	long long int * rr = mergeSort(test, 0, 4);
	for (int j = 0; j < 5; ++j)
	{
		cout << rr[j] << "\n";
	}
	return 0;
	*/

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

	switch (method)
	{
		case 1:
			ACSF(stations, stationNum, sourceStation);

			break;
		case 2:
			ACSet(stations, stationNum, sourceStation);

			break;

		case 3:
			ACF(stations, stationNum, sourceStation);
			break;

		case 4:
			DC(stations, stationNum, sourceStation);
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