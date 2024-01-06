#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <math.h>

//kierunki moga byc jak wskazowki zegara tzn zmieniamy kierunek odejmujac badz dodajac okreslona liczbe




int main(int argc, char **argv){
    int m = argc > 1 ? atoi(argv[1]): 10;
    int n = argc > 2 ? atoi(argv[2]): 10;

    plansza_podstawa p = zainicjuj_plansze(n,m);
    
    if(p == NULL)
    {
        printf("Nie udalo sie przydzielic pamieci dla planszy %d x %d", m, n); 
    }
    narysuj_plansze(p);
    zwolnij_plansze(p);
}

