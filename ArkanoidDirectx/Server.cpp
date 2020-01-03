#include "Server.h"

#define PLAYER_COUNT 2

Server::Server(HWND hWnd)
{
    si.hWnd = hWnd;
}

Server::~Server()
{
    closesocket(si.ListenSocket);
    //TODO clenup threat and socet
    WSACleanup();
}

std::string Server::CreateServer()
{
    if (isCreate)
        return ipAddress;

    ServerInfo* pSI = &si;

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    struct ifaddrs* temp_addr = NULL;
    int iResult;
    std::string errorMessage;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        errorMessage = "WSAStartup failed with error: " + std::to_string(iResult);
        MessageBox(si.hWnd, errorMessage.c_str(), "Error", MB_OK);
        return false;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    std::vector<std::string> ipsAddress;
    GetIPAdress(&ipsAddress);

    for (int i = 0; i < ipsAddress.size(); i++)
    {
        if (MessageBox(si.hWnd, ("Your address IP is " + ipsAddress[i]).c_str(), "Error", MB_YESNO) == 6)
        {
            ipAddress = ipsAddress[i];
            break;
        }
    }

    if (ipAddress == "")
    {
        MessageBox(si.hWnd, "Cannot get IP address", "Error", MB_OK);
        return false;
    }

    // Resolve the server address and port
    iResult = getaddrinfo(ipAddress.c_str(), DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        errorMessage = "getaddrinfo failed with error: " + std::to_string(iResult);
        MessageBox(si.hWnd, errorMessage.c_str(), "Error", MB_OK);
        WSACleanup();
        return false;
    }

    SOCKET ListenSocket = INVALID_SOCKET;

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (ListenSocket == INVALID_SOCKET) {
        errorMessage = "Error at socket() " + std::to_string(WSAGetLastError());
        MessageBox(si.hWnd, errorMessage.c_str(), "Error", MB_OK);
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        errorMessage = "Bind failed with error " + std::to_string(WSAGetLastError());
        MessageBox(si.hWnd, errorMessage.c_str(), "Error", MB_OK);
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    freeaddrinfo(result);

    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        errorMessage = "Listen failed with error " + std::to_string(WSAGetLastError());
        MessageBox(si.hWnd, errorMessage.c_str(), "Error", MB_OK);
        closesocket(ListenSocket);
        WSACleanup();
        return false;
    }

    si.ListenSocket = ListenSocket;

    hRunThread = CreateThread(NULL, 0, RunServer, pSI, 0, &dwRunThreadId);

    isCreate = true;

    return ipAddress;
}

DWORD WINAPI Server::ConnectPlayer(void* parg)
{
    ServerInfo* psi = (ServerInfo*)parg;
    psi->serverRun = true;
    std::string errorMessage;
    // Accept a client socket
    while (psi->playerConnected < PLAYER_COUNT)
    {
        psi->ClientSockets[psi->playerConnected] = accept(psi->ListenSocket, NULL, NULL);
        if (psi->ClientSockets[psi->playerConnected] == INVALID_SOCKET) {
            errorMessage = "Accept failed: " + std::to_string(WSAGetLastError());
            MessageBox(psi->hWnd, errorMessage.c_str(), "Error", MB_OK);
            closesocket(psi->ListenSocket);
            WSACleanup();
            ExitProcess(2);
        }
        psi->playerConnected++;
    }
    // No longer need server socket
    //closesocket(psi->ListenSocket);

    return 0;
}

