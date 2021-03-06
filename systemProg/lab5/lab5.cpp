#include "stdafx.h"
#include "Lab5.h"
#include <math.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HWND mainWindow;
HWND button1;
HWND button2;
HWND button3;
HWND button4;

WCHAR button1Title[MAX_LOADSTRING];
WCHAR button2Title[MAX_LOADSTRING];
WCHAR button3Title[MAX_LOADSTRING];
WCHAR button4Title[MAX_LOADSTRING];

bool DoTask1 = false;
bool DoTask2 = false;
bool DoTask3 = false;
bool lButtonPressed = false;

int lButtonPressedX;
int lButtonPressedY;
int lButtonX;
int lButtonY;

int i = 0;
int j = 0;
double k = 0;
int R = 5;

vector<RECT> lines;

COLORREF avgDesktopColor = RGB(207, 212, 212);

const COLORREF WHITE RGB(255, 255, 255);
const COLORREF RED RGB(255, 0, 0);
const COLORREF GREEN RGB(0, 255, 0);
const COLORREF BLUE RGB(0, 0, 255);

const RECT FLAGWHITE = { 100, 100, 300, 130 };
const RECT FLAGBLUE = { 100, 130, 300, 160 };
const RECT FLAGRED = { 100, 160, 300, 190 };

const RECT circleArea = {0, 0, 700, 700};

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

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);

    LoadStringW(hInstance, IDS_BUTTON1_TITLE, button1Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON2_TITLE, button2Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON3_TITLE, button3Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON4_TITLE, button4Title, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


COLORREF GetAvgColor() {
	HWND win = GetDesktopWindow();
	HDC cl = GetDC(win);
	RECT rec;
	long long red = 0, green = 0, blue = 0, count = 0;
	GetWindowRect(win, &rec);
	for (int i = 0; i < rec.right; i += 300)
		for (int j = 0; j < rec.bottom; j += 300)
		{
			count++;
			COLORREF color = GetPixel(cl, i, j);
			red += GetRValue(color);
			green += GetGValue(color);
			blue += GetBValue(color);
		}
	red = int(red / count);
	green = int(green / count);
	blue = int(blue / count);
	ReleaseDC(win, cl);
	return RGB(red, green, blue);
}

BOOL DrawRect(HWND hWnd, HDC hdc, const vector<int>& pts, const COLORREF& clr) {
	HPEN pen = CreatePen(PS_DASH, 2, clr);
	HBRUSH brush = CreateSolidBrush(clr);
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	POINT* ptss = new POINT[5];
	for (int i = 0; i < pts.size(); i += 2) {
		ptss[i / 2] = { pts[i], pts[i + 1] };
	}
	ptss[4] = ptss[0];
	return Polygon(hdc, ptss, 4);
}

BOOL DrawRound(HWND hWnd, HDC hdc, int x, int y, int r, const COLORREF& clr) {
	HPEN pen = CreatePen(PS_DASH, 2, clr);
	HBRUSH brush = CreateSolidBrush(clr);
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	return Ellipse(hdc, x - r, y - r, x + r, y + r);
}

void DrawWall(HWND hWnd, HDC hdc) {
	//Рисуем дверки да окна
	HPEN pen = CreatePen(PS_DASH, 2, RGB(75, 75, 75));
	HBRUSH brush = CreateSolidBrush(RGB(75, 75, 75));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, 10, 70, 501, 501);

	for (int j = 0; j <= 90; j++) {
		int i = 90 - j;
		float num = j;
		DrawRound(hWnd, hdc, 270, 230, i, RGB(255 - 180 * cos(3.14 / 2 * num / 90), 255 - 180 * cos(3.14 / 2 * num / 90), 200 - 125 * cos(3.14 / 2 * num / 90)));
	}

	vector<int> pts_2 = { 180, 230, 180, 140, 360, 140, 360, 230 };
	DrawRect(hWnd, hdc, pts_2, RGB(75, 75, 75));

	vector<int> pts_3 = { 260, 230, 265, 210, 275, 210, 280, 230, 260, 230 };
	DrawRect(hWnd, hdc, pts_3, RGB(50, 50, 50));

	vector<int> pts_1 = { 190, 460, 210, 270, 320, 270, 300, 460, 190, 460 };
	DrawRect(hWnd, hdc, pts_1, RGB(100, 71, 50));

	vector<int> pts2 = { 10, 450, 500, 450, 500, 500, 10, 500, 10, 450 };
	DrawRect(hWnd, hdc, pts2, RGB(50, 50, 50));

	vector<int> pts0 = { 200, 450, 220, 280, 310, 280, 290, 450, 200, 450 };
	DrawRect(hWnd, hdc, pts0, RGB(240, 240, 150));

	vector<int> pts = { 200, 450, 220, 280, 290, 290, 270, 460, 200, 450 };
	DrawRect(hWnd, hdc, pts, RGB(125, 104, 87));

	for (int j = 0; j <= 15; j++) {
		int i = 15 - j;
		vector<int> pts3 = { 100 - i, 400 + i, 115 - i, 300 - i, 170 + i, 300 - i, 155 + i, 400 + i, 100 - i, 400 + i };
		int num = (240 - 75) / 15;
		DrawRect(hWnd, hdc, pts3, RGB(240 - num * i, 240 - num * i, i * 75 / 15));
	}

	vector<int> pts31 = { 96, 404, 111, 296, 174, 296, 159, 404, 96, 404 };
	DrawRect(hWnd, hdc, pts31, RGB(170, 170, 100));

	vector<int> pts3 = { 100, 400, 115, 300, 170, 300, 155, 400, 100, 400 };
	DrawRect(hWnd, hdc, pts3, RGB(240, 240, 150));

	for (int j = 0; j <= 15; j++) {
		int i = 15 - j;
		vector<int> pts4 = { 340 - i, 400 + i, 355 - i, 300 - i, 410 + i, 300 - i, 395 + i, 400 + i, 340 - i, 400 + i };
		int num = (240 - 75) / 15;
		DrawRect(hWnd, hdc, pts4, RGB(240 - num * i, 240 - num * i, i * 75 / 15));
	}
	vector<int> pts41 = { 336, 404, 351, 296, 414, 296, 399, 404, 336, 404 };
	DrawRect(hWnd, hdc, pts41, RGB(170, 170, 100));

	vector<int> pts4 = { 340, 400, 355, 300, 410, 300, 395, 400, 340, 400 };
	DrawRect(hWnd, hdc, pts4, RGB(240, 240, 150));
}

