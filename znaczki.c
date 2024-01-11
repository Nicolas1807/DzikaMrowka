#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include "funkcje.h"
#define LINE_VERTICAL L"│"
#define LINE_HORIZONTAL L"─"
#define LINE_DOWN_RIGHT L"┌"
#define LINE_DOWN_LEFT L"┐"
#define LINE_UP_RIGHT L"└"
#define LINE_UP_LEFT L"┘"
#define SQUARE_WHITE L" "
#define SQUARE_BLACK L"█"


const wchar_t* arrowsBlack[] = {L"▲", L"▶", L"▼", L"◀"};
const wchar_t* arrowsWhite[] = {L"△", L"▷", L"▽", L"◁"};
char tmpname[1024];

void WypiszZapisz(FILE* f, int tryb, const wchar_t* wc)
{
    if(tryb == 0)
    {
        fwprintf(f, L"%ls", wc);
    }
    if(tryb == 1)
    {
        wprintf(L"%ls", wc);
        fwprintf(f, L"%ls", wc);
    }
}

void wyswietlCmd(plansza_podstawa p, int iteracja) {
    setlocale(LC_ALL, "en_US.UTF-8");

    const wchar_t* wc = SQUARE_BLACK;
    int avoid = 0;
    
   
    sprintf(tmpname, "%s\\file_%d.txt", p->NazwaFolderu, iteracja);
    FILE *f = fopen(tmpname, "w");
    

    for(int i = 0; i <= 2*(p->liczba_wierszy); i++)
    {
        if(i%2==0)
        {
            avoid = 0;
        }
        else{
            avoid = 1;
        }
        WypiszZapisz(f, p->tryb, L"\n");
        for(int j = 0; j<= 2*(p->liczba_kolumn); j++)
        {
            if(i==0 && j==0) 
            {
                wc = LINE_DOWN_RIGHT;
                WypiszZapisz(f, p->tryb, wc);
                continue;
            }
            else if (i==0 && j==2*(p->liczba_kolumn))
            {
                wc = LINE_DOWN_LEFT;
                WypiszZapisz(f, p->tryb, wc);
                
                continue;
            }
            else if (i==2*(p->liczba_wierszy) && j==0)
            {
                wc = LINE_UP_RIGHT;
                WypiszZapisz(f, p->tryb, wc);

                continue;
            }
            else if (i==2*(p->liczba_wierszy) && j==2*(p->liczba_kolumn))
            {
                wc = LINE_UP_LEFT;
                WypiszZapisz(f, p->tryb, wc);

                continue;
            }
            else{
                if(avoid == 0){
                    wc = LINE_HORIZONTAL;
                    WypiszZapisz(f, p->tryb, wc);

                    continue;
                }
                else{
                    if(j%2==0)
                    {
                        wc = LINE_VERTICAL;
                        WypiszZapisz(f, p->tryb, wc);

                        continue;
                    }
                    else
                    {
                        if((p->AntY == (i-1)/2) && (p->AntX == (j-1)/2))
                        {
                            if(p->template[(i-1)/2][(j-1)/2] == 1)
                            {
                                wc = arrowsBlack[p->antDirection];
                                WypiszZapisz(f, p->tryb, wc);

                            }
                            else{
                                wc = arrowsWhite[p->antDirection];
                                WypiszZapisz(f, p->tryb, wc);

                            }
                            continue;
                        }
                        else if(p->template[(i-1)/2][(j-1)/2] == 0)
                        {
                            wc = SQUARE_WHITE;
                        }
                        else
                        {
                            wc = SQUARE_BLACK;
                        }
                        
                        WypiszZapisz(f, p->tryb, wc);

                        continue;
                    }
                }
            }

            
            
            
        }
    }

    
    p->files[iteracja] = f;
    fclose(f);

}