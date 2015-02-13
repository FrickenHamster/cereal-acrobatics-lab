#include <math.h>
#include <iostream>
#include "Tree.h"



TNode::TNode(int vv)
{
	val = vv;
	parentIndex = -1;
	childHead = 0;
	childTail = 0;
	next = 0;
	childNum = 0;
	distToParent = 0;
}

void TNode::addChild(TNode * nn,long long int dd)
{

	if (childHead == 0)
	{
		childHead = nn;
		childTail = nn;
	}
	else
	{
		childTail->next = nn;
		childTail = nn;
	}
	nn->distToParent = dd;
	childNum++;
}

void Tree::printResult()
{
	cout << lowPower << "\n";
	for (int i = 0; i < stationNum; ++i)
	{
		if (lowTransSchedule[i] != 0)
		{
			TNode * nn = nodes[i];
			cout << i + 1 << " " << lowTransSchedule[i] << " " << nn->parentIndex << "\n";
		}
	}
}

void TNode::print()
{
	cout << "Node:" << val << "Children:\n";
	TNode * nn = childHead;
	while (nn != 0)
	{
		nn->print();
		nn = nn->next;
	}
	cout << "end Node:" << val << "\n";
}

Tree::Tree(long long int * rate, Station ** stations, int sn, int source)
{
	//set root
	//unmark all staitons
	stationNum = sn;
	
	// keep track of schedule and parents
	lowTransSchedule = new int[stationNum];
	parentIndexes = new int[stationNum];

	nodes = new TNode*[stationNum];

	bool * mark = new bool[stationNum];

	for (int i = 0; i < stationNum; ++i)
	{
		cout <<"treenode:" << stations[i]->getX() << "," << stations[i]->getY() << "rate: " << rate[i] << "\n";
		nodes[i] = new TNode(i);
		mark[i] = false;
	}
	TNode * root = nodes[source];

	PTQueue * queue = new PTQueue(stationNum);

	queue->push(root);
	mark[source] = true;

	while (!queue->isEmpty())
	{
		TNode * i = queue->pop();
		for (int j = 0; j < stationNum; ++j)
		{
			if (i->val == j)
				continue;
			if (mark[j])
				continue;
			long long int dd = pow(stations[i->val]->getX() - stations[j]->getX(), 2) + pow(stations[i->val]->getY() - stations[j]->getY(), 2);
			if (dd <= rate[i->val])
			{
				//cout << "added child" << j << "to" << i->val << "\n";
				nodes[j]->parentIndex = i->val;
				i->addChild(nodes[j], dd);
				mark[j] = true;
				queue->push(nodes[j]);
			}

		}

	}
	
	lowPower = 0;
	for (int i = 0; i < stationNum; ++i)
	{
		parentIndexes[i] = nodes[i]->parentIndex;
		TNode *nn = nodes[i];
		TNode *cc = nn->childHead;
		long long int pp = 0;
		while (cc != 0)
		{
			pp = max(cc->distToParent, pp);
			cc = cc->next;
		}
		//cout << "added power " << i << ":" << pp << "\n";
		lowTransSchedule[i] = pp;
		lowPower += pp;
	}
	//free mem
	//cout << "lowt:" << lowPower << "\n";
	delete mark;
	delete queue;
}



int Tree::getLowestPower()
{
	return lowPower;
}

int * Tree::getLowTransSchedule()
{
	return lowTransSchedule;
}

int * Tree::getParents(int * markedIndex, int size)
{
	
	int * nn = new int[size];
	for (int i = 0; i < size; ++i)
	{
		nn[i] = 0;
	}
	for (int j = 0; j < stationNum; ++j)
	{
		int ind = markedIndex[j];
		if (parentIndexes[j] == -1)
		{
			nn[ind] = -1;
		}
		else
		nn[ind] = markedIndex[parentIndexes[j]];
	}
	return nn;
}

Tree::~Tree()
{

	for (int i = 0; i < stationNum; ++i)
	{
		delete nodes[i];
	}
	delete nodes;
	delete lowTransSchedule;
	delete parentIndexes;
	
}


