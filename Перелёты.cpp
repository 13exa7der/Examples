#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


class Flight
{
	string from;
	string to;
	double cost;
public:
	Flight(string from, string to, double cost) : to(to), from(from), cost(cost) {};

	string GetTo()
	{
		return to;
	}
	string GetFrom()
	{
		return from;
	}
	double GetCost()
	{
		return cost;
	}
};


bool InputFromFile(vector <Flight>& flights)
{
	fstream f;
	f.open("distances.txt");
	if (!f.is_open())
	{
		cout << "File error" << endl;
		return 0;
	}



	while (!f.eof())
	{
		string from = "";
		string to = "";
		double cost;
		char temp;
		f >> temp;
		if (temp == '"')
		{
			from += temp;
			f >> temp;
			while (temp != '"')
			{
				from += temp;
				f.get(temp);
			}
			from += temp;
		}
		f >> temp;
		while (temp != '"')
		{
			f >> temp;
		}
		to += temp;
		f >> temp;
		while (temp != '"')
		{
			to += temp;
			f.get(temp);
		}
		to += temp;
		f >> cost;
		flights.push_back(Flight(from, to, cost));
	}
	f.close();
}


double FindCost(vector <Flight> flights)
{
	double cost = 0;
	for (auto i : flights)
	{
		cost += i.GetCost();
	}
	return cost;
}

vector<Flight> Find(vector <Flight> flights, string from, string to)
{
	vector <Flight> result;
	double resultcost = 0;
	for (int i = 0; i < flights.size(); i++)
	{
		if (flights[i].GetFrom() == from)
		{
			if (flights[i].GetTo() == to)
			{
				if (flights[i].GetCost() < resultcost || resultcost == 0)
				{
					result.clear();
					result.push_back(flights[i]);
					resultcost = flights[i].GetCost();
					continue;
				}
			}
			vector <Flight> tempflights = flights;
			auto it = tempflights.begin();
			it += i;
			tempflights.erase(it);
			vector <Flight> tempres = Find(tempflights, flights[i].GetTo(), to);
			if (tempres.size() == 0)
			{
				continue;
			}
			if ((FindCost(tempres) + flights[i].GetCost()) < resultcost || resultcost == 0)
			{
				result.clear();
				result.push_back(flights[i]);
				for (int i = 0; i < tempres.size(); i++)
				{
					result.push_back(tempres[i]);
				}
				resultcost = (FindCost(tempres) + flights[i].GetCost());
			}

		}
	}

	return result;
	
}

void Input(string &from, string &to)
{
	char temp;
	cin >> temp;
	from += temp;
	cin >> temp;
	while (temp != '"')
	{
		from += temp;
		cin.get(temp);
	}
	from += temp;

	cin >> temp;
	to += temp;
	cin >> temp;
	while (temp != '"')
	{
		to += temp;
		cin.get(temp);
	}
	to += temp;
}


int main()
{
	vector <Flight> flights;

	if (!InputFromFile(flights))
	{
		return 0;
	}
	
	string from = "";
	string to = "";

	Input(from, to);

	vector <Flight> result = Find(flights, from, to);

	if (result.size() != 0)
	{
		cout << FindCost(result) << endl;
		cout << from << " ";
		for (int i = 0; i < result.size(); i++)
		{
			cout << result[i].GetTo() << " ";
		}
	}
	else
	{
		cout << "No route" << endl;
	}
	
	return 0;
}