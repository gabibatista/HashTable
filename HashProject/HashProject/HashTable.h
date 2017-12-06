#pragma once
#include <list>
#include <string>
using std::string;

class HashTable
{
private:
	float threshold;
	int maxSize, size, tableSize;
	struct item {
		int ra;
		std::string name;
		item* next;
	};

	item** hashTable;
	void resize();

public:
	HashTable();
	~HashTable();
	int Hash(string key);
	void AddItem(int ra, string name);
	void DeleteItem(int ra);
	item* Search(int ra);
	int NumberOfItems(int index);
	void PrintTable();
	int TotalOfPositionsUsed();
};

