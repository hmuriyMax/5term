// Lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

BOOL fl = FALSE;
RECT rect;
TCHAR Test[500];
static int NCHITTEST_count = 0;
const int IDButton1 = 0;
const int IDButton2 = 1;
const int IDEdit3 = 2;
const int IDStatic4 = 3;
const int IDStatic5 = 4;
const int IDStatic6 = 5;
const int IDStatic7 = 6;
HWND But1;
HWND But2;
HWND Edit3;
HWND Static4;
HWND Static5;
HWND Static6;
HWND Static7;
HDC hdc;
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
	LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2);
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 380, 315, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	But1 = CreateWindow(TEXT("BUTTON"), TEXT("Calc"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 25, 55, 150, 25, hWnd, (HMENU)IDButton1, hInstance, NULL);
	But2 = CreateWindow(TEXT("BUTTON"), TEXT("Push first button"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 25 + 150 + 5, 55, 150, 25, hWnd, (HMENU)IDButton2, hInstance, NULL);
	Edit3 = CreateWindow(TEXT("EDIT"), TEXT("Input number"), WS_VISIBLE | WS_CHILD | NULL | WS_BORDER, 25, 25, 150 * 2 + 5, 25, hWnd, (HMENU)IDEdit3, hInstance, NULL);
	Static4 = CreateWindow(TEXT("STATIC"), TEXT("Squared number"), WS_VISIBLE | WS_CHILD | NULL, 25, 85, 150 * 2 + 5, 25, hWnd, (HMENU)IDStatic4, hInstance, NULL);
	Static5 = CreateWindow(TEXT("STATIC"), TEXT("Mouse coordinates"), WS_VISIBLE | WS_CHILD | NULL, 25, 115, 150 * 2 + 5, 25, hWnd, (HMENU)IDStatic4, hInstance, NULL);
	Static6 = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD | NULL, 25, 145, 150 * 2 + 5, 50, hWnd, (HMENU)IDStatic5, hInstance, NULL);
	Static7 = CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD | NULL, 25, 200, 150 * 2 + 5, 25, hWnd, (HMENU)IDStatic5, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	return TRUE;
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

	case WM_RBUTTONDOWN:
	{
		POINT coordinates;
		coordinates.x = LOWORD(lParam);
		coordinates.y = HIWORD(lParam);
		TCHAR tstrX[10], tstrY[10];
		_itot_s(coordinates.x, tstrX, 10);
		_itot_s(coordinates.y, tstrY, 10);
		_tcscat_s(tstrX, _T(" "));
		_tcscat_s(tstrX, tstrY);
		SetWindowText(Static5, tstrX);
	}
	break;
	case WM_RBUTTONUP:
	{
		fl = FALSE;
	}
	case WM_LBUTTONDOWN:
	{
		fl = TRUE;
		_tcscat_s(Test, _T("Down "));
		SetWindowText(Static6, Test);
	}
	break;
	case WM_LBUTTONUP:
	{
		_tcscat_s(Test, _T("Up "));
		SetWindowText(Static6, Test);
		fl = FALSE;
	}
	break;

	case WM_LBUTTONDBLCLK:
	{
		_tcscat_s(Test, _T("Double "));
		SetWindowText(Static6, Test);
	}
	break;

	case WM_NCLBUTTONDOWN:
	{
		// Denying moving by caption
		if (wParam == 2)
			return 0;
		LRESULT lRes = DefWindowProc(hWnd, message, wParam, lParam);
		return lRes;
	}
	break;
	case WM_NCHITTEST:
	{
		NCHITTEST_count++;
		TCHAR str[10];
		_itot_s(NCHITTEST_count, str, 10);
		SetWindowText(Static7, str);

		LRESULT lRes = DefWindowProc(hWnd, message, wParam, lParam);
		return lRes;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (fl)
		{
			POINT coordinates;
			coordinates.x = LOWORD(lParam);
			coordinates.y = HIWORD(lParam);
			SetWindowPos(hWnd, HWND_TOP, coordinates.x - rect.left, coordinates.y - rect.top, 0, 0, SWP_NOSIZE);
		}
	}
	break;

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
		case IDButton1:
		{
			TCHAR tstr[100];
			GetWindowText(Edit3, tstr, 100);
			int num = _ttoi(tstr);
			_itot_s(num * num, tstr, 10);
			SetWindowText(Static4, tstr);
			break;
		}

		case IDButton2:
		{
			SendMessage(But1, BM_CLICK, 0, 0);
			break;
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
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Close window?"), TEXT("Message"), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			MessageBox(hWnd, TEXT("Continue working."), TEXT("Message"), MB_OK);
		}
		break;
	case WM_DESTROY:
		MessageBox(hWnd, TEXT("Windnow closed."), TEXT("Message"), MB_OK);
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
