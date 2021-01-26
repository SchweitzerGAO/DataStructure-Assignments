#include<iostream>
#include<string>
#include<cstring>
#include"calcStack.h"
using namespace std;
void DisplayHelp();
bool pseudo_brktmatch(const string&);
int main()
{
	Stack<double> sd;
	Stack<char> sc;
	char opt;
	double res = 0;
	string s;
	DisplayHelp();
	cout << "Input \'y\' to open the calculator:\n";
	while (cin >> opt && opt == 'y')
	{
		int ch_ct = 0, di_ct = 0;
		cout << "Please input the expression:\n";
		cin >> s;
		if (!pseudo_brktmatch(s))
		{
			cerr << "Bracket Matching Error!\n";
			system("pause");
			exit(1);
		}//bracket matching
		for (int i = 0; i < s.size()&&s[i]!='='; i++)
		{
			if (isdigit(s[i]))
			{
				di_ct++;
			}
			else
				ch_ct++;
		}
		if (ch_ct == 0||(s[0]=='-'&&ch_ct==1))
		{
			if (s[s.size() - 1] == '=')
			{
				for (int i = 0; s[i] != '='; i++)
				{
					cout << s[i];
				}
				cout << endl;
			}//deal with pure number input
			else
			{
				cerr << "Format Wrong\n";
				system("pause");
				exit(1);
			}
		}
		else if(di_ct==0)
		{
			cerr << "No Number Error!\n";
			system("pause");
			exit(1);
		}
		else
		{ 
			calculate(sd, sc, s, res);
			cout << res << endl;
		}
		cout << "Input \'y\' to continue, \'n\' to exit:\n";
	}
	system("pause");
	return 0;
}
void DisplayHelp()
{
	cout.setf(ios::left);
	cout << "Calculator\n";
	cout << "========================\n";
	cout << "Function List\n";
	cout << "Add£¨+£©\tMinus£¨-£©\n";
	cout << "Multiple£¨*£©\tDivision£¨/£©\n";
	cout << "Power£¨^£©\tModulus£¨%£©\n";
	cout << "Bracket\n";
	cout<<"ALWAYS INPUT \'=\' AT THE END OF THE EXPRESSION!\n";
	cout << "========================\n";
	
	return;
}
bool pseudo_brktmatch(const string& s)
{
	int left = 0, right = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '(')
		{
			left++;
		}
		else if (s[i] == ')')
		{
			right++;
		}
	}
	return left == right;
}
