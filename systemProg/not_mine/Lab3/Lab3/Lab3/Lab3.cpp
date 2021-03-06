#include "stdafx.h"
#include "Lab3.h"

#define _CRT_SECURE_NO_WARNINGS

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

WCHAR hideWindowsButtonTitle[MAX_LOADSTRING];
WCHAR blockLab2ButtonTitle[MAX_LOADSTRING];
WCHAR blockBorlandButtonTitle[MAX_LOADSTRING];
WCHAR blockCsButtonTitle[MAX_LOADSTRING];
WCHAR unblockButtonTitle[MAX_LOADSTRING];
WCHAR closeCsWindowButtonTitle[MAX_LOADSTRING];

WCHAR pressLab2ButtonTitle[MAX_LOADSTRING];
WCHAR pressLab2AboutButtonTitle[MAX_LOADSTRING];
WCHAR pressLab2RButtonTitle[MAX_LOADSTRING];
WCHAR moveLab2WindowButtonTitle[MAX_LOADSTRING];
WCHAR renameLab2WindowsButtonTitle[MAX_LOADSTRING];
WCHAR renameAllWindowsButtonTitle[MAX_LOADSTRING];


HWND mainWindow;
HWND hideWindowsButton;
HWND blockLab2Button;
HWND blockBorlandButton;
HWND blockCsButton;
HWND unblockButton;
HWND closeCsWindowButton;

HWND pressLab2Button;
HWND pressLab2AboutButton;
HWND pressLab2RButton;
HWND moveLab2WindowButton;
HWND renameLab2WindowsButton;
HWND renameAllWindowsButton;

HWND staticBox;

