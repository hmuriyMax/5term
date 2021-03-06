#include "stdafx.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

WCHAR button1Title[MAX_LOADSTRING];            
WCHAR button2Title[MAX_LOADSTRING];              
WCHAR editTitle[MAX_LOADSTRING];               
WCHAR staticTitle[MAX_LOADSTRING];             

HWND mainWindow;
HWND button1;
HWND button2;
HWND edit;
HWND staticOut;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void CALLBACK move(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_BUTTON1_TITLE, button1Title, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_BUTTON2_TITLE, button2Title, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_EDIT_TITLE, editTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_STATIC_TITLE, staticTitle, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   mainWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 1080, 720, nullptr, nullptr, hInstance, nullptr);

   HRGN windowRegion = CreateRectRgn(0, 0, 1080, 490);
   HRGN ellipseRegion = CreateEllipticRgn(0, 200, 1080, 720);
   HRGN circleRegion = CreateEllipticRgn(450, 250, 650, 450);

   CombineRgn(windowRegion, windowRegion, ellipseRegion, RGN_OR);
   CombineRgn(windowRegion, windowRegion, circleRegion, RGN_XOR);
   
   SetWindowRgn(mainWindow, windowRegion, true);



   button1 = CreateWindow(TEXT("BUTTON"), button1Title, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   250, 250, 170, 90, mainWindow, (HMENU)IDC_BUTTON1, hInstance, nullptr);

   button2 = CreateWindow(TEXT("BUTTON"), button2Title, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   660, 250, 170, 90, mainWindow, (HMENU)IDC_BUTTON2, hInstance, nullptr);

   edit = CreateWindow(TEXT("EDIT"), editTitle, WS_CHILD | WS_VISIBLE | ES_LEFT | WS_BORDER,
	   400, 100, 285, 30, mainWindow, (HMENU)IDC_EDIT1, hInstance, nullptr);

   staticOut = CreateWindow(TEXT("STATIC"), staticTitle, WS_CHILD | WS_VISIBLE | SS_LEFT,
	   400, 450, 285, 30, mainWindow, (HMENU)IDC_STATIC1, hInstance, nullptr);




   // Второй способ изменить координаты и размер
   //SetWindowPos(mainWindow, nullptr, 400, 400, 300, 300, 0);

   if (!mainWindow)
   {
      return FALSE;
   }

   ShowWindow(mainWindow, nCmdShow);
   UpdateWindow(mainWindow);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_SOMETHING:
				{
					SetWindowText(edit, TEXT("Menu item \"DoSomething\" clicked"));

					RECT rectButton;
					GetWindowRect(button1, &rectButton);
					
					SetParent(button1, GetDesktopWindow());
					SetWindowPos(button1, nullptr, rectButton.left, rectButton.top,
						rectButton.right - rectButton.left, rectButton.bottom - rectButton.top, 0);
					
					SetTimer(button1, IDT_BUTTON1_TIMER, 30, move);
				}
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDC_BUTTON1: 
				{
					int strSize = GetWindowTextLength(edit) + 1;
					LPWSTR str = new TCHAR[strSize];
					GetWindowText(edit, str, strSize);
					SetWindowText(staticOut, str);
				}
				break;
			case IDC_BUTTON2:
				{
					int strSize = GetWindowTextLength(mainWindow) + 1;
					LPWSTR str = new TCHAR[strSize];
					GetWindowText(mainWindow, str, strSize);
					SetWindowText(staticOut, str);
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		SetWindowText(edit, TEXT("Window created"));
		break;
	case WM_DESTROY:
		SetWindowText(edit, TEXT("Window destroyed"));
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		SetWindowText(edit, TEXT("Left mouse button pressed"));
		break;
	case WM_RBUTTONDOWN:
		{
			SetWindowText(edit, TEXT("Right mouse button pressed"));

			KillTimer(button1, IDT_BUTTON1_TIMER);
			SetParent(button1, mainWindow);
			RECT rect;
			GetWindowRect(button1, &rect);

			SetWindowPos(button1, nullptr, 250, 250,
				rect.right - rect.left, rect.bottom - rect.top, 0);
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void CALLBACK move(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	
	MoveWindow(hwnd, rect.left + 1, rect.top + 1,
		rect.right - rect.left, rect.bottom - rect.top, true);
}

// Message handler for about box.
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
