#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
using std::list;
using std::cout;
using std::endl;


HashTable::HashTable()
{
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->name = "empty";
		hashTable[i]->ra = 0;
		hashTable[i]->next = nullptr;
	}
}

void HashTable::AddItem(int ra, std::string name) {
	int index = Hash(name);
	bool encontrou = false;

	item** auxiliar = &hashTable[index];

	item a = *new item();
	a.name = name;
	a.ra = ra;
	a.next = nullptr;	

	if (auxiliar == nullptr) {
		*auxiliar = &a;
	}
	else {
		if ((*auxiliar)->name == a.name && (*auxiliar)->ra == a.ra) {
			// já existe
			encontrou = true;
		}
		else{
			while ((*auxiliar)->next != nullptr) {
				if ((*auxiliar)->name == a.name && (*auxiliar)->ra == a.ra) {
					// já existe
					encontrou = true;
					break;
				}
				else {
					auxiliar = &(*auxiliar)->next;
				}
			}

			if (!encontrou) {
				if ((*auxiliar)->name == "empty") {
					(*auxiliar)->name = a.name;
					(*auxiliar)->ra = a.ra;
				}
				else
					(*auxiliar)->next = &a;
			}
		}
	}
}

int HashTable::NumberOfItems(int index)
{
	item** auxiliar = &hashTable[index];
	int count = 0;
	if ((*auxiliar)->name == "empty") {
		return count;
	}
	else {
		count++;

		for (count = count; (*auxiliar)->next != nullptr; count++) { // AQUI Q É O PROBLEMA
			auxiliar = &(*auxiliar)->next;
		}

		return count;
	}
}

void HashTable::PrintTable()
{
	int number;
	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		cout << "-------------------" << endl;
		cout << "index = " << i << endl;
		cout << "# of items = " << number << endl;
		cout << "-------------------" << endl;
		for (int j = 0; j < number; j++) {
			cout << "-------------------" << endl;
			cout << "ra = " << hashTable[i]->ra << endl;
			cout << "name = " << hashTable[i]->name << endl;
		}
	}
}

HashTable::~HashTable()
{
}

int HashTable::Hash(std::string key) {
	int hash = 0, index;

	for (int i = 0; i < key.length(); i++)
	{
		hash += (int)key[i];
		//cout << "hash = " << hash << endl;
	}

	index = hash % tableSize;
	/* we divide the hashCode for the tableSize and the reminder is the index*/

	return index;
}