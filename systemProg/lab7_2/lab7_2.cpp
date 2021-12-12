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
HBITMAP hImg1, hImg2;
HWND hButton1, hButton2; 
WCHAR button1Title[MAX_LOADSTRING], button2Title[MAX_LOADSTRING], button3Title[MAX_LOADSTRING];
HWND hWnd;
RECT back_rect = { 0, 40, 536, 733 };

bool DoTask1 = false, DoTask2 = false;
int ball_x_coordinate = 500, ball_y_coordinate = 600;
int i = 5, j = -10;

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
        CW_USEDEFAULT, 0, 551, 788, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    hButton1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button1Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
        10, 12, 80, 25, hWnd, (HMENU)IDC_BUTTON1, hInstance, nullptr);
    hButton2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button2Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
        10 + 90, 12, 80, 25, hWnd, (HMENU)IDC_BUTTON2, hInstance, nullptr);

    hImg1 = LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
    hImg2 = LoadBitmapW(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    return TRUE;
}

void upd() {
    InvalidateRect(hWnd, &back_rect, false);
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
                DoTask1 = true;
                DoTask2 = false;
                SetTimer(hWnd, 333, 10, (TIMERPROC(upd)));
                break;
            case IDC_BUTTON2:
                DoTask2 = true;
                DoTask1 = false;
                KillTimer(hWnd, 333);
                InvalidateRect(hWnd, 0, true);
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
            if (DoTask1) {
                HDC hdc = GetDC(hWnd);
                HDC hdcImg = CreateCompatibleDC(hdc);
                SelectObject(hdcImg, hImg1);
                BitBlt(hdc, back_rect.left, back_rect.top, back_rect.right, back_rect.bottom, hdcImg, 0, 0, SRCCOPY);

                j -= -1;
                ball_x_coordinate -= i;
                ball_y_coordinate += j;
                if (ball_y_coordinate > 600) {
                    ball_y_coordinate = 600;
                    j *= -1;
                }
                if (ball_x_coordinate < -60) {
                    ball_x_coordinate += 700;
                }
                SelectObject(hdcImg, hImg2);
                BitBlt(hdc, ball_x_coordinate, ball_y_coordinate, 51, 51, hdcImg, 0, 0, SRCPAINT);

                ReleaseDC(hWnd, hdc);
                DeleteDC(hdcImg);
            }
            if (DoTask2) {
                HDC hDC;
                hDC = CreateMetaFile(L"file.wmf");
                HPEN hpen = CreatePen(PS_SOLID, 5, RGB(20, 150, 200));
                SelectObject(hDC, hpen);
                Ellipse(hDC, 0, 0, 400, 400);
                hpen = CreatePen(PS_SOLID, 5, RGB(255, 10, 10));
                SelectObject(hDC, hpen);
                Ellipse(hDC, 120, 120, 190, 190);
                Ellipse(hDC, 210, 120, 280, 190);
                Rectangle(hDC, 100, 310, 300, 250);
                CloseMetaFile(hDC);
            }
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
