
#include <iostream>
#include <ctime>
using namespace std;


// Specification B1 - Date class
class Date
{
	friend ostream& operator << (ostream& out, const Date& CurrentDate);
public:
	time_t CurrentTime = time(nullptr);
	tm *const TimeInfo = localtime(&CurrentTime);

	int Day = TimeInfo->tm_mday;
	int Month = 1 + TimeInfo->tm_mon;
	int Year = 1900 + TimeInfo->tm_year;
};

class InventoryObject
{
	friend istream& operator >> (istream& in, InventoryObject& Item);
	friend ostream& operator << (ostream& out, const InventoryObject& Item);
public:
	int IDNumber = 0;
	int Quantity = 1;
	float Price = 0;
	float RetailPrice = 0;
	Date DateAdded;
};

ostream& operator << (ostream& out, const Date& CurrentDate)
{
	out << CurrentDate.Month << "/" << CurrentDate.Day << "/" << CurrentDate.Year << endl;
	return out;
}

ostream& operator << (ostream& out, const InventoryObject& Object)
{
	out << "ID: " << Object.IDNumber << "\n";
	out << "Quantity: " << Object.Quantity << "\n";
	out << "Cost: " << Object.Price << endl;
	out << "Retail Price: " << Object.RetailPrice << endl;
	out << "Date Added: " << Object.DateAdded << endl;
	return out;
}

istream& operator >> (istream& InputSet, InventoryObject& Item)
{
	int IDNumber;
	cout << "Enter ID Number:" << endl;
	InputSet >> IDNumber;
	while (IDNumber < 10000 || IDNumber > 99999)
	{
		cout << "Enter valid ID Number (5 digits):" << endl;
		InputSet >> IDNumber;
	}
	Item.IDNumber = IDNumber;

	int Quantity;
	cout << "Enter item quantity:" << endl;
	InputSet >> Quantity;
	while (Quantity <= 0)
	{
		cout << "Enter valid quantity (greater than zero)" << endl;
		InputSet >> Quantity;
	}
	Item.Quantity = Quantity;

	float Cost;
	cout << "Enter item cost:" << endl;
	InputSet >> Cost;
	float value = (int)(Cost * 100 + .5);
	Cost = (float)value / 100;
	while (Cost <= 0)
	{
		cout << "Enter valid cost (greater than zero)" << endl;
		InputSet >> Cost;
	}
	srand(time(NULL));
	Item.Price = Cost;
	Item.RetailPrice = Cost + (Cost * (rand() % 5 + 1) / 10);
	return InputSet;
}

void DisplayMenu(char* inst)
{
	cout << "What would you like to do next?" << endl;
	cout << "<A>dd inventory" << endl;
	cout << "<D>elete inventory" << endl;
	cout << "<E>dit inventory" << endl;
	cout << "<P>rint inventory" << endl;
	cout << "<Q>uit programme" << endl;
	*inst = 'X';
	cin >> *inst;
	// Specification C4 - Menu Input Validation
	if (*inst == 'a')
	{
		*inst = 'A';
	}
	else if (*inst == 'd')
	{
		*inst = 'D';
	}
	else if (*inst == 'e')
	{
		*inst = 'E';
	}
	else if (*inst == 'p')
	{
		*inst = 'P';
	}
	else if (*inst == 'q')
	{
		*inst = 'Q';
	}
	while (*inst != 'A' && *inst != 'D' && *inst != 'E' && *inst != 'P' && *inst != 'Q')
	{
		cout << "please enter a valid menu selection." << endl;
		cin >> *inst;
		if (*inst == 'a')
		{
			*inst = 'A';
		}
		else if (*inst == 'd')
		{
			*inst = 'D';
		}
		else if (*inst == 'e')
		{
			*inst = 'E';
		}
		else if (*inst == 'p')
		{
			*inst = 'P';
		}
		else if (*inst == 'q')
		{
			*inst = 'Q';
		}
	}
}

void ProgrammeGreeting();

int main()
{
	ProgrammeGreeting();

	char Instruction = 'Q';
	int N = 1;
	bool ProgrammeIsRunning = true;
	// Specification C2 - Dynamic Array
	InventoryObject** InventoryMain = new InventoryObject*[N];
	InventoryObject** InventoryTemp = nullptr;

	for (int i = 0; i < N; i++) {

		InventoryMain[i] = new InventoryObject;
	}


	do
	{
		DisplayMenu(&Instruction);
		if (Instruction == 'A')
		{
			// Specification C3 - Resize Array
			InventoryObject* newObject = new InventoryObject;
			cin >> *newObject;

			N += 1;
			if (InventoryTemp != nullptr)
			{
				delete[] InventoryTemp;
				InventoryTemp = nullptr;
			}

			InventoryTemp = new InventoryObject*[N];
			for (int i = 0; i < N - 1; i++)
			{
				InventoryTemp[i] = InventoryMain[i];
			}

			InventoryTemp[N - 1] = newObject;

			delete[] InventoryMain;
			InventoryMain = InventoryTemp;
			InventoryTemp = nullptr;
		}
		else if (Instruction == 'D')
		{
			N -= 1;
			int DeletedID = (*InventoryMain[N]).IDNumber;
			if (InventoryTemp != nullptr)
			{
				delete[] InventoryTemp;
				InventoryTemp = nullptr;
			}

			InventoryTemp = new InventoryObject*[N];
			for (int i = 0; i < N; i++)
			{
				InventoryTemp[i] = InventoryMain[i];
			}

			delete[] InventoryMain;
			InventoryMain = InventoryTemp;
			InventoryTemp = nullptr;

			cout << "Deleted item ID#" << DeletedID << endl;
		}
		else if (Instruction == 'P')
		{
			for (int i = 0; i < N; i++) 
			{
				cout << *InventoryMain[i] << endl;
			}
		}
		else if (Instruction == 'E')
		{
			int IndexNo = 0;
			cout << "Enter the index of the inventory item (it's place in the list)" << endl;
			cin >> IndexNo;
			IndexNo -= 1;
			while (IndexNo < 0 || IndexNo > N - 1)
			{
				cout << "Please enter a number between 1 and " << N << endl;
				cin >> IndexNo;
				IndexNo -= 1;
			}

			cin >> *InventoryMain[IndexNo];
		}
		else if (Instruction == 'Q')
		{
			ProgrammeIsRunning = false;
		}
	} while (ProgrammeIsRunning);

	delete[] InventoryMain;
	return 0;
}

void ProgrammeGreeting()
{
	cout << "Welcome to the Inventory Inquisitor" << endl;
	cout << "By David Ferrel" << endl;
	cout << "3/24/2023"<< endl;
}