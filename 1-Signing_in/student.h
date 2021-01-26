#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<string>
using namespace std;
struct student
{
	string num;
	string name;
	string sex;
	int age=-1;
	string job;
};// struct storing basic data of a student
class LNode
{
public:
	student data;
	LNode* next;
	LNode(LNode* p=nullptr){next=p;}// pointer scope only
	LNode(const student& item,LNode* p=nullptr)// both pointer scope and data scope
	{
		data=item;
		next=p;
	}
	friend ostream& operator<<(ostream& out, student& item);// << overload to output data
	friend istream& operator>>(istream& in, student& item);// >> overload to input data
};// class LNode
class LinList
{
private:
	LNode* first;// head node
public:
	LinList()//constructor
	{
		first=new LNode;
		if(first==nullptr)
		{
			cerr<<"Allocation Error!\n";
			exit(1);
		}//deal with memory allocation error
	}
	~LinList(){makeEmpty();}//destructor
	void makeEmpty();// make the list empty, used in destructor
	void input();//input  students' information
	void output()const;//output
	bool insert(int i);//insert
	bool search(const string No);//search
	bool remove(int i);//remove
	bool modify(const string No);//modify
	int count()const;//the length of the list
};//class LinList
ostream& operator<<(ostream& out, student& item)
{
	out << item.num << '\t' << item.name << '\t' << item.sex << '\t'
		<< item.age << '\t' << item.job << '\t' << endl;
	return out;
}// << overload to output data, making code simpler
istream& operator>>(istream& in, student&item)
{
	in >> item.num >> item.name >> item.sex
		>> item.age >> item.job;
	return in;
}//>> overload to input data
void LinList::makeEmpty()
{
	LNode* temp;
	while (first->next)//while not empty
	{
		temp = first->next;//store the node to be deleted
		first->next = temp->next;// change the pointer of the head node
		delete temp;//delete the node
	}
	return;
}
int LinList::count()const
{
	LNode* temp = first->next;
	int count = 0;//counter
	while (temp)
	{
		temp = temp->next;//traversing
		count++;
	}
	return count;//current length
}
void LinList::input()
{
	cout << "首先请建立考生信息系统：\n";
	int person;
	cout << "请输入考生人数：\n>>>";
	while (1)
	{
		cin >> person;
		if (person > 0)
			break;
		cerr << "请输入一个正整数！\n>>>";
	}//loop to check if the number is positive
	cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别：\n";
	LNode* temp = first;
	LNode* newNode;
	while (person--)
	{
		newNode = new LNode;// new data
		if (newNode == nullptr)
		{
			cerr << "Allocation Error!\n";
			exit(1);
		}
		cin >> newNode->data;//using overloaded operator
		temp->next = newNode;//making link
		temp = temp->next;//move current pointer
	}
	temp->next = nullptr;//null end
	return;
}
void LinList::output()const
{
	if (first->next == nullptr)
	{
		cerr << "此表为空！\n";
		return;
	}//empty error
	cout << "考生信息如下所示：\n";
	cout << "考号\t姓名\t性别\t年龄\t报考类别\n";
	cout.setf(ios::left);//format setting
	LNode* temp = first->next;
	while (temp)
	{
		cout << temp->data;//using the overloaded <<
		temp = temp->next;
	}//traversing the list
	return;
}
bool LinList::insert(int i)//inserting by position
{

	LNode* temp = new LNode;//  a new node 
	LNode* current = first;
	if (temp == nullptr)
	{
		cerr << "Allocation Error!";
		exit(1);
	}//allocation error
	if (i > count() + 1||i<=0)
	{
		cerr << "无效插入位置，插入失败！\n";
		return false;
	}//position error
	cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别：\n";
	cin >> temp->data;//using the overloaded >>
	LNode* chr = first->next;
	while (chr)
	{
		if ((chr->data).num == (temp->data).num)
		{
			cerr << "考生已经存在，插入失败！\n";
			return false;
		}// existence error
		chr = chr->next;
	}
	/*if (first->next == nullptr || i == 1)//the position is the first one
	{
		temp->next = first->next;
		first->next = temp;//directly insert after head node
	}*/
	for (int j = 1; j < i; j++)
	{
		current = current->next;
	}//finding the correct position(the prior)
	temp->next = current->next;
	current->next = temp;//inserting and maintaining the lin
	
	cout << "插入成功！\n";
	return true;
}
bool LinList::remove(int i)//delete by position
{
	LNode* toDel, * current;
	current = first;
	if (first->next == nullptr)
	{
		cerr << "表空，删除失败！\n";
		return false;
	}//empty list error
	if (i <= 0||i>=count()+1)
	{
		cerr << "无效删除位置，删除失败！\n";
		return false;
	}// invalid position error
	/*if (i == 1)
	{
		toDel = first->next;
		first->next = toDel->next;
		delete toDel;
	}// delete the first node*/
	
	for (int j = 1; j < i; j++)
	{
		current = current->next;
	}//find the position
	toDel = current->next;
	current->next = toDel->next;//maintaining the link
	delete toDel;
	cout << "删除成功！\n";
	return true;
}
bool LinList::search(const string No)// sequence seaching by student.num
{
	LNode* temp=first->next;
	while (temp)
	{
		if ((temp->data).num == No)
		{
			cout << "查找成功！\n";
			cout << "考号\t姓名\t性别\t年龄\t报考类别\n";
			cout << temp->data;//using the overloaded <<
			return true;//found- and-return
		}
		temp = temp->next;//traversing
	}
	cerr << "查无此项！\n";
	return false;
}
bool LinList::modify(const string No)
{
	LNode* temp = first->next;
	while (temp)
	{
		if ((temp->data).num == No)//searching
		{
			cout << "请依次输入要修改的考生的考号、姓名、性别、年龄及报考类别：\n";
			cin >> temp->data;// using overloaded >>
			cout << "修改成功！\n";//modifying
			return true;
		}
		temp = temp->next;
	}
	cerr << "查无此项！\n";
	return false;
}
#endif
