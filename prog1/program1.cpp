#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


/*
    Parameters:
     - hInstance: instance handler of the program tha contains program necessary information
     - hPrevInstance: intuitive but legacy stuff and should be zero
     - pCmdLine: a pointer to a wide string that contains the command line arguments
     - nCmdShow: an integer with flags that contain information about how to show the window
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    //Register c++ window class

    const wchar_t w_class_name[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = w_class_name;

    RegisterClass(&wc);

    //Creating the window

    HWND hwnd = CreateWindowEx(
        0,                          //Optional window styles
        w_class_name,               //Previously registered (in a class package) class name
        L"My first window",         //The window title (name)
        WS_OVERLAPPEDWINDOW,        //Window style

        //Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 

        NULL,                       //Parent window
        NULL,                       //Menu (any?)
        hInstance,                  //Instance handle (of this program)
        NULL                        //Additional application paramteters
    );

    if(!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow); //Show the window and detail show flags

    //Run the message loop (the shown window receives messages from the user input)

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0) > 0) //There is message
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //WM -> Window Message
    switch(uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        PAINTSTRUCT window_painter;
        HDC hdc = BeginPaint(hwnd, &window_painter);

        //All painting operations between BeginPaint and EndPaint

        FillRect(hdc, &window_painter.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

        EndPaint(hwnd, &window_painter);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}