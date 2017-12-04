// HashProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

HashTable tabela;

void visualizar() {
	tabela.PrintTable();
}

void inserir() {
	int ra;
	string name;

	cout << "Digite o ra que deseja inserir: ";
	cin >> ra;
	cout << endl;
	cout << "Digite o nome que deseja inserir: ";
	cin >> name;
	cout << "\n";

	tabela.AddItem(ra, name);
}

void excluir() {

}

int main()
{
	int num;

	while (1) {
	menu:
		cout << "0 - Visualizar HashTable " << endl;
		cout << "1 - Inserir na HashTable " << endl;
		cout << "2 - Excluir da HashTable " << endl;
		cin >> num;
		cout << "\n";

		switch (num)
		{
		case 0:
			visualizar();
			break;

		case 1:
			inserir();
			break;

		case 2:
			excluir();
			break;

		default:
			goto menu;
			break;
		}
	}
}