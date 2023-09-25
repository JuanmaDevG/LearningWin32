#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>


// WPARAM -> Word Parameter / LPARAM -> Long Paramteter (both pointer sized, 8 bytes)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_CLOSE:
        if(MessageBox(hwnd, L"Do you really wanna quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        return 0;
        break;
    case WM_PAINT:
        PAINTSTRUCT painter;
        HDC handle_device_control = BeginPaint(hwnd, &painter);

        //Painting opeartions

        FillRect(handle_device_control, &painter.rcPaint, (HBRUSH)(COLOR_WINDOW +1));
        EndPaint(hwnd, &painter);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam); //Default window procedure
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    wchar_t wclass_name[] = L"Sample Window Class";

    WNDCLASS my_wclass = {};
    my_wclass.lpfnWndProc = WindowProc;
    my_wclass.lpszClassName = wclass_name;
    my_wclass.hInstance = hInstance;
    
    RegisterClass(&my_wclass);

    //CreateWindowW or CreateWindowA are for reduced configuration versions
    //This is for create window with Extended Configuration
    HWND window_handle = CreateWindowEx(
        0, wclass_name, L"Asks before quit", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL
    );
    if(!window_handle) return 0;

    ShowWindow(window_handle, nCmdShow);

    MSG actual_message = {};
    while(GetMessage(&actual_message, window_handle, 0, 0))
    {
        TranslateMessage(&actual_message);  // Erase message header information
        DispatchMessage(&actual_message);   // Window procedure activation
    }

    return 0;
}

/*
    NOTE:
    WM_DESTROY sends means that the window has been actually destroyed and there is no window now, 
    the decision to close the program is to PostQuitMessage to end the window message loop
    
    WM_CLOSE gives the opportunity to something else before the window is actually destroyed, like to 
    put a message box to confirm or somehting before the window destruction
*/