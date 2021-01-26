#include<iostream>
#include<string>
#include"student.h"
using namespace std;
int main()
{
	int loc;
	char option;
	string number;
	LinList L;
	L.input();
	L.output();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出）\n>>>";
	cin >> option;
	while (option != '0')//'0' to exit
	{
		switch (option)// choosing the operation
		{
		case '1':
		{
			cout << "请输入插入位置：\n>>>";
			cin >> loc;
			if(L.insert(loc))
			{
				L.output();
			}
			
			break;
		}
		case '2':
		{
			cout << "请输入删除位置：\n>>>";
			cin >> loc;
			if(L.remove(loc))
			{
				L.output();
			}
			break;
		}
		case '3':
		{
			cout << "请输入要搜索考生的考号：\n>>>";
			cin >> number;
			L.search(number);
			break;
		}
		case '4':
		{
			cout << "请输入要修改的考生的考号：\n>>>";
			cin >> number;
			if(L.modify(number))
			{
				L.output();
			}
			break;
		}
		case '5':
		{
			L.output();
			break;
		}
		default:
			cout << "暂无此操作项！\n";
		}
		cout << "请选择您要进行的操作\n>>>";
		cin >> option;
	}
	cout << "再见！\n";
	system("pause");
	return 0;
}