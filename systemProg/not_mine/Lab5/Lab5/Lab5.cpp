#include "stdafx.h"
#include "Lab5.h"
#include <math.h>
#include <vector>

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
HWND clearButton;

WCHAR button1Title[MAX_LOADSTRING];
WCHAR button2Title[MAX_LOADSTRING];
WCHAR button3Title[MAX_LOADSTRING];
WCHAR clearButtonTitle[MAX_LOADSTRING];

bool button1Pushed = false;
bool button2Pushed = false;
bool button3Pushed = false;
bool lButtonPressed = false;

int lButtonPressedX;
int lButtonPressedY;
int lButtonX;
int lButtonY;

int i = 0;
int j = 0;
double k = 0;
int R = 5;
RECT circle = { 200, 200, 300, 300 };

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
COLORREF getAverageColor(HWND window);
void drawFigures();
void drawFlags();
void drawAnimatedCircle();
void drawCircle(HWND hWnd, HDC hdc, RECT &circle, COLORREF color, int i, int j);
void drawLine(HDC hdc, int startX, int startY, int endX, int endY);
void drawAllLines(HDC hdc);
VOID CALLBACK drawAnimatedCircleByTimer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
void drawFlagOnWindow(HDC hdc, HBRUSH brushWhite, HBRUSH brushBlue, HBRUSH brushRed);

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
    LoadStringW(hInstance, IDS_CLEAR_BUTTON_TITLE, clearButtonTitle, MAX_LOADSTRING);
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
       CW_USEDEFAULT, 0, 1000, 650, nullptr, nullptr, hInstance, nullptr);
    button1 = CreateWindowW(_T("BUTTON"), button1Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       20, 20, 150, 30, mainWindow, (HMENU)IDC_BUTTON1, hInstance, nullptr);
    button2 = CreateWindowW(_T("BUTTON"), button2Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       190, 20, 150, 30, mainWindow, (HMENU)IDC_BUTTON2, hInstance, nullptr);
    button3 = CreateWindowW(_T("BUTTON"), button3Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
       360, 20, 150, 30, mainWindow, (HMENU)IDC_BUTTON3, hInstance, nullptr);
    clearButton = CreateWindowW(_T("BUTTON"), clearButtonTitle, WS_BORDER | WS_VISIBLE | WS_CHILD,
      530, 20, 120, 30, mainWindow, (HMENU)IDC_CLEAR_BUTTON, hInstance, nullptr);

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
					//avgDesktopColor = getAverageColor(GetDesktopWindow());
					button1Pushed = true;
					button2Pushed = false;
					button3Pushed = false;
					InvalidateRect(mainWindow, nullptr, true);
				}
				break;
			case IDC_BUTTON2:
				{
					button1Pushed = false;
					button2Pushed = true;
					button3Pushed = false;
					InvalidateRect(mainWindow, nullptr, true);
				}
				break;
			case IDC_BUTTON3:
				{
					button1Pushed = false;
					button2Pushed = false;
					button3Pushed = true;

					SetTimer(mainWindow, 322, 10, &drawAnimatedCircleByTimer);
				}
				break;
			case IDC_CLEAR_BUTTON:
				{
					button1Pushed = false;
					button2Pushed = false;
					button3Pushed = false;
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
		if(button1Pushed || button2Pushed || button3Pushed)
			break;
		if (lButtonPressed) {
			lButtonX = LOWORD(lParam);
			lButtonY = HIWORD(lParam);

			int x1 = min(lButtonX, lButtonPressedX);
			int x2 = max(lButtonX, lButtonPressedX);
			int y1 = min(lButtonY, lButtonPressedY);
			int y2 = max(lButtonY, lButtonPressedY);
			RECT rect = { x1 - 100, y1 - 100, x2 + 100, y2 + 100 };

			InvalidateRect(mainWindow, &rect, true);
		}
	}
		break;
    case WM_PAINT:
        {
			if(button1Pushed) {
				drawFigures();
			} 
			else if (button2Pushed) {
				drawFlags();
			}
			else if (button3Pushed) {
				//drawAnimatedCircle();
			}
			else {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);

				//SetROP2(hdc, R2_NOTXORPEN);
				if (lButtonPressed) {
					drawLine(hdc, lButtonPressedX, lButtonPressedY, lButtonX, lButtonY);
				}

				drawAllLines(hdc);
		
				EndPaint(hWnd, &ps);
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

void drawFigures() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mainWindow, &ps);

	RECT rect;
	GetWindowRect(mainWindow, &rect);
	rect.bottom = rect.bottom - rect.top;
	rect.right = rect.right - rect.left;
	rect.left = 0;
	rect.top = 0;

	// fill window with avgDesktop color
	HBRUSH brush = CreateSolidBrush(avgDesktopColor);
	FillRect(hdc, &rect, brush);

	HPEN pen1, pen2, pen3;
	pen1 = CreatePen(PS_DASH, 5, RED);
	pen2 = CreatePen(PS_DASHDOT, 5, GREEN);
	pen3 = CreatePen(PS_DOT, 5, BLUE);
	brush = CreateSolidBrush(BLUE);

	// draw rect
	SelectObject(hdc, pen1);
	RECT r1 = {300, 200, 500, 300};
	Rectangle(hdc, 300, 200, 500, 300);
	
	// draw ellipse
	SelectObject(hdc, pen2);
	SelectObject(hdc, brush);
	RECT r2 = {350, 250, 500, 300};
	Ellipse(hdc, 350, 250, 550, 350);

	// draw line
	SelectObject(hdc, pen3);
	MoveToEx(hdc, 400, 400, nullptr);
	LineTo(hdc, 800, 550);

	EndPaint(mainWindow, &ps);
}

