#include <windows.h>

#pragma comment(lib, "gdi32.lib")

char ClassName[] = "SimpleWinClass";

int cellSize = 10;
int playerX, playerY;

LRESULT CALLBACK WndProc(HWND h, UINT uMsg, WPARAM wP, LPARAM lP)
{
    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize player position to the center of the grid
        playerX = 500;
        playerY = 500;
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);

        // Draw grid
        for (int x = 0; x < 100; x++)
        {
            for (int y = 0; y < 100; y++)
            {
                Rectangle(hdc, x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize);
            }
        }

        // Draw player rectangle
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 0)); 
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
        // Handle arrow key input for player movement
        switch (wP)
        {
        case VK_LEFT:
            playerX = max(0, playerX - cellSize);
            break;
        case VK_RIGHT:
            playerX = min(1000 - cellSize, playerX + cellSize);
            break;
        case VK_UP:
            playerY = max(0, playerY - cellSize);
            break;
        case VK_DOWN:
            playerY = min(00 - cellSize, playerY + cellSize);
            break;
        }

        InvalidateRect(h, NULL, TRUE);
        break;
    default:
        return DefWindowProc(h, uMsg, wP, lP);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprevinst, LPSTR cmdLine, int cmdShow)
{
    WNDCLASSEX wc;
    MSG ms;
    HWND h;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hInstance = hinst;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ClassName;
    wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassEx(&wc))
        return 0;

    h = CreateWindowEx(0, ClassName, "Nasze pierwsze okno", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 1000, 0, 0, hinst, 0);

    if (!h)
        return 0;

    ShowWindow(h, cmdShow);
    UpdateWindow(h);

    while (GetMessage(&ms, NULL, 0, 0))
    {
        TranslateMessage(&ms);
        DispatchMessage(&ms);
    }

    return ms.wParam;
}
