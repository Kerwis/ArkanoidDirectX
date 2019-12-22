#include "Window.h"

Window::Window(int width, int height,LPCSTR name) noexcept
    :
    width(width),
    height(height)
{

    RECT wr = { 0, 0, width, height };   
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
        WindowClass::GetName(),    // name of the window class
        name,   // title of the window
        WS_OVERLAPPEDWINDOW,    // window style
        100,    // x-position of the window
        100,    // y-position of the window
        wr.right - wr.left,    // width of the window
        wr.bottom - wr.top,    // height of the window
        NULL, NULL, //Not used
        WindowClass::GetInstance(),    // application handle
        this);

    // newly created windows start off as hidden
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    // create graphics object
    pGfx = std::make_unique<Graphics>(hWnd, width, height);
    kbd = std::make_shared<Keyboard>();
    menu = std::make_unique<Menu>(width, height);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    //Get pointer
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd-> HandleMsg(hWnd, msg, wParam, lParam);
}

std::optional<int> Window::ProcessMessages()
{
    // this struct holds Windows event messages
    MSG msg;
    // wait for the next message in the queue, store the result in 'msg'
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        // check quit signal
        if (msg.message == WM_QUIT)
        {
            return msg.wParam;
        }

        // translate keystroke messages into the right format
        TranslateMessage(&msg);
        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    return {};
}

void Window::SetIPAddress(std::string ipaddress)
{
    menu->SetIPAddress(ipaddress);
}

void Window::SetMenuState(Menu::GameState gameState)
{
    menu->SetState(gameState);
    //menu->Show(hWnd);
    RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
    //bool repaint = UpdateWindow(hWnd);
}

Menu::GameState Window::GetMenuState()
{
    return menu->GetState();
}

Graphics& Window::GetGfx()
{
    return *pGfx;
}

std::shared_ptr<Keyboard> Window::GetKeyboardPointer()
{
    return kbd;
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // sort through and find what code to run for the message given
    switch (msg)
    {
        // this message is read when the window is closed
    case WM_DESTROY:

        // close the application entirely
        PostQuitMessage(0);
        return 0;
        break;
    case WM_PAINT:
        menu->Show(hWnd);
        break;
    case WM_KILLFOCUS:
        kbd->Reset();
            break;
    case WM_KEYDOWN:
        //After hold key autorepete prevent (optional)
        if (!(lParam & 0x40000000))//mask for bit 30
        {
            kbd->OnKeyPressed(static_cast<unsigned char>(wParam));
        }
        break;
    case WM_KEYUP:
        kbd->OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc(hWnd, msg, wParam, lParam);
}  

void Window::ShowIPDialog(DLGPROC IPAdressproc)
{
    ipAdressDlg = CreateDialog(WindowClass::GetInstance(), MAKEINTRESOURCE(IDD_DIALOGBAR), hWnd, IPAdressproc);
    ShowWindow(ipAdressDlg, SW_SHOW);
}

HWND Window::GetWindow()
{
    return hWnd;
}

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:hInst(GetModuleHandle(nullptr))
{
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();
    wc.hCursor = nullptr;
    wc.hIcon = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = nullptr;

    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

const LPCSTR Window::WindowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}