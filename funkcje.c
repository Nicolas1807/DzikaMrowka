#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <direct.h>
#include "funkcje.h"
#define WGORE 0 
#define WPRAWO 1 
#define WDOL 2 
#define WLEWO 3

#pragma comment(lib, "gdi32.lib")

//To musi być globalne bo klasa WndProc nie przyjmuje parametrow
int cellSize = 10;
int playerX, playerY;
int iteracja = 0;
plansza_podstawa p;

plansza_podstawa zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy, int iteracje, int tryb, char* nazwaFolderu, int direction, int getRandomMap, FILE *in){
     
     p =  malloc(sizeof(*p));
     srand(time(NULL));
     int randomNum;
     if(p==NULL){
        fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
        return NULL;
     }
     p->template = (int**)malloc(liczba_wierszy *sizeof(int*));
     if(p->template==NULL){
        fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
        return NULL;
     }

    // if(in != NULL)
    // {
    //     int** templateInput = (int**)malloc(liczba_wierszy *sizeof(int*));
    //     if(templateInput==NULL){
    //         fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
    //         return NULL;
    //     }
    //     char pomocniczy;
    //     int wiersze = 0;
    //     int kolumny = 0;
    //     while ((pomocniczy = fgetc(in)) != EOF) 
    //     {
    //         templateInput[wiersze][kolumny] = pomocniczy;
    //         kolumny++;
    //         if(kolumny>=p->liczba_kolumn)
    //         {
    //             wiersze++;
    //             kolumny = 0;
    //         }
    //         if(wiersze>=p->liczba_wierszy)
    //         {
    //             printf("Błąd w chuj");
    //             return NULL;
    //         }
    //     }
    // }

    


     for(int i = 0; i< liczba_wierszy;i++){
        p->template[i] = (int*)malloc(liczba_kolumn * sizeof(int));
        if(p->template[i] == NULL){
            fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci kolumn\n");
            return NULL;
        }
        for(int j = 0; j<liczba_kolumn; j++)
        {
            //TU MOZNA DAWAC MRUWIE PRZESZKODY PRZY GENEROWANIU MAPY (COOOOOO? NO WAY)

            randomNum = rand()%100;     
            if(randomNum < getRandomMap)
            {
                p->template[i][j] = 1;
            }
            else{
                p->template[i][j] = 0;
            }
        }
     }
     p->files = (FILE**)malloc(iteracje * sizeof(*p->files));
     p->liczba_kolumn = liczba_kolumn;
     p->liczba_wierszy = liczba_wierszy;
     p->antDirection = 0;
     p->ile_iteracji=iteracje;
     p->NazwaFolderu = nazwaFolderu;
     p->antDirection = direction;
     p->tryb = tryb;
     printf("%s", p->NazwaFolderu);
     // to potem pojdzie do funkcji rozpoczynajacej animacje ruchow mrowy
     return p;
}
void ruch_w_prawo(){
    p->antDirection++;
    if(p->antDirection>WLEWO){
        p->antDirection = WGORE;
    }
}
void ruch_w_lewo(){
    p->antDirection--;
    if(p->antDirection<WGORE){
        p->antDirection = WLEWO;
    }
}
void ruszDoPrzodu(){

    if(p->antDirection == 0)
    {
        p->AntY -= 1;
    }
    else if(p->antDirection == 1)
    {
        p->AntX += 1;
    }
    else if(p->antDirection == 2)
    {
        p->AntY += 1;
    }
    else if(p->antDirection == 3)
    {
        p->AntX -= 1;   
    }
    else{
        printf("Blaaadd");
    }
}
void wykonajRuch(){
    
    

    
    iteracja++;
    
    // printf("%d", p->antDirection);
    
    if (p->template[p->AntY][p->AntX]==0){
        ruch_w_prawo();
        p->template[p->AntY][p->AntX] = 1;
    }
    else if (p->template[p->AntY][p->AntX]==1){
        ruch_w_lewo();
        p->template[p->AntY][p->AntX] = 0;
        
        
    }
    
    ruszDoPrzodu();

}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    // Do nothing in this example
    if(iteracja < p->ile_iteracji)
    {
        if((p->AntX < 0) || (p->AntY < 0) || (p->AntX > p->liczba_kolumn-1) || (p->AntX>p->liczba_wierszy-1))
        {
                printf("Mrowiszon wyjebal za mape");
                PostMessage(hwnd, WM_DESTROY, 0, 0);
        }
        else
        {
            wyswietlCmd(p, iteracja);
            wykonajRuch();
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }
        
        
    }
    else{
        PostMessage(hwnd, WM_DESTROY, 0, 0);
    }
}