int windowNumber = 1;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void changeWindowVisibleState(HWND handle);
BOOL CALLBACK renameLab2Windows(HWND hwnd, LPARAM lParam);
BOOL CALLBACK renameWindow(HWND hwnd, LPARAM lParam);
BOOL CALLBACK renameChildWindows(HWND hwnd, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    LoadStringW(hInstance, HIDE_WINDOWS_BUTTON_TITLE, hideWindowsButtonTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, BLOCK_LAB2_BUTTON_TITLE, blockLab2ButtonTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, BLOCK_BORLAND_BUTTON_TITLE, blockBorlandButtonTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, BLOCK_CS_BUTTON_TITLE, blockCsButtonTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, UNBLOCK_BUTTON_TITLE, unblockButtonTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, CLOSE_CS_BUTTON_TITLE, closeCsWindowButtonTitle, MAX_LOADSTRING);

	LoadStringW(hInstance, PRESS_LAB2_BUTTON_TITLE, pressLab2ButtonTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, PRESS_LAB2_ABOUT_BUTTON_TITLE, pressLab2AboutButtonTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, PRESS_LAB2_RBUTTON_TITLE, pressLab2RButtonTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, MOVE_LAB2_WINDOW_BUTTON_TITLE, moveLab2WindowButtonTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, RENAME_LAB2_WINDOWS_BUTTON_TITLE, renameLab2WindowsButtonTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, RENAME_ALL_WINDOWS_BUTTON_TITLE, renameAllWindowsButtonTitle, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr); 
   hideWindowsButton = CreateWindow(L"BUTTON", hideWindowsButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  100, 50, 600, 40, mainWindow, (HMENU)HIDE_WINDOWS_BUTTON, hInstance, nullptr);
   blockLab2Button = CreateWindow(L"BUTTON", blockLab2ButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  100, 100, 190, 40, mainWindow, (HMENU)BLOCK_LAB2_BUTTON, hInstance, nullptr);
   blockBorlandButton = CreateWindow(L"BUTTON", blockBorlandButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  305, 100, 190, 40, mainWindow, (HMENU)BLOCK_BORLAND_BUTTON, hInstance, nullptr);
   blockCsButton = CreateWindow(L"BUTTON", blockCsButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  510, 100, 190, 40, mainWindow, (HMENU)BLOCK_CS_BUTTON, hInstance, nullptr);
   unblockButton = CreateWindow(L"BUTTON", unblockButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  715, 100, 190, 40, mainWindow, (HMENU)UNBLOCK_BUTTON, hInstance, nullptr);
   closeCsWindowButton = CreateWindow(L"BUTTON", closeCsWindowButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  100, 150, 600, 40, mainWindow, (HMENU)CLOSE_CS_BUTTON, hInstance, nullptr);

   pressLab2Button = CreateWindow(L"BUTTON", pressLab2ButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   100, 250, 250, 40, mainWindow, (HMENU)PRESS_LAB2_BUTTON, hInstance, nullptr);
   pressLab2AboutButton = CreateWindow(L"BUTTON", pressLab2AboutButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   365, 250, 250, 40, mainWindow, (HMENU)PRESS_LAB2_ABOUT_BUTTON, hInstance, nullptr);
   pressLab2RButton = CreateWindow(L"BUTTON", pressLab2RButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   630, 250, 250, 40, mainWindow, (HMENU)PRESS_LAB2_RBUTTON, hInstance, nullptr);
   moveLab2WindowButton = CreateWindow(L"BUTTON", moveLab2WindowButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   100, 300, 250, 40, mainWindow, (HMENU)MOVE_LAB2_WINDOW_BUTTON, hInstance, nullptr);
   renameLab2WindowsButton = CreateWindow(L"BUTTON", renameLab2WindowsButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   365, 300, 250, 40, mainWindow, (HMENU)RENAME_LAB2_WINDOWS_BUTTON, hInstance, nullptr);
   renameAllWindowsButton = CreateWindow(L"BUTTON", renameAllWindowsButtonTitle, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   630, 300, 250, 40, mainWindow, (HMENU)RENAME_ALL_WINDOWS_BUTTON, hInstance, nullptr);

   staticBox = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE,
		  100, 400, 600, 50, mainWindow, (HMENU)STATIC_BOX, hInstance, nullptr);


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
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case HIDE_WINDOWS_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					HWND borlandWindow = FindWindow(NULL, _T("borland"));
					HWND csWindow = FindWindow(NULL, _T("cs"));

					if (lab2Window)
						changeWindowVisibleState(lab2Window);
					if (borlandWindow)
						changeWindowVisibleState(borlandWindow);
					if (csWindow)
						changeWindowVisibleState(csWindow);
				}	
				break;
			case BLOCK_LAB2_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					if (lab2Window) {
						SetWindowText(staticBox, _T("Захвачено окно Lab2"));
						EnableWindow(lab2Window, false);
					}
					else
						SetWindowText(staticBox, _T("Не удалось захватить окно Lab2"));
				}
				break;
			case BLOCK_BORLAND_BUTTON:
				{
					HWND borlandWindow = FindWindow(NULL, _T("borland"));
					if (borlandWindow) {
						SetWindowText(staticBox, _T("Захвачено окно borland"));
						EnableWindow(borlandWindow, false);
					}
					else
						SetWindowText(staticBox, _T("Не удалось захватить окно borland"));
				}
				break;
			case BLOCK_CS_BUTTON:
				{
					HWND cs = FindWindow(NULL, _T("cs"));
					if (cs) {
						SetWindowText(staticBox, _T("Захвачено окно cs"));
						EnableWindow(cs, false);
					}
					else
						SetWindowText(staticBox, _T("Не удалось захватить окно cs"));
				}
				break;
			case UNBLOCK_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					HWND borlandWindow = FindWindow(NULL, _T("borland"));
					HWND cs = FindWindow(NULL, _T("cs"));
					if (lab2Window)
						EnableWindow(lab2Window, true);
					if (borlandWindow)
						EnableWindow(borlandWindow, true);
					if (cs)
						EnableWindow(cs, true);
					SetWindowText(staticBox, _T("Все окна разблокированы"));
				}
				break;
			case CLOSE_CS_BUTTON:
				{
					HWND cs = FindWindow(NULL, _T("cs"));
					if (cs)
						SendMessage(cs, WM_DESTROY, 0, 0);
				}
				break;
			case PRESS_LAB2_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					if (lab2Window) {
						HWND button1 = FindWindowEx(lab2Window, NULL, 0, _T("Button1"));
						if (button1) {
							SendMessage(button1, WM_LBUTTONDOWN, 0, 0);
							Sleep(100);
							SendMessage(button1, WM_LBUTTONUP, 0, 0);
						}
					}
				}
				break;
			case PRESS_LAB2_ABOUT_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					if (lab2Window) {
						SendMessage(lab2Window, WM_COMMAND, IDM_ABOUT, 0);
					}
				}
				break;
