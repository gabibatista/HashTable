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
		if ((*auxiliar)->name == a.name) {
			if ((*auxiliar)->ra != a.ra) {
				(*(*auxiliar)).next = new item();
				(*(*auxiliar)).next->name = name;
				(*(*auxiliar)).next->ra = ra;
				(*(*auxiliar)).next->next = nullptr;
			}
			else {
				// ras iguais >>>>>>> já existe
				encontrou = true;
			}
		}
		else{
			while ((*auxiliar)->next != nullptr) {
				if ((*auxiliar)->name == a.name){
					if ((*auxiliar)->ra != a.ra) {
						(*(*auxiliar)).next = new item();
						(*(*auxiliar)).next->name = name;
						(*(*auxiliar)).next->ra = ra;
						(*(*auxiliar)).next->next = nullptr;
					}
					else {
						// ras iguais >>>>>>> já existe
						encontrou = true;
					}
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

				cout << "Item incluído com sucesso!\n" << endl;
			}
		}

		if (encontrou) {
			cout << "Esse elemento já existe!\n" << endl;
		}
	}
}

void HashTable::DeleteItem(int ra)
{
	int number;
	item* aux;
	/*ESTAVA MEXENDO AQUIIIIIIIIIII*/
	for (int i = 0; i < tableSize; i++) {
		number = NumberOfItems(i);
		aux = hashTable[i];
		if (aux->ra == ra) {
			if (aux->next != nullptr) {
				aux = aux->next;
			}
		}
		else {
			for (int j = 0; j < number; j++) {
				if (aux->next != nullptr) {
					if (aux->next->ra == ra) {
						//encontrou
						aux->next = aux->next->next;
					}
					else {
						aux = aux->next;
					}
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

HashTable::~HashTable()
{
}

int HashTable::Hash(string key) {
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