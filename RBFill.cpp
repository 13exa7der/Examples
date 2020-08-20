#include <iostream>
#include <ctime>

class RB_Tree
{
	class Node
	{
	public:
		static int count;
		Node *left;
		Node *right;
		char color;
		int data;

		Node(int data)
		{
			this->data = data;
			left = right = nullptr;
			color = 'r';
		}
	};

	Node *root;


	Node* Insert_Step(Node *current, const int &data) // добавление элемента 
	{
		if (current->data == data)
		{
			return nullptr;
		}

		if (current->data > data)
		{
			if (current->left) 
			{ 
				auto t = Insert_Step(current->left, data);
				if (t == nullptr)
				{
					return nullptr;
				}
				current->left = t;
			}
			else
			{
				current->left = new Node(data);
			}
		}
		else
		{
			if (current->right) 
			{ 
				auto t = Insert_Step(current->right, data);
				if (t == nullptr)
				{
					return nullptr;
				}
				current->right = t; 
			}
			else
			{
				current->right = new Node(data);

			}
		}
		//балансировка после добавления и установка корня на чёрный
		if (root == current)
		{
			root = current = Balance(current);
			root->color = 'b';
		}
		else
		{
			current = Balance(current);
		}

		return current;
	}


	Node *Balance(Node* current)
	{
		if (current->color == 'b') //только, если дедушка чёрный (иначе не будет двух красных подряд ниже без учёта дедушки)
		{
			if (current->right && current->right->color == 'r') //(если есть) проверка правого сына
			{
				Node * son = current->right;
				if (son->right && son->right->color == 'r') //(если есть) обработка правого внука
				{
					if (current->left && current->left->color == 'r') // дядя красный и он красный
					{
						son->color = current->color;
						ChangeColor(current, current->left);
						return current;

					}
					else
					{

						return LeftRotation(current);;
					}
				}
				if (son->left && son->left->color == 'r') //(если есть) обработка левого внука 
				{
					if (current->left && current->left->color == 'r') // дядя есть и он красный
					{
						son->color = current->color;
						ChangeColor(current, current->left);
						return current;
					}
					else
					{
						current->right = RightRotation(son);
						return LeftRotation(current);;
					}
				}
			}

			if (current->left && current->left->color == 'r') // (если есть) проверка левого сына
			{
				Node * son = current->left;
				if (son->left && son->left->color == 'r') //(если есть) обработка левого внука
				{
					if (current->right && current->right->color == 'r') // дядя есть и он красный 
					{
						son->color = current->color;
						ChangeColor(current, current->right);
						return current;

					}
					else
					{

						return RightRotation(current);;
					}
				}
				if (son->right && son->right->color == 'r') //(если есть) обработка правого внука
				{
					if (current->right && current->right->color == 'r') //дядя есть и он красный 
					{
						son->color = current->color;
						ChangeColor(current, current->right);
						return current;

					}
					else
					{
						current->left = LeftRotation(son);
						return RightRotation(current);
					}
				}
			}

		}
		return current; // не понадобилась
	}


	Node * RightRotation(Node *current) //правое вращение
	{
		Node *temp = current->left;
		current->left = temp->right;
		temp->right = current;
		ChangeColor(current, temp); //смена цвета отца и сына при вращении

		return temp;
	}

	Node * LeftRotation(Node *current) //левое вращение
	{
		Node *temp = current->right;
		current->right = temp->left;
		temp->left = current;
		ChangeColor(current, temp); //смена цвета отца и сына при вращении

		return temp;
	}

	void ChangeColor(Node* first, Node *second) //смена цвета
	{
		char temp = first->color;
		first->color = second->color;
		second->color = temp;
	}

	bool Find_Step(Node *current, const int &data)
	{
		if (current->data == data)
		{
			return 1;
		}

		if (current->left)
		{
			if (Find_Step(current->left, data))
			{
				return 1;
			}
		}

		if (current->right)
		{
			if (Find_Step(current->right, data))
			{
				return 1;
			}
		}

		return 0;
	}

	void View_Step(Node* current)
	{
		if (current->left) { View_Step(current->left); }
		printf("%d ", current->data);
		if (current->left)
		{
			printf("%d ", current->left->data);
		}
		else
		{
			printf("null ");
		}
		if (current->right)
		{
			printf("%d ", current->right->data);
		}
		else
		{
			printf("null ");
		}

		if (current->color == 'r')
		{
			printf("R\n");
		}
		else
		{
			printf("B\n");
		}

		if (current->right) { View_Step(current->right); }
	}


public:

	RB_Tree()
	{
		root = nullptr;
	}
	RB_Tree(int data)
	{
		root = new Node(data);
		root->color = 'b';
		Node::count++;
	}

	void Insert(const int &data)
	{
		if (root)
		{
			Insert_Step(root, data);
		}
		else
		{
			root = new Node(data);
			root->color = 'b';
		}
		Node::count++;
	}

	bool Find(const int &data)
	{
		if (root)
		{
			return Find_Step(root, data);
		}
		else
		{
			return 0;
		}
	}


	void View()
	{
		printf("%d\n", Node::count);
		if (root) { View_Step(root); };
	}

	void Clean(Node * current)
	{
		if (current)
		{
			if (current->right) { Clean(current->right); }
			if (current->left) { Clean(current->left); }
			delete current;
		}
	}

	~RB_Tree()
	{
		Clean(root);
	}
};

int RB_Tree::Node::count = 0;

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	RB_Tree  mytree;

	int n;
	std::cin >> n;



	for (int i = 0; i < n; i++)
	{
		int t, v;
		std::cin >> t >> v;
		if (!t)
		{
			mytree.Insert(v);
		}
		else
		{
			if (mytree.Find(v))
			{
				printf("Yes\n");
			}
			else
			{
				printf("No\n");
			}
		}
	}


	mytree.View();

	


	return 0;
}