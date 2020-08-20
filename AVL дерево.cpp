#include <iostream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <cstring>
#include <Windows.h>
#include <sstream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <list>
#include <forward_list>
#include <array>

using namespace std;


template <typename T>
class MyTree
{
	class Node
	{
	public:
		Node(T data)
		{
			left = right = nullptr;
			this->data = data;
			height = 1;
		}

		Node *left;
		Node *right;
		int height;
		T data;
	};
	Node *root;

	Node* Add(T data, Node* current)
	{
		if (data > current->data)
		{
			if (current->right != nullptr)
			{
				current->right = Add(data, current->right);
			}
			else
			{
				current->right = new Node(data);
			}
		}
		else
		{
			if (current->left != nullptr)
			{
				current->left = Add(data, current->left);
			}
			else
			{
				current->left = new Node(data);
			}
		}

		root == current ? root = current = Balance(current) : current = Balance(current);
		return current;
	}

	Node* Balance(Node * current)
	{
		Fixheight(current);
		if (Bfactor(current) == 2)
		{
			if (Bfactor(current->right)<0)
			{
				current->right = rightrotation(current->right);
			}
			current = leftrotation(current);
		}
		if (Bfactor(current) == -2)
		{
			if (Bfactor(current->left) > 0)
			{
				current->left = leftrotation(current->left);
			}
			current = rightrotation(current);
		}
		return current;
	}

	Node* leftrotation(Node *current)
	{
		Node * temp = current->right;
		current->right = temp->left;
		temp->left = current;
		Fixheight(current);
		Fixheight(temp);
		return temp;
	}

	Node* rightrotation(Node *current)
	{
		Node * temp = current->left;
		current->left = temp->right;
		temp->right = current;
		Fixheight(current);
		Fixheight(temp);
		return temp;
	}


	int Height(Node *current)
	{
		return current ? current->height : 0;
	}

	void Fixheight(Node *current)
	{
		int lf = Height(current->left);
		int rt = Height(current->right);
		lf > rt ? current->height = lf + 1 : current->height = rt + 1;
	}

	int Bfactor(Node *current)
	{
		return Height(current->right) - Height(current->left);
	}


public:


	MyTree()
	{
		root = nullptr;
	}
	MyTree(T data)
	{
		root = new Node (data);
	}


	void Add(T data)
	{
		if (root == nullptr)
		{
			root = new Node (data);
		}
		else
		{
			Add(data, root);
		}
	}


	/*void Erase(T data)
	{

	}*/

	void View()
	{
		View(root);
	}

	void View(Node * current)
	{
		cout << current->data << endl;
		if (current->left != nullptr)
		{
			View(current->left);
		}
		if (current->right != nullptr)
		{
			View(current->right);
		}
	}

};



int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	MyTree <int> first;
	
	for (int i = 0; i < 50; i++)
	{
		int a = rand() % 100 - 50;
		cout << a << endl;

		//int a;
		//cin >> a;
		first.Add(a);
	}
	
	first.View();


	return 0;
}


