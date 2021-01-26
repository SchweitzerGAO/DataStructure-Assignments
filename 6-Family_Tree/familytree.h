#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<string>
using namespace std;
class treeNode
{
public:
	string name;
	treeNode* first_child;
	treeNode* next_sibling;
	treeNode(string n = "", treeNode* fc = nullptr, treeNode* ns = nullptr)
		:name(n), first_child(fc), next_sibling(ns) {}
};//node of a tree
class QNode
{
public:
	treeNode* id;
	QNode* next;
	QNode(treeNode* n, QNode* p = nullptr)
	{
		id = n;
		next = p;
	}
	QNode(QNode* p = nullptr) { next = p; }

};//class QNode(the node element of a queue list)

class Queue
{
private:
	QNode* front;//the front node
	QNode* rear;//the rear node
public:
	Queue()
	{
		front = new QNode;
		rear = new QNode;
		if (front == nullptr || rear == nullptr)
		{
			cerr << "Allocation Error\n";
			exit(1);
		}
		front->next = rear;
		rear->next = nullptr;
	}// constructor, an empty queue
	~Queue() { makeEmpty(); }
	void makeEmpty();
	void pop();//dequeue
	void push(treeNode* x);//enqueue
	treeNode* Front();//get the elem that is at the front pos
	bool isEmpty() { return (front->next == rear); }//judge if the queue is empty
};//class Queue by linked list
class Tree
{
private:
	treeNode* root;//root
	treeNode* current;//the current node to operate
	void ancestor();//initialize a tree with an ancestor 
	void Delete(treeNode*);//delete a tree with a certain root
	bool search(treeNode*, const string&);//search a certain element 
	bool search_prior(treeNode*, const string&,int&);//search the prior of a certain element
	void output(treeNode*);//output a tree with its FIRST generation
public:
	Tree() { ancestor(); }//constructor
	~Tree() { Delete(root); }//destructor
	void build();//build family
	void insert();//insert a child
	void remove();//remove a family
	void modify();//modify the name of one element
	void All(Queue&);//output the entire tree
};//tree
void Queue::makeEmpty()
{
	QNode* temp;
	while (front->next != rear)
	{
		temp = front->next;//store the node to be deleted
		front->next = temp->next;//maintain the link
		delete temp;//delete the node
	}
	return;
}
void Queue::pop()
{
	if (front->next == rear)
	{
		cerr << "Empty Queue Error!\n";
		return;
	}//empty queue error
	QNode* temp = front->next;
	front->next = temp->next;
	delete temp;//delete the first node
}//dequeue
void Queue::push(treeNode* x)
{
	QNode* temp = front;
	while (temp->next != rear)
	{
		temp = temp->next;
	}//find the last node
	QNode* newNode = new QNode;
	if (newNode == nullptr)
	{
		cerr << "Allocation Error!\n";
		exit(1);
	}//allocation error
	newNode->id = x;
	newNode->next = rear;
	temp->next = newNode;//making link 
}//enqueue
treeNode* Queue::Front()
{
	if (front->next == rear)
	{
		cerr << "Empty Queue Error!\n";
		return nullptr;
	}//empty queue error
	return front->next->id;//get the first data of the queue
}
#endif
