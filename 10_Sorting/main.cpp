#include"sort.h"
#include<cstdlib>
#include<cstring>
#include<ctime>
const int TIMES = 100;
using namespace std;
void displayMenu();
void generRandomNum(int*, int);
void bubbleSort(int* arr, int n)
{
	long long swap = 0;//the swapping times
	for (int i = 0; i < n-1; i++)
	{
		int temp;
		for (int j = n-1; j>i; j--)//traversing the elems after current
		{
			if (arr[j-1] > arr[j])//if current is bigger
			{
				temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
				swap++;
			}//swap them
		}
	}
	cout << "Swapping times of bubble sort:" << swap << endl;
}//bubble sort
void insertSort(int* arr, int n)
{
	int i, j;
	int key;
	long long swap = 0;
	for (i = 1; i < n; i++)
	{
		key = arr[i];//store the elem to compare
		j = i;
		while (j > 0 && key < arr[j - 1])//if less
		{
			arr[j] = arr[j - 1];//move to next position
			swap++;
			j--;//compare the former pos 
		}
		arr[j] = key;//the correct pos of a[i]
		swap++;
	}
	cout << "Swapping times of insert sort:" << swap << endl;
}//insert sort
void selectionSort(int* arr, int n)
{
	int i, j, smallest;
	int temp;
	long long swap = 0;
	for (i = 0; i < n - 1; i++)
	{
		smallest = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[smallest])
			{
				smallest = j;
				swap++;
			}//choose the smallest one

		}
		temp = arr[smallest];
		arr[smallest] = arr[i];
		arr[i] = temp;//swap the smallest to correct position
		swap++;
	}
	cout<< "Swapping times of selection sort:" << swap << endl;
}//selection sort
void shellSort(int* pi, int n)
{
	long long swap = 0;
	int gap = n;//initial gap
	int i, j;
	int temp;
	while (gap > 1)//do the insert sort with gap
	{
		gap = gap / 3 + 1;//narrow the gap
		for (i = gap; i < n; i++)
		{
			if (pi[i] < pi[i - gap])
			{
				temp = pi[i];
				j = i - gap;
				while (j >= 0 && temp < pi[j])
				{
					pi[j + gap] = pi[j];
					swap++;
					j -= gap;
					
				}
				pi[j + gap] = temp;//see the code of "insertSort()",where '1' in that code becomes 'gap'
				swap++;
			}

		}
	}
	cout << "Swapping times of Shell sort:" << swap << endl;
}// Shell sort:in fact it is an insert sort with a gap(not less than 1)
void quickSort(int* arr, int left, int right,long long &swap)
{
	int standard = arr[left];
	int low = left;
	int high = right;
	if (low >= high)
	{
		return;
	}
	while (low < high)
	{
		while (low < high && arr[high] >= standard)
		{
			high--;
		}//find a element less than 'standard' 
		arr[low] = arr[high];//put it to the left
		while (low < high && arr[low] <= standard)
		{
			low++;
		}//greater than
		arr[high] = arr[low];//to right
		swap++;
	}
	arr[low] = standard;//put the standard number to the correct position(conquer)
	swap++;
	quickSort(arr, left, low - 1,swap);
	quickSort(arr, low + 1, right,swap);//divide(sort the subarrays)
}//quick sort
void mergeSort(int* arr, int left, int right, int* temp,long long& swap)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid, temp,swap);
		mergeSort(arr, mid + 1, right, temp,swap);//divide(sort of the left and right subarray)
		int p_temp = 0;
		int p_left = left;
		int p_right = mid + 1;
		while (p_left <= mid && p_right <= right)
		{
			if (arr[p_left] <= arr[p_right])
			{
				temp[p_temp] = arr[p_left];
				p_temp++;
				p_left++;
				swap++;
			}
			else
			{
				temp[p_temp] = arr[p_right];
				p_temp++;
				p_right++;
				swap++;
			}
		}
		while (p_left <= mid)
		{
			temp[p_temp++] = arr[p_left++];
		}
		while (p_right <= right)
		{
			temp[p_temp++] = arr[p_right++];
		}//a typical merge step to a temporary array(conquer)
		for (int i = 0; i <= right - left; i++)
		{
			arr[left + i] = temp[i];
		}//copy the data from temporary (sorted) to original array
	}
}//merge sort
int getMaxBit(int* arr, int n)//used in radixSort()
{
	int bits = 0;
	int max = arr[0];
	for (int i = 1; i < n; i++)//find the max element
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	while (max != 0)//get the bit of the max element
	{
		bits++;
		max /= 10;
	}
	return bits;
}
void radixSort(int* arr, int n)//LSD
{
	long long swap = 0;
	int maxDigit = getMaxBit(arr, n);//get the digit of the maximum number
	int count[10];
	int* temp = new int[n];
	int radix = 1;
	for (int i = 0; i < maxDigit; i++)
	{
		memset(count, 0, 10 * sizeof(int));
		for (int j = 0; j < n; j++)// number of numbers in every bucket
		{
			int bucketNum = (arr[j] / radix) % 10;
			count[bucketNum]++;
			swap++;
		}
		for (int k = 1; k < 10; k++)//decide the pos of last elem in every bucket
		{
			count[k] = count[k - 1] + count[k];
		}
		for (int j = n - 1; j >= 0; j--)//put to correct pos
		{
			int r = (arr[j] / radix) % 10;
			temp[count[r] - 1] = arr[j];
			count[r]--;
			swap++;
			
		}
		for (int j = 0; j < n; j++)//copy to original array
		{
			arr[j] = temp[j];
		}
		radix *= 10;
	}
	delete[]temp;
	cout << "Swapping time of radix sort:" << swap << endl;
}//radix sort
//functions below are used by heapSort()
void shiftDown(int* arr, int start, int end,long long& swap)
{
	int parent = start;
	int child = 2 * start + 1;
	int temp = arr[parent];
	while (child <= end)
	{
		if (child<end && arr[child]>arr[child+1])
		{
			child++;
		}
		if (temp <= arr[child])
		{
			break;
		}
		else
		{
			arr[parent] = arr[child];
			swap++;
			parent = child;
			child = child * 2 + 1;
		}
	}
	arr[parent] = temp;
}
void adjust(int* arr, int n,long long& swap)
{
	int leaf = (n - 2) / 2;
	while (leaf >= 0)
	{
		shiftDown(arr, leaf, n - 1,swap);
		leaf--;
	}
}
void remove(int* arr, int n, int& val,long long&swap)
{
	int cap = n;
	val = arr[0];
	arr[0] = arr[cap - 1];
	cap--;
	shiftDown(arr, 0, cap - 1,swap);
}
void heapSort(int* arr, int n,long long&swap)
{
	int* temp = new int[n];
	int cap = n;
	int val;
	int i = 0;
	adjust(arr, cap,swap);//adjust to a heap
	while (cap > 0)//heap not empty
	{
		remove(arr, cap, val,swap);//remove and re-adjust
		temp[i] = val;
		i++;
		cap--;
	}
	for (int i = 0; i < n; i++)//copy
	{
		arr[i] = temp[i];
	}
	delete[]temp;
}//heap sort
int main()
{
	int number;
	char opt;
	displayMenu();
	cout << "Please input the number of random numbers:";
	cin >> number;
	cout << "Please choose your option:";
	cin >> opt;
	int* arr=nullptr;
	while (opt != '9')
	{
		switch (opt)
		{
		case '1':
		{
			arr = new int[number];
			generRandomNum(arr, number);
			for (int i = 0; i < number; i++)
			{
				cout << arr[i] << ' ';
			}
			cout << endl;
			clock_t start = clock();
			bubbleSort(arr, number);
			clock_t end = clock();
			double time = (double) (end - start) / CLOCKS_PER_SEC;
			cout << "Time used:" << time <<endl;
			for (int i = 0; i < number; i++)
			{
				cout << arr[i] << ' ';
			}
			cout << endl;
			delete[]arr;
			break;
		}
		case '2':
		{
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			insertSort(arr, number);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		case '3':
		{
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			selectionSort(arr, number);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		case '4':
		{
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			shellSort(arr, number);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		case '5':
		{
			long long swap = 0;
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			quickSort(arr, 0, number - 1, swap);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Swapping time of quick sort:" << swap << endl;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		case '6':
		{
			long long swap = 0;
			int* temp = new int[number];
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			mergeSort(arr, 0, number - 1,temp,swap);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Swapping time of merge sort:" << swap << endl;
			cout << "Time used:" << time << endl;
			delete[]arr;
			delete[]temp;
			break;
		}
		case '7':
		{
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			radixSort(arr, number);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		case '8':
		{
			long long swap = 0;
			arr = new int[number];
			generRandomNum(arr, number);
			clock_t start = clock();
			heapSort(arr, number,swap);
			clock_t end = clock();
			double time = double(end - start) / CLOCKS_PER_SEC;
			cout << "Swapping time of heap sort:" << swap << endl;
			cout << "Time used:" << time << endl;
			delete[]arr;
			break;
		}
		default:
		{
			cout << "Invalid operation!\n";
			break;
		}
		}
		cout << "Please choose your option:";
		cin >> opt;
	}
	system("pause");
	return 0;
}
void displayMenu()
{
	cout << "Sorting Algorithms\n";
	cout << "========================\n";
	cout << "Algorithm list:\n";
	cout << "1.Bubble sort\n2.Insert sort\n";
	cout << "3.Selection sort\n4.Shell sort\n";
	cout << "5.Quick sort\n6.Merge sort\n";
	cout << "7.Radix sort\n8.Heap sort\n";
	cout<<"9.Exit\n";
	cout << "========================\n";

}
void generRandomNum(int* arr, int n)
{
	srand(unsigned(time(0)));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % n;
	}
}
