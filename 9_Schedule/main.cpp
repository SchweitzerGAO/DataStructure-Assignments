//运行之前请阅读项目文档中的“测试说明“！
#include"schedule.h"
ifstream& operator>>(ifstream& fin,Course&item)
{
	fin >> item.number >> item.name >> item.credit >> item.semester;
	fin >> item.previous[0] >> item.previous[1];
	if (item.number < 1 || item.number>38)
	{
		cerr << "Invalid course number! Please check your input file!\n";
		exit(1);
	}
	if (item.previous[0] < 0 || item.previous[1] < 0 || item.previous[0]>38 || item.previous[1]>38)
	{
		cerr << "Invalid previous course number! Please check your input file!\n";
		exit(1);
	}
	if (item.credit <= 0 || item.semester < 0)
	{
		cerr << "Invalid credit or semester! Please check your input file!\n";
	}
	return fin;
}
ofstream& operator<<(ofstream& fout, Course& item)
{
	if (item.number < 10)
	{
		fout << "c0" << item.number <<'\t';
	}
	else
	{
		fout << "c" << item.number << '\t';
	}
	fout << NAMES[item.number-1]<<'\t';
	fout << item.credit << '\t';
	for (int i = 0; i < 4; i++)
	{
		if (item.days[i] == -1)
		{
			break;
		}
		else
		{
			fout << DAYS[item.days[i]] << '(' << item.starts[i] << '-' << item.ends[i] << ')'<<' ';
		}
	}
	fout << endl;
	return fout;
}
Graph::Graph(int sz)
{
	tableSize = sz;
	NodeTable = new GraphNode * [sz];
	if (!NodeTable)
	{
		cerr << "Graph Allocation Error!\n";
		exit(1);
	}
	for (int i = 0; i < sz; i++)
	{
		NodeTable[i] = new GraphNode;
	}
	for (int i = 0; i < sz; i++)
	{
		NodeTable[i]->id = i;
	}
}
Graph::~Graph()
{
	for (int i = 0; i < tableSize; i++)
	{
		GraphNode* toDel,*temp;
		temp = NodeTable[i];
		while (temp)
		{
			toDel = temp;
			temp = temp->next;
			delete toDel;
		}

	}
	delete NodeTable;
}
void Graph::insertEdge(const int v1, const int v2)
{

	GraphNode* temp = NodeTable[v1];
	GraphNode* newNode = new GraphNode;
	if (!newNode)
	{
		cerr << "Allocation Error!\n";
		exit(1);
	}
	newNode->id = v2;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}
int Graph::getFirst(const int vertex)
{
	return(NodeTable[vertex]->next) ? (NodeTable[vertex]->next->id) : NOTFOUND;
}
int Graph::getNext(const int v1, const int v2)
{
	GraphNode* temp = NodeTable[v1];
	while (temp && temp->id != v2)
	{
		temp = temp->next;
	}
	return (temp && temp->next) ? temp->next->id : NOTFOUND;
}
void topologicalSort(Graph& G, int inDeg[], int result[])
{
	memset(result, -1, SORT * sizeof(int));
	int stackTop = -1;
	int first=-1, next=-1;
	int cnt = 0;
	for (int i = 0; i < SORT; i++)
	{
		if (inDeg[i] == 0)
		{
			inDeg[i] = stackTop;
			stackTop = i;//initialize the 0-in-degree-stack
		}
	}
	for (int i = 0; i < SORT; i++)
	{
		if (stackTop == -1)
		{
			cerr << "Cycling exists! Failed to sort!\n";
			return;
		}
		first = stackTop;
		stackTop = inDeg[stackTop];
		result[cnt++] = first;//pop to result array
		next = G.getFirst(first);
		while (next!=-1)
		{
			if (--inDeg[next] == 0)
			{
				inDeg[next] = stackTop;
				stackTop = next;//push because in degree is 0
			}
			next = G.getNext(first, next);
		}//get all the neighbor vertex
	}
	while (cnt < ALL)
	{
		result[cnt] = cnt;
		cnt++;
	}//the courses that won't need a sort(English and Chinese)
}



