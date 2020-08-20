#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <string>


using namespace std;





int main()
{
	char a[10001];
	cin.getline(a, 10001);

	pair <pair<string, string>, pair<string, string>> expr(pair<string, string>("", ""), pair<string, string>("", ""));

	pair <string, string> inv = pair<string, string>("", "");

	for (int i = 0; a[i] != '\0'; i++)
	{
		string temp = "";
		for (; i < a[i] != '\0'; i++)
		{
			if (a[i] == ' ')
			{
				break;
			}
			temp += a[i];
		}

		if (temp == "*" || temp == "/" || temp == "+" || temp == "-")
		{
			if (expr.second.first == "")
			{
				if (temp == "+")
				{
					inv.second = "(" + inv.second + " + " + expr.first.second + ")";
				}
				if (temp == "-")
				{
					inv.second = "(" + inv.second + " - " + expr.first.second + ")";
				}
				if (temp == "*")
				{
					inv.second = "(" + inv.second + " * " + expr.first.first + ")" + " + (" + inv.first + " * " + expr.first.second + ")";
				}
				if (temp == "/")
				{
					inv.second = "(" + inv.second + " * " + expr.first.first + ")" + " - (" + inv.first + " * " + expr.first.second + ")";
				}

				inv.first += temp + " " + expr.first.first;
				expr.first.first = "";
				expr.first.second = "";
			}
			else
			{
				if (temp == "*")
				{
					expr.first.second = "(" + expr.first.second + " * " + expr.second.first + ")" + " + (" + expr.first.first + " * " + expr.second.second + ")";
				}
				if (temp == "/")
				{
					expr.first.second = "(" + expr.first.second + " * " + expr.second.first + ")" + " - (" + expr.first.first + " * " + expr.second.second + ")";
				}

				if (temp == "+")
				{
					expr.first.second = "(" + expr.first.second + " + " + expr.second.second + ")";
				}

				if (temp == "-")
				{
					expr.first.second = "(" + expr.first.second + " - " + expr.second.second + ")";
				}

				expr.first.first += " " + temp + " " + expr.second.first;
				expr.first.first = "(" + expr.first.first + ")";
				expr.second.first = "";
				expr.second.second = "";
			}
			continue;
		}
		if (temp == "cos" || temp == "sqrt" || temp == "sin")
		{
			if (temp == "cos")
			{
				expr.first.second = "(-1 * sin" + expr.first.first + ")" + " * (" + expr.first.second + ")";
			}
			if (temp == "sin")
			{
				expr.first.second = "(cos" + expr.first.first + ")" + " * (" + expr.first.second + ")";
			}
			if (temp == "sqrt")
			{
				expr.first.second = "(0.5 * (1 / sqrt" + expr.first.first + "))" + " * (" + expr.first.second + ")";
			}

			expr.first.first = "(" + temp + expr.first.first + ")";
			continue;
		}
		if (expr.first.first != "")
		{
			if (expr.second.first == "")
			{
				expr.second.first = temp;
				if (temp == "x")
				{
					expr.second.second = "1";
				}
				else
				{
					expr.second.second = "0";
				}
			}
			else
			{
				inv.first += expr.first.first;
				inv.second += expr.first.second;
				expr.first.first = expr.second.first;
				expr.first.second = expr.second.second;
				expr.second.first = temp;
				if (temp == "x")
				{
					expr.second.second = "1";
				}
				else
				{
					expr.second.second = "0";
				}

			}
		}
		else
		{
			expr.first.first = temp;
			if (temp == "x")
			{
				expr.first.second = "1";
			}
			else
			{
				expr.first.second = "0";
			}
		}
	}
	if (inv.second == "")
	{
		if (expr.first.second == "")
		{
			inv.second = expr.second.second;
		}
		else
		{
			inv.second = expr.first.second;
		}
	}
	cout << inv.second << endl;

	return 0;
}