#include "stdafx.h"
#include "Lab2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

WCHAR button1Title[MAX_LOADSTRING];            
WCHAR button2Title[MAX_LOADSTRING];         

HWND mainWindow;
HWND button1;
HWND button2;
HWND edit;
HWND staticOut;
HWND staticLog;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int rButtonDownX;
int rButtonDownY;

bool lButtonDown = false;
int lButtonDownX;
int lButtonDownY;
RECT mainRect;

LPWSTR log = new TCHAR[10000];

LPWSTR numToStr(int num);
bool isNumber(LPWSTR str);
int getLengthOfNum(int num);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	log[0] = '\0';
    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON1_TITLE, button1Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON2_TITLE, button2Title, MAX_LOADSTRING);


    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   button1 = CreateWindow(L"BUTTON", button1Title, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   100, 100, 100, 40, mainWindow, (HMENU)IDC_BUTTON1, hInstance, nullptr);
   button2 = CreateWindow(L"BUTTON", button2Title, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   300, 100, 100, 40, mainWindow, (HMENU)IDC_BUTTON2, hInstance, nullptr);
   edit = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_LEFT | WS_BORDER,
	   100, 200, 100, 40, mainWindow, (HMENU)IDC_EDIT, hInstance, nullptr);
   staticOut = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT,
	   300, 200, 100, 40, mainWindow, (HMENU)IDC_STATIC_OUT, hInstance, nullptr);
   staticLog = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT,
	   300, 300, 1000, 240, mainWindow, (HMENU)IDC_STATIC_LOG, hInstance, nullptr);

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
					int strSize = GetWindowTextLength(edit) + 1;
					LPWSTR str = new TCHAR[strSize];
					GetWindowText(edit, str, strSize);

					if (isNumber(str)) {
						int num = _ttoi(str);
						num *= num;
						LPWSTR newStr = numToStr(num);
						SetWindowText(staticOut, newStr);
					}
				}
                break;
			case IDC_BUTTON2:
				{
					SendMessage(button1, BM_CLICK, 0, 0);

					//SendMessage(button1, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(5, 5));
					//SendMessage(button1, WM_LBUTTONUP, 0, MAKELONG(5, 5));
				}
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_RBUTTONDOWN: 
		{
			rButtonDownX = LOWORD(lParam);
			rButtonDownY = HIWORD(lParam);
		}
		break;
	case WM_RBUTTONUP: 
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (x == rButtonDownX && y == rButtonDownY) {
				int xNumLen = getLengthOfNum(x);
				int yNumLen = getLengthOfNum(y);
				int len = 8 + xNumLen + yNumLen;
				LPWSTR str = new TCHAR[100];
				str[0] = '\0';
				wcscat_s(str, len, L"X: ");
				wcscat_s(str, len, numToStr(x));
				wcscat_s(str, len, L" Y: ");
				wcscat_s(str, len, numToStr(y));
				SetWindowText(staticOut, str);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			wcscat_s(log, 10000, L"WM_LBUTTONDOWN ");
			SetWindowText(staticLog, log);

			lButtonDown = true;
			lButtonDownX = LOWORD(lParam);
			lButtonDownY = HIWORD(lParam);

			SetCapture(mainWindow);
			GetWindowRect(mainWindow, &mainRect);
		}
		break;
	case WM_LBUTTONUP:
		{
			wcscat_s(log, 10000, L"WM_LBUTTONUP ");
			SetWindowText(staticLog, log);

			lButtonDown = false;
			ReleaseCapture();
		}
		break;
	
	case WM_LBUTTONDBLCLK:
		{
			wcscat_s(log, 10000, L"WM_LBUTTONDBLCLK ");
			SetWindowText(staticLog, log);
		}
		break;
//	case WM_NCHITTEST:
//		{
//			wcscat_s(log, 10000, L"WM_NCHITTEST ");
//			SetWindowText(staticLog, log);
//		}
//		break;
	case WM_MOUSEMOVE: 
		if (lButtonDown) {
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			mainRect.left += LOWORD(lParam) - lButtonDownX;
			mainRect.top += HIWORD(lParam) - lButtonDownY;

			SetWindowPos(mainWindow, HWND_TOP, mainRect.left, mainRect.top, 0, 0, SWP_NOSIZE);

			lButtonDownX = LOWORD(lParam);
			lButtonDownY = HIWORD(lParam);
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

LPWSTR numToStr(int num) {
	int len = getLengthOfNum(num);
	LPWSTR newStr = new TCHAR[len + 1];
	_itot_s(num, newStr, len + 1, 10);
	return newStr;
}

bool isNumber(LPWSTR str) {
	if (str[0] == '\0')
		return false;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

int getLengthOfNum(int num) {
	if (num == 0)
		return 1;
	int len = 0;
	while (num != 0) {
		num /= 10;
		len++;
	}
	return len;
}
