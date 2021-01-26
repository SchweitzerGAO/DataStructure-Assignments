#ifndef STACK_H
#define STACK_H
#include<iostream>
using namespace std;
const int ERROR = -1;
class QNode
{
public:
	int id;
	QNode* next;
	QNode(int n, QNode* p = nullptr)
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
	void push(const int& x);//enqueue
	int Front();//get the elem that is at the front pos
	bool isEmpty() { return (front->next == rear); }//judge if the queue is empty
};//class Queue by linked list
void Queue::makeEmpty()
{
	QNode *temp;
	while (front->next!=rear)
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
void Queue::push(const int& x)
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
int Queue::Front()
{
	if (front->next == rear)
	{
		cerr << "Empty Queue Error!\n";
		return ERROR;
	}//empty queue error
	return front->next->id;//get the first data of the queue
}
#endif 

