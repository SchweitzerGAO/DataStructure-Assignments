#ifndef LINK_H_
#define LINK_H_
#include<iostream>
using namespace std;
class LNode
{
public:
	int val;
	LNode* next;
	LNode(const int& i, LNode* p = NULL)
	{
		val = i;
		next = p;
	}
	LNode(LNode* p = NULL)
	{
		next = p;
	}
};// class LNode
class List
{
private:
	LNode* first;
public:
	List()
	{
		first = new LNode;
		if (first == NULL)
		{
			cerr << "Allocation Error!\n";
			exit(1);
		}//check if the allocation is good
	}
	~List() { makeEmpty(); }
	void makeEmpty();//make the list empty, used in the destructor
	void input();
	void output()const;
	bool intersection(const List& L, List& result)const;
	void purge();
};//class List
void List::makeEmpty()
{
	LNode* temp;
	while (first->next)
	{
		temp = first->next;//record the current 'next' node
		first->next = temp->next;//change the 'next' node
		delete temp;//delete one node of the list
	}
	return;
}
void List::input()
{
	int i;//the value scope of every node
	LNode* temp = first;
	LNode* newNode;
	while (cin >> i && i != -1)
	{
		newNode = new LNode;
		if (newNode == NULL)
		{
			cerr << "Allocation Error!\n";
			exit(1);
		}// judge good alloc
		newNode->val = i;
		temp->next = newNode;//  make link
		temp = temp->next;// move the pointer
	}
	temp->next = NULL;// null tail
	return;
}
void List::output()const
{
	if (first->next == NULL)
	{
		cerr << "Empty List!";
		exit(1);
	}// null tail error
	LNode* temp = first->next;
	while (temp)
	{
		if (temp == first->next)
		{
			cout << temp->val;
		}
		else
		{
			cout << ' ' << temp->val;
		}// ensure that there is no spaces 
		temp = temp->next;
	}
	cout << endl;
	return;
}
void List::purge()// the list will always be sorted, so...
{
	LNode* current = first->next;
	LNode* temp;
	while (current->next)
	{
		temp = current->next;
		if (temp->val == current->val)// if there is a same node
		{
			current->next = temp->next;//maintian linking
			delete temp;//delete it
		}
		else
			current = current->next;// else move the pointer
	}
}
bool List::intersection(const List& L, List& result)const
{
	if (first->next == NULL || L.first->next == NULL)
	{
		return false;
	}
	LNode* pa = first->next;
	LNode* pb = L.first->next;
	LNode* pres = result.first;
	while (pa && pb)//Sorted, traverse simultaneously, reducing the time complexity
	{
		LNode* temp;
		if (pa->val == pb->val)// if the value equals,meaning that an element is the same
		{
			temp = new LNode;
			temp->val = pa->val;//copy a new node to the result list
			temp->next = pres->next;
			pres->next = temp;//making link
			pres = pres->next;
			pa = pa->next;
			pb = pb->next;// move the working pointer
		}
		else if (pa->val < pb->val)// if lesser
		{
			pa = pa->next;// move pa, because the elements after is bigger
		}
		else
		{
			pb = pb->next;// move pb
		}
	}
	pres->next = NULL;//set the tail to null
	if (result.first->next)// if result list not empty
	{
		result.purge();// no repeated elements in a set
		return true;
	}
	else
	{
		return false;
	}
}
#endif