void addEdge(Graph& G, const Course item[],int inDeg[])
{
	memset(inDeg, 0, SORT * sizeof(int));
	for (int i = 0; i < SORT; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (item[i].previous[j])
			{
				G.insertEdge(item[i].previous[j] - 1, item[i].number - 1);
				inDeg[item[i].number - 1]++;
			}
			
		}
	}
	
}
Schedule::Schedule(int request[8], int size)
{
	tableSize = size;
	CourseTable = new Course * [size];
	if (!CourseTable)
	{
		cerr << "Schedule Allocation Error!\n";
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		CourseTable[i] = new Course[request[i]];
	}
	memset(numOfCourse, 0, 8 * sizeof(int));
}

void Schedule::semesterDivision(const int request[8], const int result[],Course item[])
{
	int sum[SEM];
	memset(sum, 0, SEM * sizeof(int));
	int sem = 0;
	int cur = 0;
	while (cur < SORT)
	{
		if (sem == 0)
		{
			int j;
			for (j = cur; j < cur + request[sem]-2; j++)//Chinese and English
			{
				item[result[j]].semester = sem + 1;
			}
			cur = j;
			sem++;
		}
		else
		{
			int j;
			for (j = cur; j < cur + request[sem] - 1; j++)//only English
			{
				item[result[j]].semester = sem + 1;
			}
			cur = j;
			sem++;
		}
	}//semester distribution
	for (int trav = 0; trav < ALL; trav++)
	{
		CourseTable[item[trav].semester - 1][numOfCourse[item[trav].semester - 1]]
			= item[trav];
		sum[item[trav].semester - 1] += item[trav].credit;
		numOfCourse[item[trav].semester - 1]++;
	}//put it to corresponding array
	for (int i = 0; i < SEM; i++)
	{
		if (sum[i] > 50)
		{
			cerr << "Too many courses for one semester!\n";
			exit(1);
		}
	}//judge if the total credit is reasonable(<50)
}
bool Schedule::arrangeByDuration(const int dur,int start,Course& item, bool available[5][10], int cnt)
//dur:the duration of a period(3,2,1 only);
//start:the day that it start to search
//item:the course to be processed
//available: the schedule table recording the available classes
//cnt:the current time of "dividing a class(for class of credit 6,5,4)" 
{
	int times = 0;
	int i = start;
	for (; times < 5; times++)
	{
		if (dur == 1)//ONLY 2 divided into 1 and 1
		{
			if (available[i % 5][0])
			{
				item.days[cnt] = i % 5;//guarantee that i is from 0 to 5
				item.starts[cnt] = 1;
				item.ends[cnt] = 1;
				available[i % 5][0] = false;
				return true;
			}
			if (available[i % 5][1])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 2;
				item.ends[cnt] = 2;
				available[i % 5][1] = false;
				return true;
			}
			if (available[i % 5][5])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 6;
				item.ends[cnt] = 6;
				available[i % 5][5] = false;
				return true;
			}
			if (available[i % 5][6])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 7;
				item.ends[cnt] = 7;
				available[i % 5][6] = false;
				return true;
			}
		}
		else if (dur == 2)
		{
			if (available[i % 5][0] && available[i % 5][1])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 1;
				item.ends[cnt] = 2;
				available[i % 5][0] = available[i % 5][1] = false;
				return true;
			}
			if (available[i % 5][5] && available[i % 5][6])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 6;
				item.ends[cnt] = 7;
				available[i % 5][5] = available[i % 5][6] = false;
				return true;
			}
		}
		else if (dur == 3)
		{
			if (available[i % 5][2] && available[i % 5][3]&&available[i % 5][4])
			{
				item.days[cnt] = i % 5;;
				item.starts[cnt] = 3;
				item.ends[cnt] = 5;
				available[i % 5][2] = available[i % 5][3]=available[i % 5][4] = false;
				return true;
			}
			else if (available[i % 5][7] && available[i % 5][8]&&available[i % 5][9])
			{
				item.days[cnt] = i % 5;
				item.starts[cnt] = 8;
				item.ends[cnt] = 10;
				available[i % 5][7] = available[i % 5][8] = available[i % 5][9] = false;
				return true;
			}
		}
		i++;
	}
	return false;
}

