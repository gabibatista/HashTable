#pragma once
#include <list>
#include <string>

class HashTable
{
public:
	HashTable();
	~HashTable();
	int Hash(std::string key);
	void AddItem(int ra, std::string name);
	int NumberOfItems(int index);
	void PrintTable();

private:
	static const int tableSize = 10; 
	struct item {
		int ra;
		std::string name;
		item* next;
	};

	item* hashTable[tableSize];
};

