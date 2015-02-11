#include <math.h>
#include <iostream>
#include "Tree.h"



TNode::TNode(int vv)
{
	val = vv;
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

Tree::Tree(long long int * rate, Station ** stations, int stationNum, int source)
{
	//set root
	//unmark all staitons
	
	lowTransSchedule = new int[stationNum];
	
	nodes = new TNode*[stationNum];
	
	//TNode * root = new TNode(source);

	bool * mark = new bool[stationNum];
	
	for (int i = 0; i < stationNum; ++i)
	{
		cout <<"treenode:" << stations[i]->getX() << "," << stations[i]->getY() << "rate: " << rate[i] << "\n";
		nodes[i] = new TNode(i);
		mark[i] = false;
	}
	//cout << "src:" << source << nodes[source];
	TNode * root = nodes[source];
	
	PTQueue * queue = new PTQueue(stationNum);
	
	queue->push(root);
	mark[source] = true;
	
	while (!queue->isEmpty())
	{
		TNode * i = queue->pop();
		//PTQueue * l = new PTQueue(stationNum);
		cout <<"cc";
		for (int j = 0; j < stationNum; ++j)
		{
			if (i->val == j)
				continue;
			if (mark[j])
				continue;
			long long int dd = pow(stations[i->val]->getX() - stations[j]->getX(), 2) + pow(stations[i->val]->getY() - stations[j]->getY(), 2);
			if (dd <= rate[i->val])
			{
				i->addChild(nodes[j], dd);
				//l->push(nodes[j]);
				mark[j] = true;
				queue->push(nodes[j]);
				cout<<"ass";
			}
			
		}
		/*while (!l->isEmpty())
		{
			TNode * j = l->pop();
			i->addChild(j, );
			mark[j->val] = true;
			queue->push(j);
		}*/
		
	}
	//cout << "suki" << root->val;
	root->print();

	lowPower = 0;
	for (int i = 0; i < stationNum; ++i)
	{
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
	
	//cout << "power" << lowPower;
	
}



int Tree::getLowestPower()
{
	return lowPower;
}

int * Tree::getLowTransSchedule()
{
	return lowTransSchedule;
}
