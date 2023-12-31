#include "occupancyRegistry.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

bool compare(occupancy* o1, occupancy* o2)
{
	return(o1->date < o2->date);
}

void occupancy::writeToFile()
{
	sort(OCCUPANCY.begin(), OCCUPANCY.end(), compare);
	fstream file;
	file.open("OCCUPANCY.txt", ios::out | ios::trunc);
	string text;
	for (int i = 0; i < OCCUPANCY.size(); i++)
	{
		bool flag = 0;
		for (int j = 0; j < OCCUPANCY[i]->roomNumber.size(); j++)
		{
			if (flag == 1)
			{
				text += "/";
			}
			flag = 1;
			if (OCCUPANCY[i]->isOccupied[j] == true)
			{
				text += "!";
			}

			text += to_string(OCCUPANCY[i]->roomNumber[j]);
		}
		text += "|";
		text += to_string(OCCUPANCY[i]->date);
		text += "\n";
	}
	file << text;
	file.close();
}
int occupancy::numOfDays(int checkIn, int checkOut)
{
	readFromFile();
	int days=0;
	for (int i = 0; i < OCCUPANCY.size(); i++)
	{
		if (OCCUPANCY[i]->date >= checkIn && OCCUPANCY[i]->date < checkOut)
		{
			days++;
		}
	}
	return days;
}
void occupancy::readFromFile()
{
	OCCUPANCY.clear();
	string contents, line;
	fstream file;
	file.open("OCCUPANCY.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			string num;
			string date;
			bool occupied = false;
			bool flag = false;
			occupancy* newNode = new occupancy;
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == '|')
				{
					flag = true;
					newNode->roomNumber.push_back(stoi(num));
					num = "";
					if (occupied == true)
					{
						newNode->isOccupied.push_back(true);
						occupied = false;
					}
					else
					{
						newNode->isOccupied.push_back(false);
					}
				}
				if (flag == true && isdigit(line[i]))
				{
					date += line[i];
				}
				else
				{
					if (line[i] == '!')
					{
						occupied = true;
					}
					if (line[i] == '/')
					{

						newNode->roomNumber.push_back(stoi(num));
						num = "";
						if (occupied == true)
						{
							newNode->isOccupied.push_back(true);
							occupied = false;
						}
						else
						{
							newNode->isOccupied.push_back(false);
						}

					}
					if (isdigit(line[i]))
					{
						num += line[i];

					}
				}

			}
			if (isdigit(date[0]))
			{
					newNode->date = stoi(date);
			}
			OCCUPANCY.push_back(newNode);

		}
	}
	file.close();

}

void occupancy::modifyRegistry(int checkIn, int checkOut, vector<int>rooms, bool OnOff)
{
	readFromFile();
	int index;
	index = (checkIn - OCCUPANCY[0]->date);
	int index2 = numOfDays(checkIn, checkOut) + index;
	for (int i = index; i < index2; i++)
	{
		for (int j = 0; j < rooms.size(); j++)
		{
			for (int k = 0; k < OCCUPANCY[i]->roomNumber.size(); k++)
			{
				if (rooms[j] == OCCUPANCY[i]->roomNumber[k] && OnOff == true)
				{
					OCCUPANCY[i]->isOccupied[k] = true;

				}
				else if (rooms[j] == OCCUPANCY[i]->roomNumber[k] && OnOff == false)
				{
					OCCUPANCY[i]->isOccupied[k] = false;
				}
			}
		}
	}
	writeToFile();
}

bool occupancy::checkIfFree(int checkIn, int checkOut, vector<int> rooms)
{
	readFromFile();
		int index;
	index = (checkIn - OCCUPANCY[0]->date);
	int index2 = numOfDays(checkIn, checkOut) + index;

	for (int i = index; i <= index2; i++)
	{
		for (int j = 0; j < rooms.size(); j++)
		{
			for (int k = 0; k < OCCUPANCY[i]->roomNumber.size(); k++)
			{
				if (rooms[j] == OCCUPANCY[i]->roomNumber[k] && OCCUPANCY[i]->isOccupied[k] == true)
				{
					return false;
				}
			}
		}
	}
	return true;
}
