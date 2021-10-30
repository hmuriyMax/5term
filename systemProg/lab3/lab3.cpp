#include "framework.h"
#include "lab3.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

LPCWSTR lab2Name = L"lab2";
LPCWSTR borlandName = L"Form3";
LPCWSTR sharpName = L"ЛР3";
LPCWSTR wnd_name;

HWND hLabel;
HWND hLabel2;
HWND hLabel3;
HWND wnd;
HWND Lab2;
HWND Borland;
HWND Sharp;

HWND hEditHide;
HWND hButHide;
HWND hButSharpHide;
HWND hEditDisable;
HWND hButDisable;
HWND hButDisableSharp;
HWND hButClose;
HWND hButL2Task;
HWND hButL2Abt;
HWND hButRenameChld;
HWND hButRenameAll;

TCHAR tstr[100];


const int  IDEditHide = 0;
const int  IDButHide = 1;

const int  IDEditDis = 5;
const int  IDButDis = 6;

const int  IDButClose = 8;

const int  IDButL2Task = 9;
const int  IDButL2Abt = 10;
const int  IDButRenameChld = 11;

const int  IDButRenameAll = 12;

int wnd_num = 0;
int chld_num = 0;


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

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

    MSG msg;

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB3);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 465, 230, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    hLabel = CreateWindow(L"STATIC", L"Lab2 ", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 25, 75, 25, hWnd, NULL, hInstance, 0);
    hLabel2 = CreateWindow(L"STATIC", L"Borland", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 60, 75, 25, hWnd, NULL, hInstance, 0);
    hLabel3 = CreateWindow(L"STATIC", L"C#", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 95, 75, 25, hWnd, NULL, hInstance, 0);

    hEditHide = CreateWindow(L"EDIT", L"WND", WS_CHILD | NULL | WS_BORDER | WS_VISIBLE, 105, 40, 75, 25, hWnd, (HMENU)IDEditHide, hInstance, 0);
    hButHide = CreateWindow(L"BUTTON", L"Hide", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 105, 75, 75, 25, hWnd, (HMENU)IDButHide, hInstance, 0);

    hEditDisable = CreateWindow(L"EDIT", L"WND", WS_CHILD | NULL | WS_BORDER | WS_VISIBLE, 185, 40, 75, 25, hWnd, (HMENU)IDEditDis, hInstance, 0);
    hButDisable = CreateWindow(L"BUTTON", L"Disable", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 185, 75, 75, 25, hWnd, (HMENU)IDButDis, hInstance, 0);

    hButClose = CreateWindow(L"BUTTON", L"Close", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 265, 95, 75, 25, hWnd, (HMENU)IDButClose, hInstance, 0);

    hButL2Task = CreateWindow(L"BUTTON", L"Act", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 265, 25, 75, 25, hWnd, (HMENU)IDButL2Task, hInstance, 0);
    hButL2Abt = CreateWindow(L"BUTTON", L"About", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 345, 25, 75, 25, hWnd, (HMENU)IDButL2Abt, hInstance, 0);
    hButRenameChld = CreateWindow(L"BUTTON", L"Rename children", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 25, 130, 175, 25, hWnd, (HMENU)IDButRenameChld, hInstance, 0);

    hButRenameAll = CreateWindow(L"BUTTON", L"Rename all windows", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 205, 130, 215, 25, hWnd, (HMENU)IDButRenameAll, hInstance, 0);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

BOOL CALLBACK rename_child(HWND hWnd, LPARAM lParam)
{
    ++chld_num;
    TCHAR name[MAX_LOADSTRING] = _T("Ребёнок №");
    TCHAR num[MAX_LOADSTRING];
    _itot_s(chld_num, num, 10);
    _tcscat_s(name, num);
    SendMessage(hWnd, WM_SETTEXT, NULL, LPARAM(name));
    return TRUE;
}

BOOL CALLBACK rename_window(HWND hWnd, LPARAM lParam)
{
    ++wnd_num;
    TCHAR name[MAX_LOADSTRING] = _T("Окно №");
    TCHAR num[MAX_LOADSTRING];
    _itot_s(wnd_num, num, 10);
    _tcscat_s(name, num);
    SendMessage(hWnd, WM_SETTEXT, NULL, LPARAM(name));
    chld_num = 0;
    EnumChildWindows(hWnd, &rename_child, lParam);
    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_RBUTTONDOWN:
    {
        Lab2 = FindWindow(NULL, lab2Name);
        SendMessage(Lab2, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        Lab2 = FindWindow(NULL, lab2Name);
        SendMessage(Lab2, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    }
    break;
    case WM_LBUTTONUP:
    {
        Lab2 = FindWindow(NULL, lab2Name);
        SendMessage(Lab2, WM_LBUTTONUP, MK_LBUTTON, lParam);
    }
    break;
    case WM_MOUSEMOVE:
    {
        Lab2 = FindWindow(NULL, lab2Name);
        SendMessage(Lab2, WM_MOUSEMOVE, wParam, lParam);
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDButHide:
        {
            GetWindowText(hEditHide, tstr, 100);
            wnd = FindWindow(NULL, tstr);
            if (wnd)
                ShowWindow(wnd, SW_HIDE);
        }
        break;
        case IDButDis:
        {
            GetWindowText(hEditDisable, tstr, 100);
            wnd = FindWindow(NULL, tstr);
            if (wnd)
                EnableWindow(wnd, FALSE);
        }
        break;
        case IDButClose:
        {
            wnd = FindWindow(NULL, sharpName);
            if (wnd)
                if (IsWindowEnabled(wnd))
                    PostMessage(wnd, WM_QUIT, NULL, NULL);
        }
        break;
        case IDButL2Task:
        {
            Lab2 = FindWindow(NULL, lab2Name);
            HWND hBut = NULL;
            if (Lab2)
                hBut = FindWindowEx(Lab2, NULL, L"BUTTON", L"Calc");
            if (hBut)
                SendMessage(hBut, BM_CLICK, 0, 0);
        }
        break;
        case IDButL2Abt:
        {
            Lab2 = FindWindow(NULL, lab2Name);
            if (Lab2)
                SendMessage(Lab2, WM_COMMAND, IDM_ABOUT, NULL);
        }
        break;
        case IDButRenameChld:
        {
            Lab2 = FindWindow(NULL, lab2Name);
            if (Lab2)
                chld_num = 0;
                EnumChildWindows(Lab2, &rename_child, lParam);
        }
        break;
        case IDButRenameAll:
        {
            wnd_num = 0;
            EnumChildWindows(NULL, &rename_window, lParam);
        }
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


