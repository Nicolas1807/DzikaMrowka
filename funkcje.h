#ifndef F_H

#define F_H

//Struktura Dla Mrówiszona template to mapa zer i jedynek gdzie białe a gdzie czarne pole (reszta zrozumiała)
typedef struct plansza_podstawa{
    int**template;
    int liczba_kolumn;
    int liczba_wierszy;
    int antDirection;
    int AntX;
    int AntY;
    int ile_iteracji;

}*plansza_podstawa;


plansza_podstawa zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy, int iteracje);

int narysuj_plansze(plansza_podstawa p);

void zwolnij_plansze(plansza_podstawa p);

void wyswietlCmd(plansza_podstawa p);


#endif