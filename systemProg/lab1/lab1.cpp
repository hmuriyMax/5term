// lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];    // имя класса главного окна
HWND button1, button2, input1, output1;
WCHAR str[10000];
RECT cords, cords2;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        CW_USEDEFAULT, 0, 525, 320, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    HRGN rgn, el, rnd;

    button1 = CreateWindow(TEXT("BUTTON"), TEXT("who am  i"), WS_CHILD | WS_VISIBLE, 10, 160, 80, 20, hWnd, NULL, hInst, NULL);
    button2 = CreateWindow(TEXT("BUTTON"), TEXT("who are u"), WS_CHILD | WS_VISIBLE, 100, 160, 80, 20, hWnd, NULL, hInst, NULL);
    input1 = CreateWindow(TEXT("EDIT"), TEXT("input me"), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 240, 140, hWnd, NULL, hInst, NULL);
    output1 = CreateWindow(TEXT("STATIC"), TEXT("output me"), WS_CHILD | WS_VISIBLE | WS_BORDER, 260, 10, 240, 140, hWnd, NULL, hInst, NULL);

    rgn = CreateRectRgn(0, 0, 525, 250);
    el = CreateEllipticRgn(0, 200, 525, 300);
    rnd = CreateEllipticRgn(250, 240, 275, 265);
    CombineRgn(rgn, rgn, el, RGN_OR);
    CombineRgn(rgn, rgn, rnd, RGN_XOR);

    SetWindowRgn(hWnd, rgn, true);
    ShowWindow(hWnd, nCmdShow);
    //SetWindowPos(hWnd, HWND_NOTOPMOST, 100, 100, 525, 250, SWP_SHOWWINDOW);
    UpdateWindow(hWnd);

    return TRUE;
}

void MoveBut(HWND &but) {
    GetWindowRect(but, &cords);
    int wid = abs(cords.left - cords.right);
    int hei = abs(cords.top - cords.bottom);
    for (int i = 0; i < 200; i++) {
        SetWindowPos(but, HWND_NOTOPMOST, cords.left + i, cords.top + i, wid, hei, WS_VISIBLE);
        Sleep(10);
    }
    return;
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
    case WM_CREATE:
    {
        MessageBox(hWnd, TEXT("День добрый! Добро пожаловать в ЛР1!"), TEXT("Первое окно"), MB_OK);
    }
    case WM_COMMAND:
    {
        if ((HWND)lParam == button1) {
            GetWindowText(input1, str, 10000);
            SetWindowText(output1, str);
        }
        else if ((HWND)lParam == button2) {
            GetWindowText(hWnd, str, 10000);
            SetWindowText(output1, str);
        }
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case ID_0001:
        {
            MessageBox(hWnd, TEXT("Нажата кнопка меню"), TEXT("Окно нажатия."), MB_OK);
            GetWindowRect(button1, &cords);
            GetWindowRect(hWnd, &cords2);
            SetParent(button1, NULL);
            int lft = cords2.left;
            int top = cords2.top;
            int wid = abs(cords.left - cords.right);
            int hei = abs(cords.top - cords.bottom);
            for (int i = 0; i <= 200; i++) {
                SetWindowPos(button1, HWND_NOTOPMOST,  cords.left + i,  cords.top - int(((i-100)*(i-100) - 10000)/100), wid, hei, 0);
                Sleep(10); 
                UpdateWindow(button1);
            }
        }
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
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_RBUTTONDOWN:
        SetParent(button1, hWnd);
        SetWindowPos(button1, HWND_TOP, 10, 160, 80, 20, SWP_SHOWWINDOW);
        MessageBox(hWnd, TEXT("Нажата правая кнопка"), TEXT("Окно нажатия."), MB_OK);
        break;

    case WM_LBUTTONDOWN:
        MessageBox(hWnd, TEXT("Нажата левая кнопка"), TEXT("Окно нажатия."), MB_OK);
        break;

    case WM_DESTROY:
        MessageBox(hWnd, TEXT("Вы ушли! Bye!"), TEXT("Последнее окно."), MB_OK);
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
