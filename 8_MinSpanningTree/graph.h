#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
using namespace std;
const int NOTFOUND = -1;
struct WeightedEdge
{
	char begin;
	char finish;
	int weight;
	bool operator<=(const WeightedEdge& ed) { return weight <= ed.weight; }
	bool operator>=(const WeightedEdge& ed) { return weight >= ed.weight; }
	friend istream& operator>>(istream&, WeightedEdge&);
	friend ostream& operator<<(ostream&, WeightedEdge&);

};
struct Vertex
{
	char name;
	int tag;
};

void quickSort(WeightedEdge*, int, int);
class KGraph
{
private:
	Vertex* nameOfVex;
	WeightedEdge* edges;
public:
	KGraph(int);
	~KGraph();
	void inputName(const int);
	void inputEdge(const int);
	int Find(const char ,const int);
	bool Kruskal(WeightedEdge*,const int,const int);
	bool resize(const int);//just to change the arrays to a reasonable size,NOT COPY
};
void outputMST(WeightedEdge*,const int);//output the result
#endif
