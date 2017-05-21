#ifndef BST_H
#define BST_H

#include "List.h"
#include <stdio.h>

#define MAX 25

//============================================================================================
typedef struct TreeItem
{
	wchar_t name[MAX];
	UINT countAllText;  // ilosc wystapien w calym tekscie
	TreeItem* left;
	TreeItem* right;
	List pList;
}TreeElement;

//=============================================================================================

void InOrder( TreeItem* pRoot );                     // wypisanie drzewa na ekran metoda in-order
TreeItem* FindandInsert( wchar_t* buffor, TreeItem* p, UINT line_nr );
TreeItem* ReadFile( FILE* file, TreeItem* pRoot );  // czytam z pliku
void Visit( TreeItem *pRoot, UINT nLine );         // 
void WriteInOrder( FILE* file, TreeItem* pRoot );  // zapisuje do pliku metoda in-order
int CompareStrings( wchar_t* ptr1, wchar_t* ptr2 );// porownuje dwa lancuchy znakow( czy sa takiem same i porownuje pierwsze znaki )
int nextGoodSign( wchar_t z );                     // jesli znak jest a-zA-Z_0-9 zwracam 1
int FirstSign( wchar_t z );                        // jesli znak jest a-zA-Z_ zwracam 1
int isPolish( wchar_t c );                         // jesli znak jest polskim znakiem specjalnym zwracam 1

//============================================================================================

#endif