void Schedule::Arrange_one(Course& item, bool available[5][10])
{
	if (item.credit == 6)//=3+3=1+2+1+2
	{
		int cnt = 0;
		if (!arrangeByDuration(3,0, item, available, cnt))//3-false
		{
			int temp1 = cnt;
			if (!arrangeByDuration(2,0, item, available, cnt) ||
				(!arrangeByDuration(1, item.days[temp1] + 2, item, available, ++cnt)))//2+1-false
			{
				cerr << "Arrange Wrong!\n";
				exit(1);
			}
		}
		int temp2 = cnt;
		cnt++;
		if (!arrangeByDuration(3, item.days[temp2] + 2, item, available, cnt))
		{
			int temp3 = cnt;
			if (!arrangeByDuration(2, item.days[temp2] + 2, item, available, cnt) ||
				(!arrangeByDuration(1, item.days[temp3] + 2, item, available, ++cnt)))
			{
				cerr << "Arrange Wrong!\n";
				exit(1);
			}
		}
		return;
	}
	if (item.credit == 5)
	{
		int cnt = 0;
		if (!arrangeByDuration(3,0, item, available, cnt))
		{
			int temp1 = cnt;
			if (!arrangeByDuration(2,0, item, available, cnt) ||
				(!arrangeByDuration(1, item.days[temp1] + 2, item, available, ++cnt)))
			{
				cerr << "Arrange Wrong!\n";
				exit(1);
			}
		}
		int temp2 = cnt;
		cnt++;
		if (!arrangeByDuration(2, item.days[temp2] + 2, item, available, cnt))
		{
			cerr << "Arrange Wrong!\n";
			exit(1);
		}
		return;
	}
	if (item.credit == 4)
	{
		int cnt = 0;
		if (!arrangeByDuration(2, 0, item, available, cnt))
		{
			cerr << "Arrange Wrong!\n";
			exit(1);
		}
		int temp = cnt;
		cnt++;
		if (!arrangeByDuration(2, item.days[temp] + 2, item, available, cnt))
		{
			cerr << "Arrange Wrong!\n";
			exit(1);
		}
		return;
	}
	if (item.credit == 3)
	{
		int cnt = 0;
		if (!arrangeByDuration(3,0, item, available, cnt))
		{
			int temp1 = cnt;
			if (!arrangeByDuration(2, 0, item, available, cnt) ||
				(!arrangeByDuration(1, item.days[temp1] + 2, item, available, ++cnt)))
			{
				cerr << "Arrange Wrong!\n";
				exit(1);
			}
		}
	}

}
void Schedule::Arrange_all(int request[8], bool available[5][10])
{
	for (int i = 0; i < SEM; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			memset(available[j], true, 10 * sizeof(bool));//reset the table
		}
		for (int j = 0; j < request[i]; j++)//traverse all the courses
		{
			Arrange_one(CourseTable[i][j], available);

		}
	}
}
void inData(ifstream& fin, Course item[],int request[8],const int num)
{
	for (int i = 0; i < SEM; i++)
	{
		fin >> request[i];
		if (request[i] <= 0)
		{
			cout << "Invalid request!\n";
			exit(1);
		}
	}
	for (int i = 0; i < num; i++)
	{
		fin >> item[i];
	}
}
ofstream& operator<<(ofstream& fout, const Schedule& Sch)
{
	for (int i = 0; i < SEM; i++)
	{
		fout << "第" << i + 1 << "学期：\n";
		fout << "课程编号\t课程名称\t学分\t时间\n";
		for (int j = 0; j < Sch.numOfCourse[i]; j++)
		{
			fout << Sch.CourseTable[i][j];
		}
		fout << "=====================================\n";
	}
	
	return fout;
}
int main()
{
	int request[SEM],inDeg[SORT],result[ALL];
	bool available[5][10];
	Graph G;
	ifstream fin;
	ofstream fout;
	fin.open("data.TXT");
	fout.open("schedule.TXT");
	if (fin.bad())
	{
		cerr << "Please create \"data\".TXT and put the course data into it!\n";
		exit(1);
	}
	Course all[ALL], toSort[SORT];
	inData(fin, all, request,ALL);
	int sum = 0;
	for (int i = 0; i < SEM; i++)
	{
		sum += request[i];
	}
	if (sum != ALL)
	{
		cerr << "Invalid request!\n";
		exit(1);
	}
	Schedule S(request);
	for (int i = 0; i < SORT; i++)
	{
		toSort[i] = all[i];
	}
	addEdge(G, toSort, inDeg);
	topologicalSort(G, inDeg, result);
	S.semesterDivision(request, result, all);
	S.Arrange_all(request, available);
	fout << S;
	cout << "Arranged successfully!\nPress enter to exit:\n";
	cin.get();
	return 0;
}