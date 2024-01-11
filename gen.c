#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <math.h>






int main(int argc, char **argv){

    FILE*f = argc>1?fopen(argv[1], "w"):stdout;

    for(int i = 0; i < 40; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            if(((j>5)&&(j<15))||((j>25)&&(j<35)))
            {
                fprintf(f, "1");
            }
            else{
                fprintf(f, "0");
            }
        }
    }
    fclose(f);

    return 0;
}