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

void wyswietlCmd(plansza_podstawa p) {
    setlocale(LC_ALL, "en_US.UTF-8");

    const wchar_t* wc = SQUARE_BLACK;
    int avoid = 0;

    for(int i = 0; i <= 2*(p->liczba_wierszy); i++)
    {
        if(i%2==0)
        {
            avoid = 0;
        }
        else{
            avoid = 1;
        }
        wprintf(L"\n");
        for(int j = 0; j<= 2*(p->liczba_kolumn); j++)
        {
            if(i==0 && j==0) 
            {
                wc = LINE_DOWN_RIGHT;
                wprintf(L"%ls", wc);
                continue;
            }
            else if (i==0 && j==2*(p->liczba_kolumn))
            {
                wc = LINE_DOWN_LEFT;
                wprintf(L"%ls", wc);
                continue;
            }
            else if (i==2*(p->liczba_wierszy) && j==0)
            {
                wc = LINE_UP_RIGHT;
                wprintf(L"%ls", wc);
                continue;
            }
            else if (i==2*(p->liczba_wierszy) && j==2*(p->liczba_kolumn))
            {
                wc = LINE_UP_LEFT;
                wprintf(L"%ls", wc);
                continue;
            }
            else{
                if(avoid == 0){
                    wc = LINE_HORIZONTAL;
                    wprintf(L"%ls", wc);
                    continue;
                }
                else{
                    if(j%2==0)
                    {
                        wc = LINE_VERTICAL;
                        wprintf(L"%ls", wc);
                        continue;
                    }
                    else
                    {
                        if((p->AntY == (i-1)/2) && (p->AntX == (j-1)/2))
                        {
                            if(p->template[(i-1)/2][(j-1)/2] == 0)
                            {
                                wc = arrowsBlack[p->antDirection];
                                wprintf(L"%ls", wc);
                            }
                            else{
                                wc = arrowsWhite[p->antDirection];
                                wprintf(L"%ls", wc);
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
                        
                        wprintf(L"%ls", wc);
                        continue;
                    }
                }
            }

            
            
            
        }
    }


}