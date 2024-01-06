#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "funkcje.h"
#define WGORE 0 
#define WPRAWO 1 
#define WDOL 2 
#define WLEWO 3

#pragma comment(lib, "gdi32.lib")

//To musi być globalne bo klasa WndProc nie przyjmuje parametrow
int cellSize = 10;
int playerX, playerY;
plansza_podstawa p;

plansza_podstawa zainicjuj_plansze(int liczba_kolumn, int liczba_wierszy){
     p =  malloc(sizeof(*p));
     if(p==NULL){
        fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
        return NULL;
     }
     p->template = (int**)malloc(liczba_wierszy *sizeof(int*));
     if(p->template==NULL){
        fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci wierszy\n");
        return NULL;
     }
     for(int i = 0; i< liczba_wierszy;i++){
        p->template[i] = (int*)malloc(liczba_kolumn * sizeof(int));
        if(p->template[i] == NULL){
            fprintf(stderr,"Nie udało się utworzyć tablicy, błąd alokacji pamięci kolumn\n");
            return NULL;
        }
        for(int j = 0; j<liczba_kolumn; j++)
        {
            //TU MOZNA DAWAC MRUWIE PRZESZKODY PRZY GENEROWANIU MAPY (COOOOOO? NO WAY)
            p->template[i][j] = 0;
        }
     }
     p->liczba_kolumn = liczba_kolumn;
     p->liczba_wierszy = liczba_wierszy;
     p->antDirection = 0;
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
        playerY -= cellSize;
    }
    else if(p->antDirection == 1)
    {
        playerX += cellSize;
    }
    else if(p->antDirection == 2)
    {
        playerY += cellSize;
    }
    else if(p->antDirection == 3)
    {
        playerX -= cellSize;
    }
    else{
        printf("Blaaadd");
    }
}
void wykonajRuch(){
    int px = playerX/cellSize;
    int py = playerY/cellSize;
    
    
    printf("%d", p->antDirection);
    if (p->template[py][px]==0){
        ruch_w_prawo();
        p->template[py][px] = 1;
    }
    else if (p->template[py][px]==1){
        ruch_w_lewo();
        p->template[py][px] = 0;
        
        
    }
    
    ruszDoPrzodu();

}

//Odpala się gdy okno się odświeża i szuka akcji, które się wydarzyły
LRESULT CALLBACK WndProc(HWND h, UINT uMsg, WPARAM wP, LPARAM lP)
{

    switch (uMsg)
    {
    //Odpala sie na poczatku (default ustawienie mrówy)
    case WM_CREATE:
        playerX = round((p->liczba_kolumn*cellSize)/2);
        playerY = round((p->liczba_wierszy*cellSize)/2);
        break;

    //Odpala sie by narysowac mape przy odswiezeniu (tylko czasem z jakiegoś powodu)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);

        for (int x = 0; x < p->liczba_kolumn; x++)
        {
            for (int y = 0; y < p->liczba_wierszy; y++)
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
        HBRUSH blueBrush = CreateSolidBrush(RGB(40, 40, 100)); 
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
        Rectangle(hdc, playerX, playerY, playerX + cellSize, playerY + cellSize);
        SelectObject(hdc, oldBrush);
        DeleteObject(blueBrush);
        EndPaint(h, &ps);
        break;
    }
    case WM_DESTROY:
    {
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

    h = CreateWindowEx(0, "MyClassName", "Mruwa", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, p->liczba_kolumn*cellSize+20, p->liczba_wierszy*cellSize+40, 0, 0, GetModuleHandle(NULL), 0);

    if (!h)
        return 0;


    ShowWindow(h, SW_SHOWNORMAL);
    UpdateWindow(h);

    //TUTAJ WYWALA BLAD PROGRAM NIE ODPOWIADA
    // for(int z = 0; z<100; z++)
    // {
    //     InvalidateRect(h, NULL, TRUE);
    //     UpdateWindow(h);
        
    // }
    

    while (GetMessage(&ms, NULL, 0, 0))
    {
        TranslateMessage(&ms);
        DispatchMessage(&ms);
    }

}



void zwolnij_plansze(plansza_podstawa p){
    for(int i=0; i<p->liczba_wierszy;i++){
        free(p->template[i]);
    }
    free(p->template);
    free(p);
}