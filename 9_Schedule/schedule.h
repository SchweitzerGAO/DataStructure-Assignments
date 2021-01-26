#ifndef SCHEDULE_H
#define SCHEDULE_H
#include<iostream>
#include<fstream>
#include<cstring>//memset
#include<string>
using namespace std;
const int SEM = 8;
const int SORT = 29;
const int ALL = 38;
const int NOTFOUND = -1;
const string DAYS[5] = { "周一","周二","周三","周四","周五" };
const string NAMES[38] = { "程序设计基础","离散数学","数据结构算法","汇编语言","算法设计",
					   "计算机组成原理","微机原理","单片机应用","编译原理","操作系统原理","数据库原理",
						"高等数学","线性代数","数值分析","普通物理","计算机文化","计算机系统结构",
						"计算机网络","数据通信","面向对象程序设计","Java","C#.net","PowerBuilder",
						"VC++","ASP程序设计","JSP程序设计","VB.net","Delphi","C++ Builder",
						"英语","英语","英语","英语","英语","英语","英语","英语","大学语文"};
struct Course
{
	int days[4] = { -1,-1,-1,-1 };
	int starts[4] = { 0,0,0,0 };
	int ends[4] = { 0,0,0,0 };//arrange information
	int number=-1;
	string name="";
	int credit = -1;
	int semester = -1;
	int previous[2] = { 0,0 };//necessary information
	friend ifstream& operator>>(ifstream&, Course&);
	friend ofstream& operator<<(ofstream&, Course&);
	
};
struct GraphNode
{
	int id;
	GraphNode* next;
	GraphNode(int i=-1, GraphNode* gn=nullptr) :id(i), next(gn) {}//contructor
};
class Graph
{
public:
	Graph(int sz = 29);
	~Graph();
	void insertEdge(const int,const int);//insert edge to a graph
	int getFirst(const int);//get the first neighbor of a vertex
	int getNext(const int, const int);//get the next neighbor of a vertex(used in getting all the neighbors)
private:
	GraphNode** NodeTable;//table of every course
	int tableSize;//size of the table
};//class Graph
class Schedule
{
public:
	Schedule(int request[8],int size=8);
	~Schedule() { delete CourseTable; }
	void semesterDivision(const int request[8], const int result[],Course[]);//distribute class for every semester
	void Arrange_one(Course&,bool[5][10]);//the integrated arrange function(for one course)
	void Arrange_all(int request[8], bool[5][10]);//the integrated function(for all courses)
	friend ofstream& operator<<(ofstream&,const Schedule&);//<< overloaded to output to a file
	

	
private:
	Course** CourseTable;
	int tableSize;//number of semester
	int numOfCourse[8];//used in arranging courses into each semester
	bool arrangeByDuration(const int dur, int start, Course&, bool[5][10], int cnt);//arrange classes by 1,2,3 duration
};//class Schedule
void addEdge(Graph&, const Course[],int inDeg[]);//add edges to a graph
void topologicalSort(Graph&, int inDeg[],int result[]);//for the division of courses
void inData(ifstream&,Course[],int[8],const int);
#endif
