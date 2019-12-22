#include "Menu.h"

Menu::Menu(int width, int height)
    :width(width), height(height)
{
}

void Menu::Show(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    RECT rect;
    GetWindowRect(hWnd, &rect);
    COLORREF color = RGB(0, 50, 100);
    HBRUSH hbrush = CreateSolidBrush(color);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkColor(hdc, color);
    SelectObject(hdc, hbrush);


    Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    ShowTitle(hdc);

    switch (gameState)
    {
    case Menu::GameState::Menu:
        ShowOptions(hdc);
        break;
    case Menu::GameState::WaitingForPlayer:
        ShowWaitForPlayer(hdc);
        break;
    case Menu::GameState::JoiningServer:
        ShowJoiningServer(hdc);
        break;
    default:
        break;
    }

    
    EndPaint(hWnd, &ps);
}

void Menu::SetState(GameState newGameState)
{
    gameState = newGameState;
}

void Menu::SetIPAddress(std::string ipaddress)
{
    IPAddress = ipaddress;
}

Menu::GameState Menu::GetState()
{
    return gameState;
}


void Menu::ShowTitle(HDC hdc)
{
    LPCSTR myMessage = "Arkanoid";

    //Title
    TextOut(hdc,
        // Location of the text
        width / 2 - 15,
        50,
        // Text to print
        myMessage,
        // Size of the text
        strlen(myMessage));

}

void Menu::ShowOptions(HDC hdc)
{
    LPCSTR myMessage = "1 - create server\r\n2 - join Server";
    RECT rc;
    SetRect(&rc, 50, 100, width - 50, height - 100);
    DrawText(hdc, myMessage, strlen(myMessage), &rc, DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
}

void Menu::ShowJoiningServer(HDC hdc)
{
    std::string myMessage = "Joining server...";
    RECT rc;
    SetRect(&rc, 50, 100, width - 50, height - 100);
    DrawText(hdc, myMessage.c_str(), strlen(myMessage.c_str()), &rc, DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
}

void Menu::ShowWaitForPlayer(HDC hdc)
{
    std::string myMessage = "Waiting for player.\n\nYour IP is " + IPAddress + "\n\nIt's copied to your clipboard!";
    RECT rc;
    SetRect(&rc, 50, 100, width - 50, height - 100);
    DrawText(hdc, myMessage.c_str(), strlen(myMessage.c_str()), &rc, DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
}
