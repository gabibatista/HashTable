#pragma once
#include <list>
#include <string>
using std::string;

class HashTable
{
private:
	int size = 10;
	/*COMO VOU AUMENTAR A HASHTABLE?*/
	static const int tableSize = 10;
	struct item {
		int ra;
		std::string name;
		item* next;
	};

	item* hashTable[tableSize];

public:
	HashTable();
	~HashTable();
	int Hash(int key);
	void AddItem(int ra, string name);
	void DeleteItem(int ra);
	item* Search(int ra);
	item* Search(string name);
	int NumberOfItems(int index);
	void PrintTable();
	int TotalOfPositionsUsed();
};

