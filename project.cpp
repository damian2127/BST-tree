#include "Bst.h"
#include "List.h"
#include <cstdlib>
#include <iostream>


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");  // kodowanie polskich znakow

	//==============================
	FILE *plik;
	plik = fopen("Dane.txt", "r");
	
	if ( !plik )
	{
		printf("I can't open the file!\n");
		return 0;
	}

	//================================
	FILE* wynikowy;
	wynikowy = fopen("Wynik.txt", "w");
	if ( !wynikowy )
	{
		printf("I can't open the file!\n");
		return 0;
	}

	//================================
	TreeItem* pRoot = NULL;

	pRoot = ReadFile(plik, pRoot);
	InOrder( pRoot );
	WriteInOrder( wynikowy, pRoot );
	
	//usun metoda preorder

	//===============================
	return 0;
}

