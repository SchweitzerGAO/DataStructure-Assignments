#ifndef DFSTACK_H
#define DFSTACK_H
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
const int MOVX[] = { 1,0,-1,0 };
const int MOVY[] = { 0,1,0,-1 };
struct point
{
	int x;
	int y;
};
template<class T>
class Stack
{
private:
	T* val;
	int topIdx;
	int maxSize;
public:
	Stack(int sz = 100)
	{
		maxSize = sz;
		topIdx = -1;
		val = new T[maxSize];
		if (val == nullptr) { cerr << "Allocation Error!\n"; exit(1); }
	}
	~Stack() { delete[]val; }
	bool isEmpty() { return (topIdx == -1); }
	bool isFull() { return (topIdx == maxSize - 1); }
	void push(const T& x);
	void pop();
	T top();
	int max() { return maxSize; }
	int size() { return (topIdx + 1); }
};//template class stack
template<class T>
void Stack<T>::push(const T& x)
{
	if (isFull())
	{
		cerr << "Full Stack Error!\n";
		return;
	}
	val[++topIdx] = x;
	return;
}
template<class T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		cerr << "Empty Stack Error!\n";
		return;
	}
	--topIdx;//modify the top index,which is equivalance to deleting the top elem
}
template<class T>
T Stack<T>::top()
{
	return(val[topIdx]);
}

#endif

