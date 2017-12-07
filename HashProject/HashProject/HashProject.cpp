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
using std::stoi;

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

	if (tabela.Exist(ra))
		cout << "Esse elemento já existe!\n" << endl;
	else {
		cout << "Digite o nome que deseja inserir: ";
		cin >> name;
		cout << "\n";

		tabela.AddItem(ra, name);

		if (tabela.Exist(ra))
			cout << "Item incluído com sucesso!\n" << endl;
	}
}

void excluir() {
	int ra;
	cout << "Digite o RA que deseja excluir: ";
	cin >> ra;
	cout << "\n";

	if (!tabela.Exist(ra))
		cout << "Esse item não existe!\n" << endl;
	else {
		tabela.DeleteItem(ra);
		
		if (!tabela.Exist(ra))
			cout << "Item excluído com sucesso!\n" << endl;
	}
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