//			case PRESS_LAB2_RBUTTON:
//				{
//					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
//					if (lab2Window) {
//						SendMessage(lab2Window, WM_RBUTTONDOWN, 0, 0);
//						SendMessage(lab2Window, WM_RBUTTONUP, 0, 0);
//					}
//				}
//				break;
//			case MOVE_LAB2_WINDOW_BUTTON:
//				{
//					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
//					if (lab2Window) {
//						SendMessage(lab2Window, WM_LBUTTONDOWN, 0, 0);
//						SetCursorPos(800, 800);
//						SendMessage(lab2Window, WM_MOUSEMOVE, 0, 0);
//						SendMessage(lab2Window, WM_LBUTTONUP, 0, 0);
//					}
//				}
//				break;
			case RENAME_LAB2_WINDOWS_BUTTON:
				{
					HWND lab2Window = FindWindow(NULL, _T("Lab2"));
					if (lab2Window) {
						EnumChildWindows(lab2Window, &renameLab2Windows, 0);
					}
				}
				break;
			case RENAME_ALL_WINDOWS_BUTTON:
				{
					EnumWindows(&renameWindow, 0);
				}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_RBUTTONDOWN:
		{
			HWND lab2Window = FindWindow(NULL, _T("Lab2"));
			if (lab2Window) {
				SendMessage(lab2Window, WM_RBUTTONDOWN, wParam, lParam);
			}
		}
		break;
	case WM_RBUTTONUP:
		{
			HWND lab2Window = FindWindow(NULL, _T("Lab2"));
			if (lab2Window) {
				SendMessage(lab2Window, WM_RBUTTONUP, wParam, lParam);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			HWND lab2Window = FindWindow(NULL, _T("Lab2"));
			if (lab2Window) {
				SendMessage(lab2Window, WM_LBUTTONDOWN, wParam, lParam);
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			HWND lab2Window = FindWindow(NULL, _T("Lab2"));
			if (lab2Window) {
				SendMessage(lab2Window, WM_LBUTTONUP, wParam, lParam);
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			HWND lab2Window = FindWindow(NULL, _T("Lab2"));
			if (lab2Window) {
				SendMessage(lab2Window, WM_MOUSEMOVE, wParam, lParam);
			}
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
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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

void changeWindowVisibleState(HWND handle) {
	if (IsWindowVisible(handle))
		ShowWindow(handle, 0);
	else
		ShowWindow(handle, 5);
}

BOOL CALLBACK renameLab2Windows(HWND hwnd, LPARAM lParam) {
	SendMessage(hwnd, WM_SETTEXT, 0, LPARAM(LPCSTR(_T("Renamed"))));
	return TRUE;
}

BOOL CALLBACK renameWindow(HWND hwnd, LPARAM lParam) {
	TCHAR parentLabel[MAX_LOADSTRING] = _T("window");
	TCHAR number[MAX_LOADSTRING];
	_itot(windowNumber, number, 10);
	_tcscat(parentLabel, number);
	windowNumber++;
	SendMessage(hwnd, WM_SETTEXT, 0, LPARAM(LPCSTR(parentLabel)));
	EnumChildWindows(hwnd, &renameChildWindows, 0);
	return TRUE;
}

BOOL CALLBACK renameChildWindows(HWND hwnd, LPARAM lParam) {
	TCHAR parentLabel[MAX_LOADSTRING] = _T("child");
	TCHAR number[MAX_LOADSTRING];
	_itot(windowNumber, number, 10);
	_tcscat(parentLabel, number);
	windowNumber++;
	SendMessage(hwnd, WM_SETTEXT, 0, LPARAM(LPCSTR(parentLabel)));
	EnumChildWindows(hwnd, &renameChildWindows, 0);
	return TRUE;
}
