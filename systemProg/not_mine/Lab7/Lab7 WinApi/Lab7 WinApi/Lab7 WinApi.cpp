#include "stdafx.h"
#include "Lab7 WinApi.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HBITMAP hBmp1, hBmp2;
HWND button1, button2, button3, mainWindow;
WCHAR button1Title[MAX_LOADSTRING], button2Title[MAX_LOADSTRING], button3Title[MAX_LOADSTRING];

int k = 0;
int i = -400;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK drawAnimatedBitmap(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime);
void createMetaFile();

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
    LoadStringW(hInstance, IDC_LAB7WINAPI, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON1_TITLE, button1Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON2_TITLE, button2Title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDS_BUTTON3_TITLE, button3Title, MAX_LOADSTRING);

	hBmp1 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	hBmp2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));

    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB7WINAPI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB7WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB7WINAPI);
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
      200, 100, 600, 500, nullptr, nullptr, hInstance, nullptr);

   button1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button1Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
							80, 412, 80, 25, mainWindow, (HMENU)IDC_BUTTON1, hInstance, nullptr);
   button2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button2Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
							80 + 90, 412, 80, 25, mainWindow, (HMENU)IDC_BUTTON2, hInstance, nullptr);
   button3 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("BUTTON"), button3Title, WS_BORDER | WS_VISIBLE | WS_CHILD,
							80 + 180, 412, 80, 25, mainWindow, (HMENU)IDC_BUTTON3, hInstance, nullptr);


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
				SetTimer(mainWindow, 322, 10, &drawAnimatedBitmap);
			}	
			break;
			case IDC_BUTTON2:
			{
				createMetaFile();
			}	
			break;
			case IDC_BUTTON3:
			{
				RECT rect = { 0, 0, 600, 500 };
				InvalidateRect(hWnd, &rect, true);
				KillTimer(mainWindow, 322);
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


VOID CALLBACK drawAnimatedBitmap(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime) {
	HDC hdc = GetDC(mainWindow);
	HDC compatibleDC = CreateCompatibleDC(hdc);

	SelectObject(compatibleDC, hBmp1); //Выбирает объект картинку
	BitBlt(hdc, 0, 0, 500, 500, compatibleDC, 0, 0, SRCCOPY); //Помещает картинку на экран
												   
	SelectObject(compatibleDC, hBmp2); //Выбирает объект картинку
	
	if (i == 600) {
		i = -400;
		k = 0;
	}
	if (400 + i <= 500) {
		BitBlt(hdc, i, 280, 400, 120, compatibleDC, 0, 0, SRCCOPY);
		i += 5;
	} else {
		k += 5;
		BitBlt(hdc, i, 280, 400 - k, 120, compatibleDC, 0, 0, SRCCOPY);
		i += 5;
	}
	ReleaseDC(mainWindow, hdc);
	DeleteDC(compatibleDC); //удаляем из памяти контекст
}


void createMetaFile() {
	HDC MetaDC;
	MetaDC = CreateMetaFile(L"test.wmf");
	if (MetaDC != NULL) {
		HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		SelectObject(MetaDC, hpen);
		Ellipse(MetaDC, 100, 0, 200, 100);
		Rectangle(MetaDC, 0, 0, 100, 100);
	}
	CloseMetaFile(MetaDC);
}
