#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <iomanip>

using namespace std;

//const methods

class DATE
{
public:

	DATE()
	{
		int year = 0;
		int month = 0;
		int day = 0;
	}

	DATE(const int& new_year, const int& new_month, const int& new_day)
	{
		year = new_year;

		if (new_month > 12 || new_month < 1)
		{
			throw runtime_error("Month value is invalid: " + to_string(new_month));
			return;
		}
		else
		{
			month = new_month;
		}

		if (new_day > 31 || new_day < 1)
		{
			throw runtime_error("Day value is invalid: " + to_string(new_day));
			return;
		}
		else
		{
			day = new_day;
		}
		
	}

	int GetYear() const
	{
		return year;
	}

	int GetMonth() const
	{
		return month;
	}

	int GetDay() const
	{
		return day;
	}


private:

	int year;
	int month;
	int day;


};

istringstream& operator>>(istringstream& stream, DATE& date)
{
	if (stream)
	{
		string whole_line;
		stream >> whole_line;
		stringstream stream2(whole_line);
		 
		int year, month, day;
		stream2 >> year;
		if (stream2.peek() != '-')
		{
			throw runtime_error("Wrong date format: " + whole_line);//
		}
		else
		{
			stream2.ignore(1);
		}
		stream2 >> month;
	
		if (stream2.peek() != '-')
		{
			throw runtime_error("Wrong date format: " + whole_line);//
		}
		else
		{
			stream2.ignore(1);
		}
		set<char> OKones = { '+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

		if (OKones.count(char(stream2.peek())) == 0)
		{
			throw runtime_error("Wrong date format: " + whole_line);//
		}
		else 
			stream2 >> day;

		if (stream2.peek() != EOF)
		{
			throw runtime_error("Wrong date format: " + whole_line);
		}
		else
			date = DATE(year, month, day);
	}

	return stream;
}

ostream& operator<<(ostream& stream, const DATE& date)
{
	stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2) << setfill('0') << date.GetMonth() << '-' << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

bool operator<(const DATE& left, const DATE& right)
{
	long first = 365 * left.GetYear() + 31 * left.GetMonth() + left.GetDay();
	long second = 365 * right.GetYear() + 31 * right.GetMonth() + right.GetDay();
	return first < second;
}


class DATABASE
{
public:
	void ADD_1(const DATE& date, const string& event)
	{
		DATABASE[date].insert(event);

	}

	bool DEL_1(const DATE& date, const string& event) 
	{
		if (DATABASE.count(date) != 0)
		{
			if (DATABASE.at(date).count(event) != 0) 
			{
				DATABASE[date].erase(event);
				return 1;
			}
			else return 0; // means nothing was here
		}
		else return 0; // means nothing was here
	}

	int DEL_N(const DATE& date)
	{
		if (DATABASE.count(date) != 0)
		{
			int amount = DATABASE[date].size();
			DATABASE.erase(date);
			return amount;
		}
		else return 0;
	}

	set<string> FIND_1(const DATE& date) const
	{
		if (DATABASE.count(date) != 0)
		{
			return DATABASE.at(date);
		}
		else return {};
	}

	void PRINT() const
	{
		for (const auto& c : DATABASE)
		{
			auto it = c.second.end();
			it--;
			for (const auto& k : c.second)
			{
				if (k != (*it))
				{

					cout << c.first << ' ' << k << endl;
				}
				else cout << c.first << ' ' << k << endl;
			}
			
		}
	}

private:
	map<DATE, set<string>> DATABASE;

};


int main() 
{
	DATABASE database;
	string str;

	while (getline(cin, str))
	{
		string query;
		istringstream kek(str);

		kek >> query;

		if (query == "Add")
		{
			try // since incorrect input is a possibility
			{
				DATE date;
				string event;

				kek >> date >> event;

				database.ADD_1(date, event);
			}

			catch(exception& error)
			{
				cout << error.what();
			}
		}

		else if (query == "Del")
		{
			try // since incorrect input is a possibility
			{
				DATE date;
				string event;

				kek >> date;

				if (kek.peek() == ' ') //after that there will be another word- that is, a command to delete a certain event
				{
					kek >> event;

					if (database.DEL_1(date, event)  == 1)
					{
						cout << "Deleted successfully" << endl;
					}

					else
					{
						cout << "Event not found" << endl;
					}
				}
				else
				{
					cout << "Deleted "<< to_string(database.DEL_N(date)) <<" events" << endl; 
				}
			}

			catch (exception& error)
			{
				cout << error.what();
			}
		}

		else if (query == "Find")
		{
			try // since incorrect input is a possibility
			{
				DATE date;
				string event;

				kek >> date;

				set<string> temp_set = database.FIND_1(date);
				//sort(begin(temp_set), end(temp_set));
				if (temp_set.empty())
				{
					
				}
				else
				{
					auto it = temp_set.end();
					it--;
					for (const auto& c : temp_set)
					{
						if (c != (*it))
						{
							cout << c << endl;
						}
						else cout << c;
					}
					cout << endl;
				}
			}

			catch (exception& error)
			{
				cout << error.what();
			}
		}

		else if (query == "Print")
		{
			database.PRINT();
			cout << endl;
		}

		else if (query.size() != 0)
		{
			cout << "Unknown command: " << query << endl;
		}
	}

	return 0;
}
