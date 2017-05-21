#ifndef TYPES_H
#define TYPES_H

#include <windows.h>
#include <stdlib.h>
#include <iostream>

//======================================================================
typedef struct tagListItem
{
	int line;       // zapamietuje numer linii
	int lineNum;;   // zapamietuje ilosc wystapien w linii
	tagListItem* pNext;
}ListItem;

//======================================================================
typedef ListItem* List;

void LInit( List *pList );                             // inicjalizacja listy
ListItem* LAddFront( List* pList, UINT c );            // dodaje element na poczatek listy
ListItem* LAdd( List* pList, ListItem *pElem, UINT b );// dodawanie po wskazanym elemencie
ListItem* LFind( List pList, ListItem **ppNext, UINT c );// zwraca element poprzedni
int LIsEmpty( ListItem* pList );                       // sprawdza czy lista jest pusta

#endif

//=======================================================================