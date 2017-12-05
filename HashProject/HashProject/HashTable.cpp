#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
#include <string>
using std::list;
using std::cout;
using std::endl;
using std::string;


HashTable::HashTable()
{
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->name = "empty";
		hashTable[i]->ra = 0;
		hashTable[i]->next = nullptr;
	}
}

void HashTable::AddItem(int ra, string name) {
	int index = Hash(ra);
	bool encontrou = false;
	item** auxiliar = &hashTable[index];

	if (hashTable[index]->ra != 0) {
		if (TotalOfPositionsUsed() >= 0.6 * tableSize)
			tableSize += 0.5*tableSize;
	}

	if ((*auxiliar) == nullptr) {
		(*(*auxiliar)) = *new item();
		(*(*auxiliar)).name = name;
		(*(*auxiliar)).ra = ra;
		(*(*auxiliar)).next = nullptr;
	}
	else {
		if ((*auxiliar)->ra == ra) {
			encontrou = true;
		} else {
			while ((*auxiliar)->next != nullptr) {
				auxiliar = &(*auxiliar)->next;
			}
		}
			
		if (!encontrou) {
			if ((*(*auxiliar)).name == "empty") {
				(*(*auxiliar)).name = name;
				(*(*auxiliar)).ra = ra;
			}
			else {
				(*(*auxiliar)).next = new item();
				(*(*auxiliar)).next->name = name;
				(*(*auxiliar)).next->ra = ra;
				(*(*auxiliar)).next->next = nullptr;
			}

			cout << "Item incluído com sucesso!\n" << endl;
		}

		if (encontrou) {
			cout << "Esse elemento já existe!\n" << endl;
		}
	}
}

void HashTable::DeleteItem(int ra)
{
	int number;
	item** aux;
	bool encontrou = false;

	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		aux = &hashTable[i];
		if ((*aux)->ra == ra) {
			if ((*(*aux)).next == nullptr) {
				(*(*aux)).name = "empty";
				(*(*aux)).ra = 0;
			}
			else
				(*aux) = (*(*aux)).next;
			cout << "Item excluído com sucesso!\n" << endl;
			encontrou = true;
		}
		else {
			for (int j = 0; j < number; j++) {
				if ((*aux)->next != nullptr) {
					if ((*aux)->next->ra == ra) {
						//encontrou
						(*(*aux)).next = (*(*aux)).next->next;

						cout << "Item excluído com sucesso!\n" << endl;
						encontrou = true;
					}
					else {
						aux = &(*aux)->next;
					}
				}

				if (encontrou) {
					break;
				}
			}
		}
	}
}

HashTable::item* HashTable::Search(int ra)
{
	int number;
	item* aux;
	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		aux = hashTable[i];
		for (int j = 0; j < number; j++) {
			if (aux->ra == ra) {
				//encontrou
				return aux;
			}
			else {
				aux = aux->next;
			}
		}
	}
}

HashTable::item* HashTable::Search(string name)
{
	int number;
	item* aux;
	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		aux = hashTable[i];
		for (int j = 0; j < number; j++) {
			if (aux->name == name) {
				//encontrou
				return aux;
			}
			else {
				aux = aux->next;
			}
		}
	}
}

int HashTable::NumberOfItems(int index)
{
	item** auxiliar = &hashTable[index];
	int count = 0;
	if ((*auxiliar) != nullptr) {
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
	else {
		return 0;
	}
}

void HashTable::PrintTable()
{
	int number;
	item* aux;

	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		cout << "-------------------" << endl;
		cout << "index = " << i << endl;
		cout << "# of items = " << number << endl;
		cout << "-------------------" << endl;

		aux = hashTable[i];
		for (int j = 0; j < number; j++) {
			cout << "ra = " << aux->ra << endl;
			cout << "name = " << aux->name << endl;
			cout << "-------------------" << endl;
			aux = aux->next;
		}
	}
	cout << "\n" << endl;
}

int HashTable::TotalOfPositionsUsed()
{
	int count = 0;
	for (int i = 0; i < tableSize; i++) {
		if (hashTable[i] != nullptr) {
			if (hashTable[i]->ra != 0)
				count++;
		}
	}
	
	return count;
}

HashTable::~HashTable()
{
}

int HashTable::Hash(int key) {
	int hash = 0, index;

	/*for (int i = 0; i < key.length(); i++)
	{
		hash += (int)key[i];
		//cout << "hash = " << hash << endl;
	}*/

	index = key % tableSize;
	/* we divide the hashCode for the tableSize and the reminder is the index*/

	return index;
}