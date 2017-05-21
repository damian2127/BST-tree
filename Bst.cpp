#include "Bst.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//==============================================================================================================================
void InOrder( TreeItem* pRoot )
{
	if ( pRoot )
	{
		InOrder( pRoot->left );
		wprintf(L"%s", pRoot->name);
		printf("\n");
		InOrder( pRoot->right );
	}
}

//===============================================================================================================================
void WriteInOrder( FILE* file, TreeItem* pRoot )
{
	if ( pRoot )
	{
		WriteInOrder( file, pRoot->left );

		fwprintf(file, L"%s:  ", pRoot->name);
		int i = 1;

		do
		{
			pRoot->pList = pRoot->pList->pNext;
			fwprintf(file, L" Linia %d:%d razy |", pRoot->pList->line, pRoot->pList->lineNum);

		} while ( pRoot->pList->pNext );

		fprintf(file, "Ogolnie %d razy  ", pRoot->countAllText);

		fprintf(file, "\n");

		WriteInOrder( file, pRoot->right );
	}

}
//==================================================================================================================================

TreeItem* ReadFile ( FILE* file, TreeItem* pRoot )
{

	int line_nr = 1;           // ustawiam numer na linii na 1

	wchar_t buffor[25] = { 0 };// tab przechowujaca slowo
	int i = 0;                 // licznik do liczby znakow

	while ( !feof(file) )      // dopoki nie dojechalem do konca pliku
	{
		wchar_t z = fgetwc( file );// pobieram znak
		
		if ( !i && FirstSign(z) ) // jesli jest to pierwszy znak czyli i=0 oraz spelnia warunek bycia pierwszym znakiem
		{
			buffor[i] = z;
			i++;
		}
		else if ( i && nextGoodSign(z) ) // jesli jest to drugi i kolejny znak i jest dobry( a-zA-Z _0-9 )
		{
			buffor[i] = z;
			i++;
		}
		else
		{
			if ( i != 0) // jesli wczytalem cale slowo, bo znak ktory wczytalem teraz nie nadaje sie do zadnego if'a
			{                     // znajdz i wstaw buffor do drzewa
				pRoot = FindandInsert( buffor, pRoot, line_nr );  // przekazuje slowo, pRoot'a i numer linii w ktorej jest dane slowo
				memset(buffor, 0, 25);          // zeruje bufor przechowujacy slowo
				i = 0;                          // zeruje licznik liczby znakow
			}
		}
		if ( z == '\n' ) line_nr++;  // zwieksz numer linii
	}


	fclose( file );

	return pRoot;
}

//=======================================================================================================================================
TreeItem* FindandInsert( wchar_t* buffor, TreeItem* pRoot, UINT line_nr ) // przekazuje nr linii w ktorej jest dane slowo z buffor
{
	// sprawdzamy czy 'mniejsze' (lewo) czy 'wiÍksze' (prawo) czy rÛwne (lista++)	

	if ( !pRoot )  // jeúli pRoot = NULL
	{
		pRoot = ( TreeItem* )calloc(1, sizeof(TreeItem) ); // alokuj pamiec na element drzewa
		wcsncpy( pRoot->name, buffor, 25 );  // przekopiuj slowo do wezla
		pRoot->countAllText = 1;             // w tym momencie ilosc wystapien slowa w calym tekscie = 1
		pRoot->left = pRoot->right = NULL;
		
		if( &pRoot->pList )
		{
			LInit( &pRoot->pList ); // zainicjuj liste
		}

		LAddFront(&pRoot->pList, line_nr)->lineNum=1; // dodaj na poczatek listy

		return pRoot;
	}

	if ( CompareStrings(buffor, pRoot->name) == 1 )  // czyli buffor > pRoot->name
	{
		pRoot->right = FindandInsert( buffor, pRoot->right, line_nr ); // i wchodze w prawe poddrzewo
	}
	else if ( CompareStrings(buffor, pRoot->name) == -1 ) //czyli buffor < pRoot->name
	{
		pRoot->left = FindandInsert( buffor, pRoot->left, line_nr ); // i wchodze w lewe poddrzewo
	}
	else if ( CompareStrings(buffor,pRoot->name) == 0 ) // czyli to sa te same slowa
	{                                      
		Visit( pRoot, line_nr );                       // odwiedzamy wezel
	}
	
	return pRoot;
}

//===================================================================================================================================
void Visit( TreeItem *pRoot, UINT nLine )
{
	ListItem *temp = NULL;                     // tworze element listy
	temp = LFind( pRoot->pList, &temp, nLine );// jak przegladam szukajac nline=2 to w temp bede mial wsk na ostatni element wsk na cos z linijki 1
	
	pRoot->countAllText++;                     // skoro odwiedzilem wezel to slowo zwiekszylo ilosc swych wystapien w calym tekscie

	if( !temp || nLine != temp->pNext->line ) // jesli temp == NULL lub przekazany nLine != line
	{
		LAddFront(&pRoot->pList, nLine)->lineNum = 1;	
	}
	else
	{
		temp->pNext->lineNum++;              // to oznacza, ze w tej linii slowo wystapilo po raz kolejny
	}
}

//===================================================================================================================================

int CompareStrings( wchar_t* ptr1, wchar_t* ptr2 )
{
	wchar_t* str1 = (wchar_t*)calloc(1, wcslen(ptr1) + 1);
	wchar_t* str2 = (wchar_t*)calloc(1, wcslen(ptr2) + 1);

	wcscpy(str1, ptr1);
	wcscpy(str2, ptr2);
	_wcslwr(str1);
	_wcslwr(str2);

	int result = wcscmp(str1, str2);

	return result;

	free(str1);
	free(str2);

	/*do
    {
        if ( *str1 > *str2 )
            return 1;

        if ( *str1 < *str2 )
            return -1;
       
        return 0;
 
    } while ( *str1++ && *str2++ );*/
}

//=======================================================================================================================================
int FirstSign( wchar_t c )
{
	return ( (c == '_' || (c <= 'Z' && c >= 'A')) || (c <= 'z' && c >= 'a') || isPolish(c) );
}

//=====================================================================================================================================
int nextGoodSign( wchar_t c )
{
	return ( (c == '_' || (c <= 'Z' && c >= 'A')) || (c <= 'z' && c >= 'a') || (c <= '9' && c >= '0') || isPolish(c));
}

//=====================================================================================================================================
int isPolish(wchar_t c)
{
	switch(c)
	{
	case L'π':
	case L'Ê':
	case L'Í':
	case L'≥':
	case L'Ò':
	case L'Û':
	case L'ú':
	case L'ø':
	case L'ü':
	case L'•':
	case L'∆':
	case L' ':
	case L'£':
	case L'—':
	case L'”':
	case L'å':
	case L'Ø':
	case L'è': return 1;
	}
	return 0;
}

//============================================================================================================================