void DrawTextOntheWall(HWND hWnd, HDC hdc) {
	HBRUSH brush = CreateSolidBrush(TRANSPARENT);
	SelectObject(hdc, brush);

	HGDIOBJ font = CreateFont(40, 0, 0, 0, 700, true, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Roboto Bk");
	SelectObject(hdc, font);

	for (int i = 50; i > 40; i--) {
		int j = 50 - i;
		SetTextColor(hdc, RGB(75 + j * 18, 75 - 5.5 * j, 75 + 2.5 * j));
		TextOut(hdc, 210 + 10 - j, 125 - 5 + j * 0.5, TEXT("BAR"), 3);
	}

	SetTextColor(hdc, RGB(255, 20, 100));
	TextOut(hdc, 210, 125, TEXT("BAR"), 3);

	font = CreateFont(20, 0, 0, 0, 700, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Agency FB");
	SelectObject(hdc, font);

	for (int i = 50; i > 40; i--) {
		int j = 50 - i;
		SetTextColor(hdc, RGB(75 + j * 8, 75 - 5.5 * j, 75 + 7.5 * j));
		TextOut(hdc, 220 + 5 - j * 0.5, 100 - 2 + j * 0.2, TEXT("ZINZIVER"), 8);
	}

	SetTextColor(hdc, RGB(255, 120, 250));
	TextOut(hdc, 220, 100, TEXT("ZINZIVER"), 8);
}

void drawLine(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, nullptr);
	LineTo(hdc, endX, endY);
}

void drawAllLines(HDC hdc) {
	for (auto& rect : lines) {
		drawLine(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
}

void drawFlag(HDC hdc, int ltx, int lty, int rbx, int rby) {
	HBRUSH brushWhite = CreateSolidBrush(WHITE);
	HBRUSH brushBlue = CreateSolidBrush(BLUE);
	HBRUSH brushRed = CreateSolidBrush(RED);
	int hgt = rby - lty;
	int wdt = rbx - ltx;
	SelectObject(hdc, brushWhite);
	Rectangle(hdc, ltx, lty, rbx, lty + hgt / 3);
	SelectObject(hdc, brushBlue);
	Rectangle(hdc, ltx, lty + hgt / 3, rbx, lty + 2 * hgt / 3);
	SelectObject(hdc, brushRed);
	Rectangle(hdc, ltx, lty + 2 * hgt / 3, rbx, rby);
}

void Task1() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mainWindow, &ps);

	RECT rect;
	GetWindowRect(mainWindow, &rect);
	rect.bottom = rect.bottom - rect.top;
	rect.right = rect.right - rect.left;
	rect.left = 0;
	rect.top = 0;


	HBRUSH brush = CreateSolidBrush(GetAvgColor());
	FillRect(hdc, &rect, brush);

	DrawWall(mainWindow, hdc);
	DrawTextOntheWall(mainWindow, hdc);

	EndPaint(mainWindow, &ps);
}

void Task2() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mainWindow, &ps);

	drawFlag(hdc, 100, 100, 400, 400);

	HWND desktop = GetDesktopWindow();
	HDC desktopDC = GetWindowDC(desktop);
	drawFlag(desktopDC, 100, 100, 400, 400);

	HWND sharp = FindWindow(NULL, _T("Lab8 lists"));
	HDC sharpDC = GetWindowDC(sharp);
	drawFlag(sharpDC, 100, 100, 400, 400);

	ReleaseDC(desktop, desktopDC);
	ReleaseDC(sharp, sharpDC);
	EndPaint(mainWindow, &ps);
}

