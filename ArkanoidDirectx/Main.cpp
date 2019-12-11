#include "Window.h"

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    int windowWidth = 640;
    int windowHeight = 480;
    const auto pClassName = L"Game";

    //Create Window, handle message inside
    Window wnd(windowWidth, windowHeight, pClassName);


   // this struct holds Windows event messages
    MSG msg;
    BOOL gResult;
    // wait for the next message in the queue, store the result in 'msg'
    while ((gResult = GetMessage(&msg, NULL, 0, 0)) > 0)
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }
    
    if (gResult == -1)
    {
        return -1;
    }

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}