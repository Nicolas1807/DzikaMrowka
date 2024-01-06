#include <stdio.h>
#include <stdlib.h>
#include <funkcje.h>

//kierunki moga byc jak wskazowki zegara tzn zmieniamy kierunek odejmujac badz dodajac okreslona liczbe
#define WGORE 0 
#define WDOL 2 
#define WPRAWO 1 
#define WLEWO 3

int **plansza;
int poz_x;
int poz_y;
int kierunek_mrowki;

void ruch_w_prawo(){
    kierunek_mrowki++;
    if(kierunek_mrowki>WLEWO){
        kierunek_mrowki = WGORE;
    }
}
void ruch_w_lewo(){
    kierunek_mrowki--;
    if(kierunek_mrowki<WGORE){
        kierunek_mrowki = WLEWO;
    }
}

int main(int argc, char **argv){
    int m = argc > 1 ? atoi(argv[1]): 10;
    int n = argc > 2 ? atoi(argv[2]): 10;
    kierunek_mrowki = argc > 3 ? atoi(argv[3]): WGORE;
    poz_x = n/2;//pozycja mrowki w x 
    poz_y = m/2;//pozycja mrowki w y 

    narysuj_plansze(zainicjuj_plansze(n,m,plansza));//trzeba zrobic funkcje 
    zwolnij_plansze(plansza,m);
}