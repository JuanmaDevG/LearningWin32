#include <stdio.h>
#include <windows.h>

/*
    This program manages application state by an information struct

    We're going to pass an array of three screen positions to our window program, 
    the program will modify them each time we ask to exit but we cancel the exit finally.

    Notes:
    WPARAM -> Word Parameter
    LPARAM -> Long Parameter

    The program information comes in lParam from the message when the window was created, and the first message 
    Dispatched to the queue was WM_CREATE, so the data pointer must be added to the Global Window Long Pointer User Data
    with the SetWindowLongPtr, and then later get it with GetWindowLongPtr.
    In case WM_CREATE the documentation has a bunch of unnecesary code, so I simplified it.
*/

struct Position {
    int x, y, z;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)lParam);    //Set the Global Window Long Pointer
        return 0;
    case WM_DESTROY:
        /* code */
        return 0;
    case WM_CLOSE:
        //Continue later
        return 0;
    case WM_PAINT:

        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdline, int nCmdShow)
{
    //Declaring positions
    Position* positions = new Position[3]{0,0,0};
    
    //Defining my window class
    wchar_t wclass_name[] = L"My Window Class";
    WNDCLASS window_class = {};
    window_class.lpfnWndProc = WindowProc;
    window_class.lpszClassName = wclass_name;
    window_class.hInstance = hInstance;

    //Register the window class
    RegisterClass(&window_class);

    //Defining the window handle (using my class)
    HWND hwnd = CreateWindowEx(
        0, wclass_name, L"Try to close many times", WS_OVERLAPPEDWINDOW, 
        //Coords
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        //More options
        NULL, NULL, hInstance, (void*)positions /*User parameters without relying on global variables*/
    );

    //Show the window to the screen
    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while(GetMessage(&msg, hwnd, 0, 0))
    {
        TranslateMessage(&msg);         //Removing header information
        DispatchMessage(&msg);          //Processing the message and sending info to the WindowProc
    }

    return 0;
}