#include <stdio.h>
#include <stdlib.h>

//tu potem dodaje sie implementacje funkcji, trzeba stworzyc tez plik naglowkowy do tego
int** zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy, int** plansza){
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
     return plansza;
}
void zwolnij_plansze(int **plansza, int liczba_wierszy){
    for(int i=0; i<liczba_wierszy;i++){
        free(plansza[i]);
    }
    free(plansza);
}