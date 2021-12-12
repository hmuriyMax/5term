// lab7_2.cpp : Определяет точку входа для приложения.
//

#include <iostream>
#include "framework.h"
#include "lab7_2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HBITMAP hBackImg, hTextImg;
HWND hAnimateButton, hMetaButton; 
WCHAR button1Title[MAX_LOADSTRING], button2Title[MAX_LOADSTRING], button3Title[MAX_LOADSTRING];
HWND hWnd;
RECT rect = { 0, 40, 1000, 707 };

bool DoTask1 = false, DoTask2 = false;
int coordX = 400, coordY = 200;
int i = 3, j = 1;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB72, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON1_TITLE, button1Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON2_TITLE, button2Title, MAX_LOADSTRING);

    hBackImg = LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    hTextImg = LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));

    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB72));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB72));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB72);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1015, 765, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    hAnimateButton = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button1Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
        10, 12, 80, 25, hWnd, (HMENU)IDC_BUTTON1, hInstance, nullptr);
    hMetaButton = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button2Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
        10 + 90, 12, 80, 25, hWnd, (HMENU)IDC_BUTTON2, hInstance, nullptr);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

void Task1() {
    HDC hdc = GetDC(hWnd);
    HDC hdcImg = CreateCompatibleDC(hdc);
    SelectObject(hdcImg, hBackImg);
    BitBlt(hdc, 0, 40, 1000, 667, hdcImg, 0, 0, SRCCOPY);

    if (coordX <= rect.left || coordX + 450 >= rect.right)
        i *= -1;
    if (coordY <= rect.top || coordY + 84 >= rect.bottom)
        j *= -1;
    coordX += i;
    coordY += j;
    SelectObject(hdcImg, hTextImg);
    BitBlt(hdc, coordX, coordY, 450, 84, hdcImg, 0, 0, SRCPAINT);

    ReleaseDC(hWnd, hdc);
    DeleteDC(hdcImg);
}

void Task3() {
    HDC MetaDC;
    MetaDC = CreateMetaFile(L"pic.wmf");
    HPEN hpen = CreatePen(PS_SOLID, 5, RGB(200, 0, 255));
    SelectObject(MetaDC, hpen);
    Ellipse(MetaDC, 0, 0, 200, 100);
    Rectangle(MetaDC, 0, 0, 100, 100);
    CloseMetaFile(MetaDC);
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDC_BUTTON1:
                SetTimer(hWnd, 66, 1, (TIMERPROC)&Task1);
                break;
            case IDC_BUTTON2:
                KillTimer(hWnd, 66);
                InvalidateRect(hWnd, 0, true);
                Task3();
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
