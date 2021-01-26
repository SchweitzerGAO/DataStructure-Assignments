#ifndef HEAP_H
#define HEAP_H
#include<iostream>
using namespace std;
class MinHeap
{
private:
	int* heap;
	int curSize;//current size(from 1)
	int capacity;
	void up(int);//shift up
	void down(int, int);//shift down
public:
	MinHeap(int sz=100);//constructor
	~MinHeap() { delete[] heap; }//destructor
	bool isEmpty() { return curSize == 0; }//judge if the heap is empty
	bool isFull() { return curSize == capacity; }//is full
	bool input(int);//original array
	void adjust();//adjust to a tree
	bool insert(const int&);//insert a data
	bool remove(int&);//remove a data
};
int Huffman(MinHeap& H);//Huffman Tree Algorithm
#endif

