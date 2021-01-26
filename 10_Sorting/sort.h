#ifndef SORT_H
#define SORT_H
#include<iostream>
using namespace std;
void bubbleSort(int*, int);
void insertSort(int*, int);
void selectionSort(int*, int);
void shellSort(int*, int);
void quickSort(int*, int, int,long long&);
void mergeSort(int*, int, int,int*,long long&);
int getMaxBit(int*,int);//the function is used by radixSort()
void radixSort(int*, int);
//functions below are used by heapSort();
void shiftDown(int*, int, int,long long&);//shift to a heap from top to bottom
void adjust(int*, int,long long&);//adjust an array to a heap by shiftDown() 
void remove(int*, int, int&,long long&);//remove an element from the top of a heap
							 //while maintaining the properties of heap
//
void heapSort(int*, int,long long&);
#endif