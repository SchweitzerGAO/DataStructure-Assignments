#include"familytree.h"
using namespace std;
void displayMenu();
void Tree::ancestor()
{
	root = new treeNode;
	if (root == nullptr)
	{
		cout << "Allocation Error!\n";
		exit(1);
	}
	current = root;
	cout << "Please initialize a family tree:\n";
	cout << "Please input the ancestor's name:";
	cin >> root->name;
	cout << "The ancestor of the family is:" << root->name<<endl;
}//create a tree with the ancestor's name
bool Tree::search(treeNode* r,const string& n)
{
	bool res = false;
	if (r->name == n)
	{
		current = r;
		res = true;
	}//found
	else
	{
		treeNode* q = r->first_child;
		while (q != nullptr && !(res = search(q, n)))//recursion finding
		{
			q = q->next_sibling;
		}
	}
	return res;
}
bool Tree::search_prior(treeNode* r, const string& n,int& tag)//'tag' to mark the type of prior
{
	bool res = false;
	if (r->first_child)
	{
		if (r->first_child->name == n)//parent is prior
		{
			current = r;
			tag = 1;
			res = true;
		}
		else
		{
			treeNode* q = r->first_child;
			while (q != nullptr && !(res = search_prior(q, n, tag)))
			{
				q = q->next_sibling;
			}
		}
	}
	if (r->next_sibling)//sibling is prior
	{
		if (r->next_sibling->name == n)
		{
			current = r;
			tag = 2;
			res = true;
		}
		else
		{
			treeNode* q = r->first_child;
			while (q != nullptr && !(res = search_prior(q, n, tag)))
			{
				q = q->next_sibling;
			}
		}
	}
	return res;
}
void Tree::Delete(treeNode* r)
{
	treeNode* q = r->first_child,*temp;
	while (q)//while q is not null
	{
		temp = q->next_sibling;//store the next sibling
		Delete(q);//recursion
		q = temp;//update q
	}
	delete r;//delete root
}
void Tree::output(treeNode* r)
{
	treeNode* q = r->first_child;
	if (q)//if node 'q' has children
	{
		cout << r->name << "'s child(ren) is(are):";
		while (q)
		{
			cout << q->name << ' ';
			q = q->next_sibling;
		}//output all the children
		cout << endl;
	}
	else
	{
		cout << r->name << " has no children\n";
	}
}
void Tree::build()
{
	string to_do;
	cout << "Please input the name of the person to build a family:";
	cin >> to_do;
	if (!search(root, to_do))
	{
		cerr << "This person doesn't exist!\n";
		return;
	}
	if (current->first_child)
	{
		cerr << "Can't build family because this person already has one!\n";
		return;
	}
	int num;
	treeNode* newNode, * temp=current;
	string str;
	cout << "Please input the number of the child(ren):";
	cin >> num;//number of child(ren)
	cout << "Please input the child(ren)'s name in order:";
	for (int i = 0; i < num; i++)
	{
		newNode = new treeNode;
		if (newNode == nullptr)
		{
			system("pause");
			exit(1);
		}
		cin >> str;
		newNode->name = str;
		if (i == 0)
		{
			temp->first_child = newNode;
			temp = newNode;
		}//first child
		else
		{
			temp->next_sibling = newNode;
			temp = temp->next_sibling;
		}//next sibling
	}
	output(current);
}
void Tree::insert()
{
	string to_do;
	cout << "Please input the name of the person to insert a child:";
	cin >> to_do;
	if (!search(root, to_do))
	{
		cerr << "This person doesn't exist!\n";
		return;
	}
	treeNode* newNode = new treeNode;
	if (newNode == nullptr)
	{
		system("pause");
		exit(1);
	}
	string str;
	cout << "Please input the name of this child:";
	cin >> str;
	newNode->name = str;
	if (current->first_child)
	{
		treeNode* temp = current->first_child;
		while (temp->next_sibling)
		{
			temp = temp->next_sibling;
		}
		temp->next_sibling = newNode;
	}//find the last sibling
	else
	{
		current->first_child = newNode;
	}//the next is the first child
	output(current);
	
}
void Tree::remove()
{
	if (root->name == "")
	{
		cerr << "Empty Tree Error!\n";
		return;
	}
	string to_do;
	treeNode* temp;
	int tag = 0;
	cout << "Please input the name of the person whose family to be dismissed:";
	cin >> to_do;
	if (root->name == to_do)
	{
		Delete(root);
		cout << "Family tree destroyed\n";
		system("pause");
		exit(1);
	}
	if (!search_prior(root, to_do,tag))
	{
		cerr << "This person doesn't exist!\n";
		return;
	}
	if (tag==1)//parent
	{
		output(current->first_child);
		temp = current->first_child;
		current->first_child = current->first_child->next_sibling;//modify first child
		Delete(temp);
	}
	if (tag==2)//sibling
	{
		output(current->next_sibling);
		temp = current->next_sibling;
		current->next_sibling = current->next_sibling->next_sibling;//modify next sibling
		Delete(temp);
	}
	cout << "Delete successfully!\n";
}
void Tree::modify()
{
	string to_do;
	cout << "Please input the name of the person to change name:";
	cin >> to_do;
	if (!search(root, to_do))
	{
		cerr << "This person doesn't exist!\n";
		return;
	}
	string newName,oldName;
	oldName = current->name;
	cout << "Please input the new name:";
	cin >> newName;
	current->name = newName;
	cout << oldName << " has changed the name to " << newName << endl;
}
void Tree::All(Queue& Q)
{
	int i = 1;
	treeNode* fro,*temp;
	cout << "Gen " << i <<":\t";
	cout << root->name << endl;
	Q.push(this->root);
	while (!Q.isEmpty())
	{
		bool tag = false;//tag to determine whether to output an "endl"
		fro= Q.Front();
		temp = fro->first_child;
		if (temp)//temp has child
		{
			tag = true;//modify tag to true
			++i;
			cout << "Gen " << i << ":\t";
		}//generation info
		while (temp)
		{
			cout << temp->name << ' ';
			Q.push(temp);
			temp = temp->next_sibling;
		}
		if (tag)
		{
			cout << endl;
		}
		Q.pop();
	}
}
int main()
{
	displayMenu();
	Tree fm_tree;
	Queue Q;
	char opt;
	cout << "\nPlease choose the option:";
	cin >> opt;
	while (opt != 'F' && opt != 'f')
	{
		switch (opt)
		{
		case 'A':
		case 'a':
		{
			fm_tree.build();
			break;
		}
		case 'B':
		case 'b':
		{
			fm_tree.insert();
			break;
		}
		case 'C':
		case 'c':
		{
			fm_tree.remove();
			break;
		}
		case 'D':
		case 'd':
		{
			fm_tree.modify();
			break;
		}
		case 'E':
		case 'e':
		{
			fm_tree.All(Q);
			break;
		}
		default:
		{
			cerr << "Invaild option!\n";
			break;
		}
		}
		cout << "\nPlease choose the option:";
		cin >> opt;
	}
	cout << "Goodbye!\n";
	system("pause");
	return 0;
}
void displayMenu()
{
	cout << "-------------------------\n";
	cout << "Family Tree Manage System\n";
	cout << "Option List:\n";
	cout << "A:Build a family \nB:Insert a child\nC:Dismiss a family\nD:Change name\nE:Output all the tree\nF:Exit\n";
	cout << "-------------------------\n";
}