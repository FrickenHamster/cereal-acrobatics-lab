#ifndef PTREE_H_
#define PTREE_H_

#include "Station.h"

using namespace std;

class TNode
{
public:
	TNode(int);
	void addChild(TNode*,long long int);
	void print();

private:
	int val;
	bool mark;
	int childNum;
	int parentIndex;
	
	TNode *next;
	TNode *childHead;
	TNode *childTail;
	
	long long int distToParent;
	
	friend class Tree;
};



class Tree
{
public:
	Tree(long long int *, Station **, int, int);
	virtual ~Tree();
	int getLowestPower();
	int * getLowTransSchedule();
	void printResult();
	int * getParents(int *, int);

private:
	TNode ** nodes;
	int stationNum;
	int lowPower;
	int * lowTransSchedule;
	int * parentIndexes;
};

#endif /* PTREE_H_ */

/*
class QueueNode
{
public:
	QueueNode(TNode * node)
	{
		data = node;
	}
private:
	TNode * data;
friend class PTQueue;
};*/

class PTQueue
{
private:
	int headIndex;
	int tailIndex;
	int size;
	int maxSize;
	TNode ** array;
	
public:
	PTQueue(int ms)
	{
		maxSize = ms;
		array = new TNode *[maxSize];
		headIndex = 0;
		tailIndex = 0;
		size = 0;
	}
		
	virtual ~PTQueue()
	{
		delete array;
	}
	
	void push(TNode* node)
	{
		if (size >= maxSize)
		{
			return;
		}
		array[headIndex] = node;
		headIndex++;
		size++;
		if (headIndex >= maxSize)
		{
			headIndex = 0;
		}
	}
	
	TNode * pop()
	{
		if (size <= 0)
			return 0;
		TNode * rr = array[tailIndex];
		tailIndex ++;
		size--;
		if (tailIndex >= maxSize)
		{
			tailIndex = 0;
		}
		return rr;
	}
	
	bool isEmpty()
	{
		if (size <= 0)
			return true;
		return false;
	}
	
};