#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <math.h>






int main(int argc, char **argv){

    FILE*f = argc>1?fopen(argv[1], "w"):stdout;

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(((j>=0)&&(j<5))||((j>=15)&&(j<20)))
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