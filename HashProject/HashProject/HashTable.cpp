#include "stdafx.h"
#include "HashTable.h"
#include <iostream>


HashTable::HashTable()
{
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = *new std::list<item*>();
	}
}

void HashTable::AddItem(int ra, std::string name) {
	int index = Hash(name);

	item a = *new item();
	a.name = name;
	a.ra = ra;

	if (hashTable[index].size() == 0)
		hashTable[index].insert(&a);

	/*TÁ BEM ERRADO TALVEZ*/
}

HashTable::~HashTable()
{
}

int HashTable::Hash(std::string key) {
	int hash = 0, index;

	for (int i = 0; i < key.length(); i++)
	{
		hash += (int)key[i];
		std::cout << "hash = " << hash << std::endl;
	}

	index = hash % tableSize;
	/* we divide the hashCode for the tableSize and the reminder is the index*/

	return index;
}