DWORD WINAPI Server::RunServer(void* parg)
{
    ServerInfo* psi = (ServerInfo*)parg;
    DWORD   dwConnectThreadId;
    HANDLE  hConnectThread;
    DWORD   dwReciveOneThreadId;
    HANDLE  hReciveOneThread;
    DWORD   dwReciveTwoThreadId;
    HANDLE  hReciveTwoThread;
    std::string errorMessage;

    hConnectThread = CreateThread(NULL, 0, ConnectPlayer, psi, 0, &dwConnectThreadId);

    if (hConnectThread == NULL)
    {
        std::string message = "Error: " + GetLastError();
        MessageBox(psi->hWnd, errorMessage.c_str(), "Error", MB_OK);
        return 1;
    }

    WaitForSingleObject(hConnectThread, INFINITE);

    CloseHandle(hConnectThread);

    psi->recivePlayer = 0;
    hReciveOneThread = CreateThread(NULL, 0, BounceMessage, psi, 0, &dwReciveOneThreadId);
    while (psi->recivePlayer == 0)
    {
        Sleep(10);
    }
    psi->recivePlayer = 1;
    hReciveTwoThread = CreateThread(NULL, 0, BounceMessage, psi, 0, &dwReciveTwoThreadId);
    while (psi->recivePlayer == 1)
    {
        Sleep(10);
    }


    psi->serverReady = true;
    std::string info;
    for (int i = 0; i < psi->playerConnected; i++)
    {
        info = std::to_string(i);
        int iSendResult = send(psi->ClientSockets[i], info.c_str(), (int)strlen(info.c_str()), 0);

        if (iSendResult == SOCKET_ERROR) {            
            errorMessage = "Send failed with error: " + std::to_string(WSAGetLastError());
            MessageBox(psi->hWnd, errorMessage.c_str(), "Error", MB_OK);
            closesocket(psi->ClientSockets[i]);
            WSACleanup();
            return 1;
        }
    }

    return 0;
}

DWORD WINAPI Server::BounceMessage(void* parg)
{
    ServerInfo* psi = (ServerInfo*)parg;
    std::string errorMessage;
    int iResult = 1;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int reciveP = psi->recivePlayer;
    int sendP = (reciveP + 1) % 2;
    psi->recivePlayer = -1;
    while (iResult > 0)
    {
        iResult = recv(psi->ClientSockets[reciveP], recvbuf, recvbuflen, 0);

        if (iResult == SOCKET_ERROR) {
            errorMessage = "Recive failed with error: " + std::to_string(WSAGetLastError());
            MessageBox(psi->hWnd, errorMessage.c_str(), "Error", MB_OK);
            closesocket(psi->ClientSockets[reciveP]);
            closesocket(psi->ClientSockets[sendP]);
            WSACleanup();
            return 1;
        }

        iResult = send(psi->ClientSockets[sendP], recvbuf, iResult, 0);

        if (iResult == SOCKET_ERROR) {
            errorMessage = "Send failed with error: " + std::to_string(WSAGetLastError());
            MessageBox(psi->hWnd, errorMessage.c_str(), "Error", MB_OK);
            closesocket(psi->ClientSockets[reciveP]);
            closesocket(psi->ClientSockets[sendP]);
            WSACleanup();
            return 1;
        }
    }
    return 0;
}

bool Server::ServerRun()
{
    return si.serverRun;
}

bool Server::ServerReady()
{
    return si.playerConnected == PLAYER_COUNT;
}

void Server::GetIPAdress(std::vector<std::string>* ipsAddress)
{
    ULONG outBufLen = 15000;
    PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, (outBufLen));
    IP_ADAPTER_ADDRESSES* adapter(NULL);

    auto ip = GetAdaptersAddresses(AF_INET,
        GAA_FLAG_SKIP_ANYCAST |
        GAA_FLAG_SKIP_MULTICAST |
        GAA_FLAG_SKIP_DNS_SERVER |
        GAA_FLAG_SKIP_FRIENDLY_NAME,
        NULL, pAddresses, &outBufLen);

    for (adapter = pAddresses; NULL != adapter; adapter = adapter->Next)
    {
        // Skip loopback adapters
        if (IF_TYPE_SOFTWARE_LOOPBACK == adapter->IfType)
        {
            continue;
        }

        // Parse all IPv4 and IPv6 addresses
        for (
            IP_ADAPTER_UNICAST_ADDRESS* address = adapter->FirstUnicastAddress;
            NULL != address;
            address = address->Next)
        {
            auto family = address->Address.lpSockaddr->sa_family;
            if (AF_INET == family)
            {
                // IPv4
                SOCKADDR_IN* ipv4 = reinterpret_cast<SOCKADDR_IN*>(address->Address.lpSockaddr);

                char str_buffer[INET_ADDRSTRLEN] = { 0 };
                inet_ntop(AF_INET, &(ipv4->sin_addr), str_buffer, INET_ADDRSTRLEN);
                //ipAddrs.mIpv4.push_back(str_buffer);
                std::string ret = str_buffer;
                ipsAddress->push_back(str_buffer);
                //return ret;
            }
        }
    }
}