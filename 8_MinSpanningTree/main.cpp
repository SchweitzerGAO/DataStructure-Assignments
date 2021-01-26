#include"graph.h"
#include<iostream>
using namespace std;
void displayMenu();
istream& operator>>(istream& is, WeightedEdge& item)
{
	is >> item.begin >> item.finish >> item.weight;
	return is;
}
ostream& operator<<(ostream& os, WeightedEdge& item)
{
	os << item.begin << "-(" << item.weight << ")->" << item.finish << '\t';
	return os;
}
void quickSort(WeightedEdge* arr, int left, int right)
{
	WeightedEdge standard = arr[left];
	int low = left;
	int high = right;
	if (low >= high)
	{
		return;
	}
	while (low < high)
	{
		while (low < high && arr[high] >= standard)
		{
			high--;
		}
		arr[low] = arr[high];
		while (low < high && arr[low] <= standard)
		{
			low++;
		}
		arr[high] = arr[low];
	}
	arr[low] = standard;
	quickSort(arr, left, low - 1);
	quickSort(arr, low + 1, right);
}
KGraph::KGraph(int sz=100)
{
	nameOfVex = new Vertex[sz];
	edges = new WeightedEdge[sz * (sz - 1) / 2];
	if (!( edges && nameOfVex))
	{
		cout << "Allocation Error!\n";
		exit(1);
	}
}//constructor
KGraph::~KGraph()
{
	delete[]edges;
	delete[]nameOfVex;
}//destructor
bool KGraph::resize(const int vex)
{
	int edge = vex * (vex - 1) / 2;
	delete[]edges;
	delete[]nameOfVex;//delete the original array;
	nameOfVex = new Vertex[vex];
	edges = new WeightedEdge[edge];
	if (nameOfVex && edges)
	{
		return true;
	}
	else
		return false;
}
void KGraph::inputName(const int vex)
{
	cout << "Please input the names of the vertices:\n";
	for (int i = 0; i < vex; i++)
	{
		cin >> nameOfVex[i].name;
		nameOfVex[i].tag = i;
	}
}//input the name of vertices
void KGraph::inputEdge(const int ed)
{
	cout << "Please input the edges of the graph:\n";
	for (int i = 0; i < ed; i++)
	{
		cin >> edges[i];//using overloaded >>
	}
	quickSort(edges, 0, ed - 1);//quicksort to sort the edges by weight from low to high
}
int KGraph::Find(const char name, const int vex)//find the position of the vertex
{
	for (int i = 0; i < vex; i++)
	{
		if (nameOfVex[i].name == name)
		{
			return i;
		}
	}
	return NOTFOUND;
}
bool KGraph::Kruskal(WeightedEdge* MinTree,const int vex,const int ed)
{
	int num = 0;
	int tempTag=-1;//very imprortant to store the tag of 'end', or it will come to a bug
	for (int i = 0; i < ed; i++)
	{
		int ini= Find(edges[i].begin,vex);//the start vertex
		int end = Find(edges[i].finish, vex);//the finish vertex
		if (end == NOTFOUND || ini == NOTFOUND)//if not found
		{
			cerr << "Invalid vertex!\n";
			return false;
		}
		if (nameOfVex[ini].tag != nameOfVex[end].tag)//if color not same
		{
			MinTree[num++] = edges[i];//add to MST
			tempTag = nameOfVex[end].tag;//store the tag 
			for (int j = 0; j < vex; j++)
			{
				if (nameOfVex[j].tag == tempTag)//has the same color with ending vertex
				{
					nameOfVex[j].tag = nameOfVex[ini].tag;//paint the same color with beginning vertex
				}
			}
		}
		if (num == vex - 1)//complete constructing MST
		{
			break;
		}
	}
	if (num < vex - 1)//not enough
	{
		cerr << "Failed to build Kruskal MST!\n";
		return false;
	}
	cout << "Successfully generated Kruskal MST!\n";
	
	return true;
}
void outputMST(WeightedEdge* arr, const int n)
{
	cout << "MST Edges are as below:\n";
	for (int i = 0; i < n; i++)
	{
		cout <<"Edge"<<i+1<<": "<< arr[i] << endl;
	}
	return;
}
void displayMenu()
{
	cout.setf(ios::left);
	cout << "Kruskal MST generator:\n";
	cout << "===========================\n";
	cout << "Operation List:\n";
	cout << "A:Initialize Vertices\nB:Initialize Edges\nC:Generate MST\nD:Display MST\nE:Exit\n";
	cout << "Please choose the options in the order of A-B-C-D\n";
	cout << "===========================\n";
}
int main()
{
	displayMenu();
	char opt;
	int numOfVex = -1;
	int numOfEdge = -1;
	KGraph G;
	WeightedEdge* MST=nullptr;
	bool hasAns = false;
	cout << "Please choose the option:";
	cin >> opt;
	while (opt != 'e' && opt != 'E')
	{
		switch (opt)
		{
		case 'a':
		case 'A':
		{
			cout << "Please input the number of vertices:";
			cin >> numOfVex;
			if (!G.resize(numOfVex))
			{
				cerr << "Allocation Error!\n";
				exit(1);
			}
			G.inputName(numOfVex);
			break;
		}
		case 'b':
		case 'B':
		{
			int standEdge = numOfVex * (numOfVex - 1) / 2;
			cout << "Please input the number of edges:";
			cin >> numOfEdge;
			if (numOfEdge > standEdge)
			{
				cerr<< "Too much edges!\n";
				exit(1);
			}
			G.inputEdge(numOfEdge);
			break;
		}
		case 'C':
		case 'c':
		{
			MST = new WeightedEdge[numOfVex - 1];
			if (!MST)
			{
				cerr << "Allocation Error!\n";
				exit(1);
			}
			hasAns=G.Kruskal(MST, numOfVex, numOfEdge);
			break;
		}
		case 'D':
		case 'd':
		{
			if (hasAns)
			{
				outputMST(MST, numOfVex - 1);
			}
			else
			{
				cerr << "No Answer!\n";
				exit(1);
			}
			break;
		}
		default:
			cout << "Unknown operation!\n";
			break;
		}
		cout << "Please choose the option:";
		cin >> opt;
	}
	cout << "Bye!\n";
	system("pause");
	return 0;
}
