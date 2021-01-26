#include"heap.h"
MinHeap::MinHeap(int sz)
{
	heap = new int[sz];
	if (heap == nullptr)
	{
		cerr << "Allocation Error!\n";
		exit(1);
	}
	capacity = sz;
	curSize = 0;
}//constructor
bool MinHeap::input(int n)
{
	if (isFull())
	{
		cerr << "Full Heap Error!\n";
		return false;
	}
	else if (n > capacity||n<=0)
	{
		cerr << "Invalid size! Please choose a size from 1 to " << capacity << endl;
		return false;
	}
	for (int i = 0; i < n; i++)
	{
		cin >> heap[i];
		curSize++;
	}
	return true;
}//input an array
void MinHeap::adjust()
{
	int curPos = (curSize - 2) / 2;//the last non-leaf data
	while (curPos >= 0)//adjust from bottom to top
	{
		down(curPos, curSize - 1);//for every part,shift from top to bottom
		curPos--;
	}
	return;
}//bottom-to-top adjustment,in which the smaller part is top-to-bottom
void MinHeap::down(int start, int end)//end with 'end'
{
	int parent = start;
	int child = 2 * start + 1;
	int temp = heap[parent];//temporarily store the data to be compared
	while (child <= end)
	{
		if (child<end && heap[child]>heap[child + 1])
		{
			child++;//choose the less one
		}
		if (temp <= heap[child])//parent<=child
		{
			break;
		}
		else//parent>child
		{
			heap[parent] = heap[child];//float the child
			parent = child;
			child = child * 2 + 1;//continue to compare
		}
	}
	heap[parent] = temp;//put temp to the correct position
	return;
}
void MinHeap::up(int start)//end with 0
{
	int child = start;
	int parent = (child - 1) / 2;
	int temp = heap[child];
	while (parent > 0)
	{
		if (heap[parent] <= heap[child])
			break;
		else
		{
			heap[child] = heap[parent];//sink the parent
			child = parent;			
			parent = (parent - 1) / 2;//continue to compare 
		}
	}
	heap[child] = temp;//put temp to the correct position
	return;
}//as above, shift from bottom to top
bool MinHeap::insert(const int& l)
{
	if (isFull())
	{
		cerr << "Full Heap Error!\n";
		return false;
	}
	//not full
	heap[curSize] = l;//insert
	up(curSize);//shift up to a heap
	curSize++;//resize
	return true;
}//insert
bool MinHeap::remove(int& l)
{
	if (isEmpty())
	{
		cerr << "Empty Heap Error!\n";
		return false;
	}
	l = heap[0];//store the val
	heap[0] = heap[curSize - 1];//temporarily fill haep[0] with the last elem
	curSize--;//resize
	down(0, curSize - 1);//shift to heap
	return true;
}//remove
int Huffman(MinHeap& H)
{
	int temp_sum=0,temp_store;
	int sum = 0;
	while (!H.isEmpty())
	{
		if (H.isEmpty())
		{
			break;
		}//protect
		else
		{
			H.remove(temp_store);
			temp_sum += temp_store;
		}
		if (H.isEmpty())
		{
			break;
		}//protect
		else
		{
			H.remove(temp_store);
			temp_sum += temp_store;
		}//remove 2 least elements 
		sum += temp_sum;//the result
		H.insert(temp_sum);//insert the sum to the heap 
		temp_sum = 0;
	}
	return sum;
}//Huffman Algorithm
int main()
{
	MinHeap H;
	int N,res;
	cout << "Please input the number of wood:\n";
	cin >> N;
	cout << "Please input their lengths:\n";
	H.input(N);
	H.adjust();
	res=Huffman(H);
	cout << "The minimal price is:\n";
	cout << res<<endl;
	system("pause");
	return 0;
}