VOID CALLBACK drawCircle(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) {
	HWND desktop = GetDesktopWindow();
	HWND sharp = FindWindow(NULL, _T("Lab8 lists"));
	HDC mainDC = GetWindowDC(mainWindow);
	HDC desktopDC = GetWindowDC(desktop);
	HDC sharpDC = GetWindowDC(sharp);

	COLORREF color = RGB(255, 125, 150);
	k++;

	bool isvertical = true;
	bool topleft = true;
	int Cx = 30 + k;
	int Cy = 30 + k;
	int Cr = 15 + int(k) % 30;
	DrawRound(mainWindow, mainDC, Cx, Cy, Cr, color);
	DrawRound(sharp, sharpDC, Cx, Cy, Cr, color);
	DrawRound(desktop, desktopDC, Cx, Cy, Cr, color);

	ReleaseDC(mainWindow, mainDC);
	ReleaseDC(desktop, desktopDC);
	ReleaseDC(sharp, sharpDC);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

    mainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, 600, 650, nullptr, nullptr, hInstance, nullptr);
    button1 = CreateWindowW(_T("BUTTON"), button1Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       20, 20, 100, 30, mainWindow, (HMENU)IDC_BUTTON1, hInstance, nullptr);
    button2 = CreateWindowW(_T("BUTTON"), button2Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       140, 20, 100, 30, mainWindow, (HMENU)IDC_BUTTON2, hInstance, nullptr);
    button3 = CreateWindowW(_T("BUTTON"), button3Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       260, 20, 100, 30, mainWindow, (HMENU)IDC_BUTTON3, hInstance, nullptr);
    button4 = CreateWindowW(_T("BUTTON"), button4Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
      390, 20, 100, 30, mainWindow, (HMENU)IDC_BUTTON4, hInstance, nullptr);

	if (!mainWindow)
    {
       return FALSE;
    }
    
    ShowWindow(mainWindow, nCmdShow);
    UpdateWindow(mainWindow);
    
    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
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
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			case IDC_BUTTON1:
				{
					DoTask1 = true;
					DoTask2 = false;
					DoTask3 = false;
					InvalidateRect(mainWindow, nullptr, true);
				}
				break;
			case IDC_BUTTON2:
				{
					DoTask1 = false;
					DoTask2 = true;
					DoTask3 = false;
					InvalidateRect(mainWindow, nullptr, true);
				}
				break;
			case IDC_BUTTON3:
				{
					DoTask1 = false;
					DoTask2 = false;
					DoTask3 = true;

					k = 5;
					SetTimer(mainWindow, 322, 10, &drawCircle);
				}
				break;
			case IDC_BUTTON4:
				{
					DoTask1 = false;
					DoTask2 = false;
					DoTask3 = false;
					lines.clear();
					InvalidateRect(nullptr, nullptr, true);
					KillTimer(mainWindow, 322);
				}
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
        }
        break;
	case WM_LBUTTONDOWN:
	{
		lButtonPressed = true;
		lButtonPressedX = LOWORD(lParam);
		lButtonPressedY = HIWORD(lParam);
	}
		break;
	case WM_LBUTTONUP:
	{
		lButtonPressed = false;
		lines.push_back({ lButtonPressedX, lButtonPressedY, lButtonX, lButtonY });
	}
		break;
	case WM_MOUSEMOVE:
	{	
		if(DoTask1 || DoTask2 || DoTask3)
			break;
		if (lButtonPressed) {
			lButtonX = LOWORD(lParam);
			lButtonY = HIWORD(lParam);

			InvalidateRect(mainWindow, nullptr, true);
		}
	}
		break;
    case WM_PAINT:
        {
			if (DoTask1) {
				Task1();
			}	
			else if (DoTask2) {
				Task2();
			}
			else if (!DoTask3) {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				if (lButtonPressed) {
					drawLine(hdc, lButtonPressedX, lButtonPressedY, lButtonX, lButtonY);
				}

				drawAllLines(hdc);
			}
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