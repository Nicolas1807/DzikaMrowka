#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <math.h>
#include <ctype.h>
#include <unistd.h>



int main(int argc, char **argv){
    char *wvalue = NULL;
    char *kvalue = NULL;
    char *ivalue = NULL;
    char *dvalue = NULL;
    char *rvalue = NULL;
    char *trybvalue = NULL;
    int index;
    int c;
    opterr = 0;
    int getRandomMap = 0;
    int m = 10;
    int n = 20;
    int direction = 0;
    int it = 10;
    int tryb = 0;
    char *folder = NULL; // Initialize to NULL
    char *plik = NULL; 

    while ((c = getopt(argc, argv, "w:k:i:m:f:d:r:p:")) != -1) {
        switch (c) {
            case 'd':      //DIRECTION
                dvalue = optarg;
                direction = atoi(dvalue);
                if((direction<0) || (direction>3))
                {
                    printf("Nalezy podac liczbe od 1 do 3");
                    return 1;
                }
                break;
            case 'r':      //RANDOMIZE MAP
                rvalue = optarg;
                getRandomMap = atoi(rvalue);
                 if ((getRandomMap < 0) || (getRandomMap > 100)) {
                        fprintf(stderr, "Program posiada tylko 2 tryby: 1 - wygeneruj lososwo mape, 0 - Pusta Mapa%d.\n");
                        return 1;
                    }
                break;
            case 'w': //WIERSZE
                wvalue = optarg;
                m = atoi(wvalue);
                break;
            case 'k': //KOLUMNY
                kvalue = optarg;
                n = atoi(kvalue);
                break;
            case 'i': //ITERATIONS
                ivalue = optarg;
                it = atoi(ivalue);
                break;
            case 'm': //MODE
                if (optarg == NULL) {
                    tryb = 1; // Set the default value if no argument provided
                } else {
                    trybvalue = optarg;
                    tryb = atoi(trybvalue);
                    if (tryb != 0 && tryb != 1) {
                        fprintf(stderr, "Program posiada tylko 2 tryby: 0 - wypisanie do okna, 1 - na standardowe wyjscie.\n");
                        return 1;
                    }
                }
                break;
            case 'f': //FOLDER
                folder = optarg;
                break;
            case 'p': //PLIK
                plik = optarg;
                break;
            case '?': // POMOC
                if (optopt == 'i' || optopt == 'w' || optopt == 'k' || optopt == 'm' || optopt == 'f' || optopt == 'd'|| optopt == 'p'|| optopt == 'r') {
                    fprintf(stderr, "Opcja/e -%c wymaga argumentu\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Nieznana opcja '-%c'\n", optopt);
                    printf("Dostepne flagi:\n-w (liczba wierszy), \n-k (liczba kolumn), \n-i (liczba iteracji mrowki), \n-m (tryb wyswietlania iteracji w oknie 0 lub w konsoli 1), \n-f (nazwa folderu do zapisu iteracji)");
                    printf("\n-d (kierunek poczatkowy mrówki 0-3), \n-p (plik, w którym podać można przeszkody), \n-r (od 0 do 100 jak bardzo mapa ma byc pokryta w czarnych polach)\n");
               
                } else {
                    fprintf(stderr, "Nieznana opcja znaków '\\x%x'\n", optopt);
                }
                return 1;
            default:
                abort();
        }
    }

    for(index = optind; index< argc; index++){
        printf("Nie ma takiego argumentu %s\n",argv[index]);
    }

    FILE*inputf = fopen(plik, "r");
    

    plansza_podstawa p = zainicjuj_plansze(n,m,it,tryb,folder, direction, getRandomMap, inputf);

    
    if(p == NULL)
    {
        printf("Nie udalo sie przydzielic pamieci dla planszy %d x %d", m, n); 
        return 1;
    }
   
    narysuj_plansze(p);
    zwolnij_plansze(p);
    fclose(inputf);

    return 0;
}