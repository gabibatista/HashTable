#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
#include <string>
using std::list;
using std::cout;
using std::endl;
using std::string;
using std::to_string;


HashTable::HashTable()
{
	threshold = 0.75f;
	maxSize = 96;
	tableSize = 5;
	size = 0;
	hashTable = new item*[tableSize];

	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->name = "empty";
		hashTable[i]->ra = 0;
		hashTable[i]->next = nullptr;
	}
}

void HashTable::AddItem(int ra, string name) {
	if (ra < 0) {
		cout << "RA inválido!\n" << endl;
		return;
	}

	if (TotalOfPositionsUsed() + 1 >= 0.5 * tableSize)
		resize();

	int index = Hash(to_string(ra));
	bool encontrou = false;
	item** auxiliar = &hashTable[index];

	//if (hashTable[index]->ra != 0) {
		//if (TotalOfPositionsUsed() >= 0.6 * tableSize)
			//tableSize += 0.5*tableSize;
	//}

	/* for resizing: http://www.algolist.net/Data_structures/Hash_table/Dynamic_resizing */

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

//			cout << "Item incluído com sucesso!\n" << endl;
		}

		if (encontrou) {
			//cout << "Esse elemento já existe!\n" << endl;
		}
	}
}

void HashTable::DeleteItem(int ra)
{
	int number;
	item** aux;
	bool encontrou = false;

	if (ra < 0) {
		cout << "RA inválido!\n" << endl;
		return;
	}

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
			//cout << "Item excluído com sucesso!\n" << endl;
			encontrou = true;
		}
		else {
			for (int j = 0; j < number; j++) {
				if ((*aux)->next != nullptr) {
					if ((*aux)->next->ra == ra) {
						//encontrou
						(*(*aux)).next = (*(*aux)).next->next;

						//cout << "Item excluído com sucesso!\n" << endl;
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

	if (!encontrou) {
//		cout << "Esse item não existe!\n" << endl;
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

bool HashTable::Exist(int ra)
{
	int number;
	item* aux;
	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		aux = hashTable[i];
		for (int j = 0; j < number; j++) {
			if (aux->ra == ra) {
				//encontrou
				return true;
			}
			else {
				aux = aux->next;
			}
		}
	}

	return false;
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

void HashTable::resize(){
	int oldTableSize = tableSize;
	tableSize = std::round(tableSize*1.5);
	maxSize = (int)(tableSize * threshold);
	item** oldTable = new item*[oldTableSize];
	
	for (int j = 0; j < oldTableSize; j++) {
		oldTable[j] = hashTable[j];
	}

	hashTable = new item*[tableSize];
	
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new item;
		hashTable[i]->name = "empty";
		hashTable[i]->ra = 0;
		hashTable[i]->next = nullptr;
	}

	size = 0;

	for (int h = 0; h < oldTableSize; h++)
		if (oldTable[h] != nullptr) {
			item *oldEntry;
			item *entry = oldTable[h];
			while (entry != nullptr && entry->ra != 0) {
				AddItem(entry->ra, entry->name);
				oldEntry = entry;
				entry = entry->next;
				delete oldEntry;
			}
		}

	delete[] oldTable;
}

HashTable::~HashTable()
{
}

int HashTable::getSize()
{
	return tableSize;
}

int HashTable::Hash(string key) {
	int hash = 0, index;

	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + (int)key[i]) * 17;
		//cout << "hash = " << hash << endl;
	}

	index = hash % tableSize;
	/* we divide the hashCode for the tableSize and the reminder is the index*/

	return index;
}