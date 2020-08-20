#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>



using namespace std;



int quant = 0;



class Node
{
public:
	string number;
	long long key;
	string left;
	string right;
	char color;
	Node()
	{

	}
	Node(string number, int key, string left, string right, char color)
	{
		this->number = number;
		this->key = key;
		this->left = left;
		this->right = right;
		this->color = color;
	}
};




bool Work(Node &node, vector <Node> &v, int c)
{
	if (node.color == 'B')
	{
		c++;
	}

	if (node.left == "null" || node.right == "null")
	{
		if (!quant)
		{
			quant = c;
		}
		else
		{
			if (!(c == quant))
			{
				return 0;
			}
		}
	}

	Node left;

	if (node.left != "null")
	{

		left = v[stoi(node.left) - 1];

		if (!(left.key < node.key))
		{
			return 0;
		}

		if (left.color == 'R')
		{
			if (node.color != 'B')
			{
				return 0;
			}
		}

		if (!(Work(left, v, c)))
		{
			return 0;
		}
	}

	Node right;

	if (node.right != "null")
	{
		right = v[stoi(node.right) - 1];

		if (!(right.key > node.key))
		{
			return 0;
		}
		if (right.color == 'R')
		{
			if (node.color != 'B')
			{
				return 0;
			}
		}


		if (!(Work(right, v, c)))
		{
			return 0;
		}
	}


	return 1;
}



int main()
{
	int n;
	cin >> n;

	if (n == 0)
	{
		cout << "YES" << endl;
		return 0;
	}

	string t;
	cin >> t;

	vector <Node> v;

	Node root;

	for (int i = 0; i < n; i++)
	{
		long long key;
		string number, left, right;
		char color;
		cin >> number >> key >> left >> right >> color;

		if (number == t)
		{
			root = Node(number, key, left, right, color);
		}

		v.push_back(Node(number, key, left, right, color));


	}

	sort(v.begin(), v.end(), [](const Node& n1, const Node& n2) 
	{return stoi(n1.number) < stoi(n2.number); });

	int c = 0;

	if (root.color == 'B')
	{
		if (Work(root, v, c))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	else
	{
		cout << "NO" << endl;
	}




	return 0;
}