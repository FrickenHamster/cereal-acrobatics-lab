#ifndef PTREE_H_
#define PTREE_H_


class ProcedureNode
{

};



class ProcedureTree
{
public:
	ProcedureTree();
	virtual ~ProcedureTree();


private:
};

#endif /* PTREE_H_ */


class PTNode
{
private:
	int data;
friend class PTQueue;
};

class PTQueue
{
private:
	int headIndex;
	int tailIndex;
	int size;
	int maxSize;
	PTNode ** array;
	
public:
	PTQueue(int ms)
	{
		maxSize = ms;
		array = new PTNode*[maxSize];
		headIndex = 0;
		tailIndex = 0;
		size = 0;
	}
	
	void push(int i)
	{
		if (size >= maxSize)
		{
			return;
		}
		array[headIndex] =  i;
		headIndex++;
		size++;
		if (headIndex >= ms)
		{
			headIndex = 0;
		}
	}
	
	int pop()
	{
		if (size <= 0)
			return -1;
		int rr = array[tailIndex];
		tailIndex ++;
		size--;
		if (tailIndex >= ms)
		{
			tailIndex = 0;
		}
		return rr;
	}
	
};