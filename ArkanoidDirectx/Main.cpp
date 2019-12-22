#include "App.h"
#include <comdef.h>

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
    try 
    {
        return App{}.Go();
    }
    catch (const _com_error & e)
    {
        MessageBox(nullptr, e.Source(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (std::exception& e)
    {
        MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "Upss", "Unknow Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
}