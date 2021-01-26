#include"Queue.h"
int main()
{
	int N,temp;
	bool flag = true;//to control no more space at the end
	Queue A, B;
	cout << "Please input the number of people waiting:\n";
	cin >> N;
	while (N <= 0)
	{
		cerr << "Please input a positive integer!\n";
		cin >> N;
	}//check if the input is valid
	cout << "Please input their numbers:\n";
	for (int i = 0; i < N; i++)
	{
		cin >> temp;
		if (temp % 2)
		{
			A.push(temp);
		}
		else
			B.push(temp);
	}// according to the rule, enqueue the 2 queues
	cout << "The order of completing:\n";
	while (!A.isEmpty() && !B.isEmpty())
	{
		if (!flag)
		{
			if (A.isEmpty()||B.isEmpty())
			{
				break;
			}//protect
			cout << ' ' << A.Front();
			A.pop();
			if (A.isEmpty())
			{
				break;
			}//as above
			cout << ' ' << A.Front();
			A.pop();
			cout << ' ' << B.Front();
			B.pop();//2 A for 1 B
		}// output with a prefix ' '
		else
		{
			if (A.isEmpty() || B.isEmpty())
			{
				break;
			}
			cout<< A.Front();
			A.pop();
			if (A.isEmpty())
			{
				break;
			}
			cout << ' ' << A.Front();
			A.pop();
			cout << ' ' << B.Front();
			B.pop();
			flag = false;
		}//without prefix ' '
	}
	while (!A.isEmpty())
	{
		if (!flag)
		{
			cout << ' ' << A.Front();
			A.pop();
		}
		else
		{
			cout << A.Front();
			A.pop();
			flag = false;
		}
	}
	while (!B.isEmpty())
	{
		if (!flag)
		{
			cout << ' ' << B.Front();
			B.pop();
		}
		else
		{
			cout << B.Front();
			B.pop();
			flag = false;
		}
	}//output the remaining elems
	cout << endl;
	system("pause");
	return 0;
}