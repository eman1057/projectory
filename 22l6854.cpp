#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

using namespace std;

template <typename k, typename v>
struct HeapItem
{
	k key;
	v value;
};
template <typename k, typename v>
class minHeap
{
	HeapItem <k, v>* arr;
	int capacity;
	int totalItems;
public:
	minHeap()
	{
		arr = 0;
		capacity = 0;
		totalItems = 0;
	}
	minHeap(int Capacity)
	{
		capacity = Capacity;
		arr = new HeapItem<k, v>[Capacity];
		totalItems = 0;
	}
	void insert(k Key, v Value)
	{
		if (totalItems == capacity)
		{
			capacity *= 2;
			HeapItem<k, v>* newArr = new HeapItem<k, v>[capacity];
			for (int i = 0; i < totalItems; i++)
			{
				newArr[i] = arr[i];
			}
			delete[] arr;
			arr = newArr;
		}
		arr[totalItems].key = Key;
		arr[totalItems].value = Value;
		totalItems++;
		int i = totalItems;
		while (i > 0)
		{
			i = i / 2;
			MinHeapify(i);
		}
	}
	bool decreaseKey(k Key, v Value)
	{
		int i = 0;
		bool check = false;
			
		for (; i < totalItems; i++)
		{
			if (arr[i].value == Value)
			{
				if (arr[i].key > Key)
				{
					arr[i].key = Key;
					check = true;
				}
				break;
			}
		}
		while (i > 0)
		{
			i = i / 2;
			MinHeapify(i);
		}
		return check;

	}
	~minHeap()
	{
		delete[]arr;
		arr = 0;
	}
	/*void Display()
	{
		for (int i = 0; i < totalItems; i++)
		{
			cout << "value: " << arr[i].value << "	key: " << arr[i].key;
			cout << endl;
		}
		cout << endl;
	}*/
	void MinHeapify(int i)
	{
		int l = 2 * i + 1;
		int r = l + 1;
		int smallest = i;
		if (l < totalItems && arr[l].key < arr[smallest].key)
			smallest = l;
		if (r < totalItems && arr[r].key < arr[smallest].key)
			smallest = r;
		if (smallest != i)
		{
			k n = arr[i].key;
			arr[i].key = arr[smallest].key;
			arr[smallest].key = n;
			v m = arr[i].value;
			arr[i].value = arr[smallest].value;
			arr[smallest].value = m;

			MinHeapify(smallest);
		}
	}
	void deleteKey(k Key)
	{
		for (int i = 0; i < totalItems; i++)
		{
			if (arr[i].key == Key)
			{
				arr[i].key = arr[totalItems - 1].key;
				arr[i].value = arr[totalItems - 1].value;
				totalItems--;


				int i = totalItems;
				while (i > 0)
				{

					i = i / 2;
					MinHeapify(i);

				}break;
			}
		}
	}
	void getMin(v& Value)
	{
		Value = arr[0].value;
	}
	void getMinKey(k& Key)
	{
		Key = arr[0].key;
	}
	bool isEmpty()
	{
		if (totalItems == 0)
			return true;
		return false;
	}
	void deleteMin()
	{
		deleteKey(arr[0].key);
	}
};

class Hospital
{
public:
	int ID;
	int time;

	Hospital()
	{
		ID = 0;
		time = 0;
	}
	Hospital(int id,int t)
	{
		ID = id;
		time = t;
	}
};

class Route
{
	int capacity;
	int* T;
	vector<list<int>> P;
	vector<list<Hospital>> V1;

public:
	Route()
	{
		capacity = 0;
		T = 0;
	}
	~Route()
	{
		delete[] T;
		T = 0;
	}
	void ReadFromFile()
	{
		string name;
		cout << "enter the file name: ";
		cin >> name;

		ifstream fin(name);
		
		if (!fin.is_open())
		{
			cout << "error opening the file";
		}
		int totalHos;

		fin >> totalHos;
		capacity = totalHos;

		int mainID;
		Hospital Hos;

		while (!fin.eof())
		{
			fin >> mainID;
			list<Hospital> List;
			while (true)
			{
				fin >> Hos.ID;
				if (Hos.ID == -1)   //-1 checker at the end of line
					break;
				fin >> Hos.time;

				List.push_back(Hos);

			}
			V1.push_back(List);
		}
	}
	void Print()
	{
		cout << "\n-------------------------------------------------------------\n";
		cout << "the Optimal Path from UN to Hospitals: \n";
		for (int i=0; i<capacity;i++)
		{
			cout << "Hospital " << i+1 << ":	";
			list <int>::iterator itr = P[i].begin();
			while(itr!=P[i].end())
			{
				if (*itr != 0)
					cout << "Hospital " << *itr << "	";
				else
					cout << "UN ";
				itr++;
			}
			cout << endl;
		}
		cout << "\n-------------------------------------------------------------\n";
		cout << "-------------------------------------------------------------\n";
		cout << "The optimal Time from UN to Hospitals: \n";
		int i = 1;
		while (i <= capacity)
		{
			cout << "HOSPITAL " << i << ":		" << T[i] << endl;
			i++;
		}
		cout << "\n-------------------------------------------------------------\n";
	}

	void CalculateOptimalPath()
	{
		minHeap<int, int> TIME(capacity+1);
		
		P.resize(capacity);


		TIME.insert(0, 0);  //for UN
		for (int i = 1; i < capacity+1; i++)   //for H1,2,3,4
		{
			TIME.insert(INT_MAX, i);
		}
		T = new int[capacity+1];    //+1 for UN
		int minID;
		int minTime;
		while (!TIME.isEmpty())
		{
			TIME.getMin(minID);
			TIME.getMinKey(minTime);
			list<Hospital>::iterator itr = V1[minID].begin();
			for (; itr != V1[minID].end(); itr++)
			{
				if (TIME.decreaseKey(itr->time + minTime, itr->ID))   //sets the optimal time
				{
					P[itr->ID-1].push_back(minID); 
				}
			}
			T[minID] = minTime;
			TIME.deleteMin();
		}
		 
	}
};

int main()
{
	Route Hospital;
	Hospital.ReadFromFile();
	Hospital.CalculateOptimalPath();
	Hospital.Print();
	return 0;
}