//Odpala się gdy okno się odświeża i szuka akcji, które się wydarzyły
LRESULT CALLBACK WndProc(HWND h, UINT uMsg, WPARAM wP, LPARAM lP)
{
    
    switch (uMsg)
    {
    //Odpala sie na poczatku (default ustawienie mrówy)
    
    case WM_CREATE:

        p->AntX = round(p->liczba_kolumn/2);
        p->AntY = round(p->liczba_wierszy/2);

        SetTimer(h, 1, 1000, TimerProc);
        break;

    //Odpala sie by narysowac mape przy odswiezeniu (tylko czasem z jakiegoś powodu)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);

        playerX = p->AntX*cellSize;
        playerY = p->AntY*cellSize;

        for (int y = 0; y < p->liczba_wierszy; y++)
        {
            for (int x = 0; x < p->liczba_kolumn; x++)
            {
                if (p->template[y][x] == 0) {
                    // Black rectangle
                    Rectangle(hdc, x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize);
                }
                else {
                    // White rectangle
                    HBRUSH whiteBrush = CreateSolidBrush(RGB(0, 0, 0));
                    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);
                    Rectangle(hdc, x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize);
                    SelectObject(hdc, oldBrush);
                    DeleteObject(whiteBrush);
}
            }
        }

        // Rysowanie Mrówy
        HBRUSH blueBrush = CreateSolidBrush(RGB(100, 0, 0)); 
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
        Rectangle(hdc, playerX, playerY, playerX + cellSize, playerY + cellSize);
        SelectObject(hdc, oldBrush);
        DeleteObject(blueBrush);
        EndPaint(h, &ps);
        break;
    }
    case WM_TIMER:
        // Handle timer events (1-second delay)    
        InvalidateRect(h, NULL, TRUE);
        
        break;
    case WM_DESTROY:

    {
        KillTimer(h, 1);
        PostQuitMessage(0);
        return 0;
    }
    case WM_KEYDOWN:
        switch (wP)
        {
        case VK_SPACE:
            wykonajRuch();
        }
        InvalidateRect(h, NULL, TRUE);
        break;
    default:
        return DefWindowProc(h, uMsg, wP, lP);
    }

    return 0;
}

int narysuj_plansze(plansza_podstawa p){

    if (_mkdir(p->NazwaFolderu) == 0) {
        printf("Directory created successfully.\n");
    } 
    else {
        perror("Error creating directory");
        return 1;
    }

    if(p->tryb == 0)
    {
        WNDCLASSEX wc;
        MSG ms;
        HWND h;


        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = wc.cbWndExtra = 0;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = "MyClassName";  
        wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);

        if (!RegisterClassEx(&wc))
            return 0;

        

        h = CreateWindowEx(0, "MyClassName", "Mruwa", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,  p->liczba_kolumn*cellSize+20,p->liczba_wierszy*cellSize+40, 0, 0, GetModuleHandle(NULL), 0);

        if (!h)
            return 0;


        ShowWindow(h, SW_SHOWNORMAL);
        UpdateWindow(h);

    
        while (GetMessage(&ms, NULL, 0, 0))
        {
            TranslateMessage(&ms);
            DispatchMessage(&ms);
        }
    }
    else if(p->tryb==1)
    {
        p->AntX = round(p->liczba_kolumn/2);
        p->AntY = round(p->liczba_wierszy/2);

        for(int i = 0; i<p->ile_iteracji; i++)
        {
            if((p->AntX < 0) || (p->AntY < 0) || (p->AntX > p->liczba_kolumn-1) || (p->AntX>p->liczba_wierszy-1))
            {
                printf("Mrowiszon wyjebal za mape");
                return 1;
            }
            else{
                wyswietlCmd(p, i);
                wykonajRuch();
                Sleep(1000);
            }
        }
    }

}



void zwolnij_plansze(plansza_podstawa p){
    for(int i=0; i<p->liczba_wierszy;i++){
        free(p->template[i]);
    }
    for(int j=0;j<p->ile_iteracji; j++)
    {
        free(p->files[j]);
    }
    free(p->template);
    free(p);
}