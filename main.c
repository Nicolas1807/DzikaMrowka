#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <math.h>
#include <ctype.h>
#include <unistd.h>

//kierunki moga byc jak wskazowki zegara tzn zmieniamy kierunek odejmujac badz dodajac okreslona liczbe




int main(int argc, char **argv){
    char *wvalue = NULL;
    char *kvalue = NULL;
    char *ivalue = NULL;
    int index;
    int c;
    opterr = 0;
    int m = 10;
    int n = 20;
    int it = 10;
    while((c = getopt (argc, argv, "w:k:i:")) != -1){
        switch (c)
        {
        case 'w':
            wvalue = optarg;
            m = atoi(wvalue);
            break;
        case 'k':
            kvalue = optarg;
            n = atoi(kvalue);
            break;
        case 'i':
            ivalue = optarg;
            it = atoi(ivalue);
            break;
        case '?':
            if(optopt == 'i' || optopt == 'w' || optopt == 'k'){
                fprintf(stderr,"Opcja/e -%c wymaga argumentu\n",optopt);
            }
            else if(isprint(optopt)){
                fprintf(stderr,"Nieznana opcja '-%c'\n",optopt);
            }
            else{
                fprintf(stderr,"Nieznana opcja znaków '\\x%x \n'",optopt);
            }
            return 1;
            break;
        default:
            abort();
        }
    }
    //printf("aflag = %d , bflag = %d , cvalue = %s\n", aflag, bflag, cvalue);

    for(index = optind; index< argc; index++){
        printf("Non-option argument %s\n",argv[index]);
    }

    plansza_podstawa p = zainicjuj_plansze(n,m,it);

    
    if(p == NULL)
    {
        printf("Nie udalo sie przydzielic pamieci dla planszy %d x %d", m, n); 
    }
    narysuj_plansze(p);
    zwolnij_plansze(p);
    return 0;
}
