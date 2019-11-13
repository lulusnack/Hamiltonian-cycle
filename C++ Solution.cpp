#include <iostream>
using std::cin;
using std::cout;
using std::endl;

struct node
{
	char name;
	char* neighbor;
	int neighbornum = 0;
};

void join(node*& data, char name, int nodenum);
void relation(node*& data, char name1, char name2, int L1, int L2);
int FindL(node*& data, char name, int nodenum);
void FindP(node*& data, int nodenum, char* path, int pathDataNum);

int main()
{
	int nodenum, sidenum;
	char start;
	node* data;
	cin >> nodenum >> sidenum >> start;
	data = new node[nodenum]();

	for (int i = 0; i < nodenum; i++)
	{
		data[i].neighbor = new char[sidenum]();
	}

	for (int i = 0; i < sidenum; i++)
	{
		char input1, input2;
		cin >> input1 >> input2;
		join(data, input1, nodenum);
		join(data, input2, nodenum);
		relation(data, input1, input2, FindL(data, input1, nodenum), FindL(data, input2, nodenum));
	}

	char* path = new char[nodenum + 1]();
	path[0] = start;
	FindP(data, nodenum, path, 1);
	return 0;
}

void join(node*& data, char name, int nodenum)
{
	static int existNodeNum = 0;
	bool newdata = true;

	if (existNodeNum == 0)
	{
		data[0].name = name;
		existNodeNum++;
		return;
	}

	for (int i = 0; i < existNodeNum; i++)
	{
		if (data[i].name == name)
		{
			newdata = false;
		}
	}

	if (newdata == true)
	{
		data[existNodeNum].name = name;
		existNodeNum++;
	}
}

void relation(node*& data, char name1, char name2, int L1, int L2)
{
	data[L1].neighbor[data[L1].neighbornum] = name2;
	data[L2].neighbor[data[L2].neighbornum] = name1;
	data[L1].neighbornum++;
	data[L2].neighbornum++;
}

int FindL(node*& data, char name, int nodenum)
{
	for (int i = 0; i < nodenum; i++)
	{
		if (data[i].name == name)
		{
			return i;
		}
	}
	return -1;
}

void FindP(node*& data, int nodenum, char* path, int pathDataNum)
{
	bool judge = true;
	for (int i = 1; i < pathDataNum; i++)
	{
		for (int j = i + 1; j < pathDataNum; j++)
		{
			if (path[i] == path[j])
			{
				judge = false;
			}
		}
	}

	if (judge == false)
	{
		return;
	}

	if (pathDataNum == nodenum + 1)
	{
		if (path[pathDataNum - 1] == path[0])
		{
			for (int i = 0; i < pathDataNum; i++)
			{
				cout << path[i];
			}
			cout << endl;
		}
		return;
	}

	int L = FindL(data, path[pathDataNum - 1], nodenum);
	for (int i = 0; i < data[L].neighbornum; i++)
	{
		path[pathDataNum] = data[L].neighbor[i];
		FindP(data, nodenum, path, pathDataNum + 1);
		path[pathDataNum] = NULL;
	}
}