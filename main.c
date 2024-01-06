#include <stdio.h>
#include <stdlib.h>

//kierunki moga byc jak wskazowki zegara tzn zmieniamy kierunek odejmujac badz dodajac okreslona liczbe
#define WGORE 0 
#define WDOL 2 
#define WPRAWO 1 
#define WLEWO 3

int **plansza;
int poz_x;
int poz_y;
int kierunek_mrowki;


// nie wiem kurwa jak to ma rysowac to gowno, po prostu printowac czy jest jakas powloka graficzna?
int** zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy){
     plansza = (int**)malloc(liczba_wierszy *sizeof(int*));
     if(plansza==NULL){
        fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
        return -1;
     }
     for(int i = 0; i< liczba_wierszy;i++){
        plansza[i] = (int*)malloc(liczba_kolumn * sizeof(int));
        if(plansza[i] == NULL){
            fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci kolumn\n");
            return -2;
        }
     }
     // to potem pojdzie do funkcji rozpoczynajacej animacje ruchow mrowy
     poz_x = liczba_kolumn/2;
     poz_y = liczba_wierszy/2;
     kierunek_mrowki = WGORE;

     return plansza;
}
void zwolnij_plansze(int **plansza, int liczba_wierszy){
    for(int i=0; i<liczba_wierszy;i++){
        free(plansza[i]);
    }
    free(plansza);
}

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