void drawFlags() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mainWindow, &ps);

	HBRUSH brushWhite = CreateSolidBrush(WHITE);
	HBRUSH brushBlue = CreateSolidBrush(BLUE);
	HBRUSH brushRed = CreateSolidBrush(RED);

	// draw flag
	drawFlagOnWindow(hdc, brushWhite, brushBlue, brushRed);

	HWND desktop = GetDesktopWindow();
	HDC desktopDC = GetWindowDC(desktop);
	// draw flag
	drawFlagOnWindow(desktopDC, brushWhite, brushBlue, brushRed);

	HWND sharp = FindWindow(NULL, _T("cs"));
	HDC sharpDC = GetWindowDC(sharp);
	// draw flag
	drawFlagOnWindow(sharpDC, brushWhite, brushBlue, brushRed);
	
	ReleaseDC(desktop, desktopDC);
	ReleaseDC(sharp, sharpDC);
	EndPaint(mainWindow, &ps);
}

void drawFlagOnWindow(HDC hdc, HBRUSH brushWhite, HBRUSH brushBlue, HBRUSH brushRed) {
	SelectObject(hdc, brushWhite);
	Rectangle(hdc, FLAGWHITE.left, FLAGWHITE.top, FLAGWHITE.right, FLAGWHITE.bottom);
	SelectObject(hdc, brushBlue);
	Rectangle(hdc, FLAGBLUE.left, FLAGBLUE.top, FLAGBLUE.right, FLAGBLUE.bottom);
	SelectObject(hdc, brushRed);
	Rectangle(hdc, FLAGRED.left, FLAGRED.top, FLAGRED.right, FLAGRED.bottom);
}

VOID CALLBACK drawAnimatedCircleByTimer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) {
	HWND desktop = GetDesktopWindow();
	HWND sharp = FindWindow(NULL, _T("cs"));
	HDC mainDC = GetWindowDC(mainWindow);
	HDC desktopDC = GetWindowDC(desktop);
	HDC sharpDC = GetWindowDC(sharp);

	COLORREF color = RGB(255, 125, 150);

	i = int(R * cos(k));
	j = int(R * sin(k));
	drawCircle(mainWindow, mainDC, circle, color, i, j);
	drawCircle(sharp, sharpDC, circle, color, i, j);
	drawCircle(desktop, desktopDC, circle, color, i, j);

	k += 0.1;
	if (k > 6.1)
		k = 0;

	ReleaseDC(mainWindow, mainDC);
	ReleaseDC(desktop, desktopDC);
	ReleaseDC(sharp, sharpDC);
}

//void drawAnimatedCircle() {
//	PAINTSTRUCT ps;
//	HDC hdc = BeginPaint(mainWindow, &ps);
//
////	HWND desktop = GetDesktopWindow();
////	HWND sharp = FindWindow(NULL, _T("cs"));
////	HDC desktopDC = GetWindowDC(desktop);
////	HDC sharpDC = GetWindowDC(sharp);
//
//	COLORREF color = RGB(255, 125, 150);
//
//	i = int(R * cos(k));
//	j = int(R * sin(k));
//	drawCircle(mainWindow, hdc, circle, color, i, j);
////	drawCircle(sharp, sharpDC, circle, color, i, j);
////	drawCircle(desktop, desktopDC, circle, color, i, j);
//
//	k += 0.1;
//	if(k > 6.1)
//		k = 0;
//
//	Sleep(20);
//
//	InvalidateRect(mainWindow, nullptr, true);
//
////	ReleaseDC(desktop, desktopDC);
////	ReleaseDC(sharp, sharpDC);
//	EndPaint(mainWindow, &ps);
//}

void drawCircle(HWND hWnd, HDC hdc, RECT &circle, COLORREF color, int i, int j) {
	SelectObject(hdc, (HBRUSH)CreateSolidBrush(color));
	circle.left += i;
	circle.top += j;
	circle.right += i;
	circle.bottom += j;
	Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);
}

void drawLine(HDC hdc, int startX, int startY, int endX, int endY) {
	MoveToEx(hdc, startX, startY, nullptr);
	LineTo(hdc, endX, endY);
}

void drawAllLines(HDC hdc) {
	for (auto &rect : lines) {
		drawLine(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
}

COLORREF getAverageColor(HWND window) {
	HDC windowDC = GetWindowDC(window);
	RECT windowRect;
	GetWindowRect(window, &windowRect);

	int r = 0;
	int g = 0;
	int b = 0;
	int k = 0;
	for (int i = windowRect.left; i <= windowRect.right; i += 10) {
		for (int j = windowRect.top; j <= windowRect.bottom; j += 10) {
			COLORREF Color = GetPixel(windowDC, i, j);
			r += GetRValue(Color);
			g += GetGValue(Color);
			b += GetBValue(Color);
			k++;
		}
	}
	return RGB(r / k, g / k, b / k);
}