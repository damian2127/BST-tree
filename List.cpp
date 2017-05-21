#include "List.h"
#include <iostream>

using namespace std;

//=====================================================================================
void LInit( List *pList )
{
	ListItem *p = ( ListItem* )malloc( sizeof(ListItem) );

	if ( !p )
	{
		printf("No memory! \n");
		return;
	}
	
	p->line = 0;                          
	p->pNext = NULL;
	*pList = p;
}

//=========================================================================================
int LIsEmpty( ListItem* pList )
{
	return (!pList) || (!pList->pNext);
}

//========================================================================================
ListItem* LAddFront( List* pList, UINT c )
{
	if ( !pList )
	{
		printf("\nNo initialization!\n");
		return NULL;
	}

	return LAdd( pList, *pList, c );
}

//=========================================================================================
ListItem* LAdd( List* pList, ListItem *pElem, UINT b )
{
	if ( !(pList) )
	{
		printf("\nNo initialization of list!\n");
		return NULL;
	}
	else if ( !(pElem) )
	{
		printf("I cant't find it \n");
		return NULL;
	}

	ListItem *p = ( ListItem* )malloc( sizeof(ListItem) ); // tworze nowe pudelko
	
	p->pNext = pElem->pNext;
	p->line = b;
	
	pElem->pNext = p;

	return p;
}

//==========================================================================================
ListItem* LFind( List pList, ListItem **ppNext, UINT c ) // c to numer linii na ktorej sie aktualnie zatrzymalem
{
	if ( LIsEmpty(pList) )
	{
		printf(" List is empty!! \n");
		return NULL;
	}

	*ppNext = pList->pNext;     // element po glowie
	ListItem *pPrev = pList;  // poprzednik

	while ( *ppNext && ((*ppNext)->line != c) ) // dppoki nie dojechalem do konca listy i line != c
	{
		pPrev = *ppNext;                  // poprzedni
		*ppNext = (*ppNext)->pNext;
	}

	if ( !(*ppNext) ) // jesli jest max 1 element w kolejce
	{
		return NULL;
	}

	return pPrev;
}

//=====================================================================================================================