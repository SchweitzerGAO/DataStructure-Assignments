#include<iostream>
#include"list.h"
int main()
{
	List A, B;
	List result;
	cout << "Please input the first list(-1 to stop):\n";
	A.input();
	cout << "Please input the second list(-1 to stop):\n";
	B.input();// get data from keyboard
	cout << "Their intersection is:\n";
	if (A.intersection(B, result))// if there are same elements in 2 sets
	{
		result.output();//output the result
	}
	else
	{
		cout << "NULL\n";
	}
	system("pause");
	return 0;
}