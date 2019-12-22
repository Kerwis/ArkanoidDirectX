#include "Client.h"
#define DELIM "." 

Client::Client(HWND hWnd)
{
    ci.hWnd = hWnd;
}

void Client::WaitForIPAddressAndRunServer()
{
    hRunThread = CreateThread(NULL, 0, WaitAndRun, &ci, 0, &dwRunThreadId);
}

DLGPROC Client::GetIPDialogProc()
{
    return IPAdressproc;
}

DWORD WINAPI Client::WaitAndRun(void* parg)
{
    ClientInfo* ci = (ClientInfo*)parg;
    if (!(ci->connected))
    {
        DWORD   dwIPThreadId;
        HANDLE  hIPThread;
        hIPThread = CreateThread(NULL, 0, WaitForIP, ci, 0, &dwIPThreadId);
        WaitForSingleObject(hIPThread, INFINITE);
        //Close wait for ip thread
        CloseHandle(hIPThread);
    }
    
    int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    iResult = recv(ci->ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0)// can be iResult == 1 but it stop work with more than 10 player (0-9)
    {
        ci->playerID = std::stoi(recvbuf);
        ci->gameStart = true;
    }
    else
    {
        std::string errorMessage = "Error when recive init message: " + std::to_string(iResult);
        MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
    }

    while (ci->popi == nullptr)
    {
        Sleep(100);
    }
    std::string message;
    while (iResult > 0)
    {
        //TODO add timeout for repete message
        message = std::to_string(ci->pmypi->playerPosition.x) + ";" + std::to_string(ci->pmypi->ballPosition.x) + ";" + std::to_string(ci->pmypi->ballPosition.y) + ";";
        
        iResult = send(ci->ConnectSocket, message.c_str(), recvbuflen, 0);
        //TODO Handle errors
        iResult = recv(ci->ConnectSocket, recvbuf, recvbuflen, 0);
        //TODO Handle errors

        char* ptr;
        char* next_token = NULL;

        ptr = strtok_s(recvbuf, ";", &next_token);
        ci->popi->playerPosition.x = std::stof(ptr);

        ptr = strtok_s(NULL, ";", &next_token);
        ci->popi->ballPosition.x = std::stof(ptr);

        ptr = strtok_s(NULL, ";", &next_token);
        ci->popi->ballPosition.y = std::stof(ptr) * -1;
    }

    return 0;
}

DWORD WINAPI Client::WaitForIP(void* parg)
{
    ClientInfo* ci = (ClientInfo*)parg;
    while (!Client::ipaddressloaded)
    {
        Sleep(100);
    }
    JoinServer(ci, Client::ipaddress);
    return 0;
}

bool Client::JoinServer(ClientInfo* ci, std::string ipaddress)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    std::string errorMessage;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        errorMessage = "WSAStartup failed with error: " + std::to_string(iResult);
        MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
        return 1;
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(Client::ipaddress.c_str(), DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        errorMessage = "Getaddrinfo failed with error: " + std::to_string(iResult);
        MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
        WSACleanup();
        return 1;
    }
    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            errorMessage = "Socket failed with error: " + std::to_string(WSAGetLastError());
            MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
            WSACleanup();
            return 1;
        }
        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            errorMessage = "Connect failed with error: " + std::to_string(WSAGetLastError());
            MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        errorMessage = "Unable to connect to server!";
        MessageBox(ci->hWnd, errorMessage.c_str(), "Error", MB_OK);
        WSACleanup();
        return 1;
    }
    
    ci->ConnectSocket = ConnectSocket;
    ci->connected = true;

	return true;
}

bool Client::ipaddressloaded = false;
std::string Client::ipaddress = "";

void Client::SetIPAddress(TCHAR* ip)
{
    Client::ipaddress = ip;
    Client::ipaddressloaded = true;
}

INT_PTR CALLBACK Client::IPAdressproc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR lpszIPAdress[16];
    WORD cchIPAdress;

    switch (message)
    {
    case WM_INITDIALOG:
        // Set password character to a plus sign (+) 
        //SendDlgItemMessage(hDlg, IDC_EDIT1, EM_SETPASSWORDCHAR, (WPARAM)'+', (LPARAM)0);

        // Set the default push button to "Cancel." 
        SendMessage(hDlg,
            DM_SETDEFID,
            (WPARAM)IDCANCEL,
            (LPARAM)0);

        return TRUE;

    case WM_COMMAND:
        // Set the default push button to "OK" when the user enters text. 
        if (HIWORD(wParam) == EN_CHANGE &&
            LOWORD(wParam) == IDC_EDIT1)
        {
            SendMessage(hDlg,
                DM_SETDEFID,
                (WPARAM)IDOK,
                (LPARAM)0);
        }
        switch (wParam)
        {
        case IDOK:
            // Get number of characters. 
            cchIPAdress = (WORD)SendDlgItemMessage(hDlg,
                IDC_EDIT1,
                EM_LINELENGTH,
                (WPARAM)0,
                (LPARAM)0);
            if (cchIPAdress >= 16)
            {
                MessageBox(hDlg,
                    "Too many characters.",
                    "Error",
                    MB_OK);

                EndDialog(hDlg, TRUE);
                return FALSE;
            }
            else if (cchIPAdress == 0)
            {
                MessageBox(hDlg,
                    "No characters entered.",
                    "Error",
                    MB_OK);

                EndDialog(hDlg, TRUE);
                return FALSE;
            }

            // Put the number of characters into first word of buffer. 
            *((LPWORD)lpszIPAdress) = cchIPAdress;

            // Get the characters. 
            SendDlgItemMessage(hDlg,
                IDC_EDIT1,
                EM_GETLINE,
                (WPARAM)0,       // line 0 
                (LPARAM)lpszIPAdress);

            // Null-terminate the string. 
            lpszIPAdress[cchIPAdress] = 0;

            //Valid
            //if (is_valid_ip(lpszIPAdress) == 0)
            {
                //MessageBox(hDlg,
                //    lpszIPAdress,
                //    "IP not valid",
                //    MB_OK);
                //return FALSE;
            }
            //Set IP Address
            SetIPAddress(lpszIPAdress);

            EndDialog(hDlg, TRUE);
            return TRUE;

        case IDCANCEL:
            EndDialog(hDlg, TRUE);
            return TRUE;
        }
        return 0;
    }
    return FALSE;

    UNREFERENCED_PARAMETER(lParam);
}

/* return 1 if string contain only digits, else return 0 */
int Client::valid_digit(char* ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}

/* return 1 if IP string is valid, else return 0 */
int Client::is_valid_ip(char* ip_str)
{
    int i, num, dots = 0;
    char* ptr;
    char* next_token=NULL;

    if (ip_str == NULL)
        return 0;

    ptr = strtok_s(ip_str, DELIM, &next_token);

    if (ptr == NULL)
        return 0;

    while (ptr) {

        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr))
            return 0;

        num = atoi(ptr);

        /* check for valid IP */
        if (num >= 0 && num <= 255) {
            /* parse remaining string */
            ptr = strtok_s(NULL, DELIM, &next_token);
            if (ptr != NULL)
                ++dots;
        }
        else
            return 0;
    }

    /* valid IP string must contain 3 dots */
    if (dots != 3)
        return 0;
    return 1;
}