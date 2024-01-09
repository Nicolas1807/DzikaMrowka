#ifndef F_H

#define F_H

//Struktura Dla Mrówiszona template to mapa zer i jedynek gdzie białe a gdzie czarne pole (reszta zrozumiała)
typedef struct plansza_podstawa{
    int**template;
    int liczba_kolumn;
    int liczba_wierszy;
    int antDirection;

}*plansza_podstawa;


plansza_podstawa zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy);

int narysuj_plansze(plansza_podstawa p,int liczba_iteracji);

void zwolnij_plansze(plansza_podstawa p);



#endif