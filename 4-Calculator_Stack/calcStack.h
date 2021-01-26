#ifndef CALCSTACK_H
#define CALCSTACK_H
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
//*******************************************
//class Stack
//*******************************************
template<class T>
class Stack
{
private:
	T* val;
	int topIdx;//topIdx always equals to the index of top element
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
	bool isEmpty() { return (topIdx== -1); }
	bool isFull() { return (topIdx== maxSize - 1); }
	void push(const T& x);
	void pop();
	T top();
	int max() { return maxSize; }
	int size() { return (topIdx + 1); }
};//template class Stack
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
}//push
template<class T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		cerr << "Empty Stack Error!\n";
		return;
	}
	--topIdx;
}//pop
template<class T>
T Stack<T>::top()
{
	return(val[topIdx]);
}//top

//*********************************************************
// functions below are the main functions of the calculator
//*********************************************************

// 1st: the operator comparing function to decide whether to push it in the stack or not

bool compare(const char& out, const char& in)//out: current operator in the string
											 //in: the top element in the stack

//if in is NOT MORE prior than out, the return value is true. Otherwise, it will be false
{
	if (out == '^' || out == '(')// the most prior operator 
	{
		return true;
	}
	if (out == '%')//second 
	{
		if (in == '^')
		{
			return false;
		}
		else
			return true;
	}
	else if (out == '*' || out == '/')//third
	{
		if (in == '^'||in=='%')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else//least '+' '-'
	{
		if (in == '(')// '(' is the least prior in the stack
			return true;
		else
			return false;
	}
}
//2nd function to append a digit char to a C string, helper of converting string into double 

void pc_append(char pc[],const char& c, int n)//pc: the string
											  //c: the current digit char
											  //n: a protective number,from corrupting memory
{
	if (strlen(pc) + 1 >= n)
	{
		cerr << "Overflow Error!\n";
		system("pause");
		exit(1);
	}
	pc[strlen(pc)] = c;
}
//3rd the operating function
double operate(double& a, double& b, const char &opr)//a: the first operating number
													 //b: the second operating number
													 //opr:the operator
{
	double ret_val=-1;
	switch (opr)
	{
	case '+':
	{
		ret_val = a + b;
		break;
	}
	case '-':
	{
		ret_val = a - b;
		break;
	}
	case '*':
	{
		ret_val = a * b;
		break;
	}
	case '/':
	{
		if (b == 0)
		{
			cerr << "Zero Division Error!\n";
			system("pause");
			exit(1);
		}//divided by 0
		ret_val = a / b;
		break;
	}
	case '%':
	{
		if (int(b) == 0)
		{
			cerr << "Zero Modulus Error!\n";
			system("pause");
			exit(1);
		}//modulus by 0
		ret_val = int(a) % int(b);
		break;
	}
	case '^':
	{
		ret_val = pow(a, b);
		break;
	}
	default:
		break;
	}
	return ret_val;
}
//4th the main processing function

void process(Stack<double>& sd, Stack<char>& sc, const string& s, double& ans,int start,int end)
//sd: stack storing the operands
//sc:stack storing operators
//ans: the result
//start:the starting position
//end:the ending position
{
	if (s[s.size()-1]!='=')
	{
		cerr << "Format Error!\n";
		system("pause");
		exit(1);
	}//the last character of the string must be an '='
	double opr_a, opr_b;//2 operands
	char number[15] = "\0";//the string used to store current operand
	for (int i = start; i < end && s[i] != '=';)//traversing the string from start to end
	{
		bool notsign = true;// to judge if a '+'or '-' is a sign
		while (isdigit(s[i]))
		{
			pc_append(number, s[i], 15);
			i++;
		}//store the number in a string
		if (number[0])//number string not empty
		{
			sd.push(atof(number));//push the number into the stack
			memset(number, '\0', 15);//clear the number 
		}
		if (!isdigit(s[i]) && s[i] != '=')//not numbers and not the last one
		{
			if (s[i] == ')')//dealing with ()
			{
				while (sc.top() != '(' && !sc.isEmpty())
				{
					opr_a = sd.top();
					sd.pop();
					opr_b = sd.top();
					sd.pop();//2 operands
					ans = (operate(opr_b, opr_a, sc.top()));//calculating
					sd.push(ans);//push the answer
					sc.pop();//pop the operator
				}
				if (sc.top() == '(')
					sc.pop();//ending this part
				i++;
				continue;
			}
			if (s[i] == '+' || s[i] == '-')//judge whether '+' or '-' is sign
			{
				if (!isdigit(s[i - 1])&&s[i-1]!=')')//if the char before '+' or '-' is not a number or it is not ')'
				{
					notsign = false;// a sign
					pc_append(number, s[i], 15);//append it into a C string
				}
			}
			if ((sc.isEmpty() || compare(s[i], sc.top())) && notsign)
			{
				sc.push(s[i]);//push a operator into a stack
			}
			else if (notsign)//if the current operator is not more prior than the stack top
			{
				while (!compare(s[i], sc.top()) && !sc.isEmpty())
				{
					opr_a = sd.top();
					sd.pop();
					opr_b = sd.top();
					sd.pop();
					ans = (operate(opr_b, opr_a, sc.top()));
					sd.push(ans);
					sc.pop();
				}//calculate
				sc.push(s[i]);//push the operator
			}
			i++;
		}
	}
	while (!sc.isEmpty() && !sd.isEmpty())
	{
		opr_a = sd.top();
		sd.pop();
		if (sc.isEmpty() || sd.isEmpty())
		{
			break;
		}
		opr_b = sd.top();
		sd.pop();
		ans = (operate(opr_b, opr_a, sc.top()));
		sd.push(ans);
		sc.pop();
	}//then pop the two stacks until one of them is empty
}
void calculate(Stack<double>& sd, Stack<char>& sc, const string& s,double& ans)//deal with some special issues
{
	int i_temp = 0;
	char c_temp[15] = "\0";
	double d_temp;
	if (s[0] == '-' || s[0] == '+')//begin with sign(+ or -)
	{
		if (isdigit(s[1]))//+(-)number
		{
			i_temp = 1;
			while (isdigit(s[i_temp]))
			{
				pc_append(c_temp, s[i_temp], 15);
				i_temp++;
			}
			d_temp = atof(c_temp);
			if (s[0] == '-')
			{
				d_temp = -d_temp;
			}
			sd.push(d_temp);
		}
		else if (s[1] == '(')//+(-)and a(
		{
			i_temp = 1;
			int start = i_temp;
			while (s[i_temp] != ')')
			{
				i_temp++;
			}
			i_temp++;
			process(sd, sc, s, ans, start, i_temp);//calculate the string in brackets
			while (!sd.isEmpty())
			{
				sd.pop();
			}
			if (s[0] == '-')
			{
				ans= -ans;
			}
			sd.push(ans);
		}
	}
	process(sd, sc, s, ans, i_temp, s.size());//calculate all the string
	return;
}
#endif
