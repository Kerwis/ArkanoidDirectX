#pragma once
#include "headers.h"
#include "Client.h"

#define MAX_PLAYERS 3

class Server
{
public:
	Server(HWND hWnd);
	~Server();
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;

	std::string CreateServer();
	bool ServerReady();
	bool ServerRun();

private:

	struct ServerInfo
	{
		int playerConnected = 0;
		bool serverRun = false;
		bool serverReady = false;
		int recivePlayer = -1;
		SOCKET ClientSockets[MAX_PLAYERS] = { INVALID_SOCKET, INVALID_SOCKET };
		SOCKET ListenSocket = INVALID_SOCKET;
		HWND hWnd;
	};

	std::string ipAddress = "";
	bool isCreate = false;
	ServerInfo si;

	const int maxPlayer = 2;

	static DWORD WINAPI ConnectPlayer(void * parg);
	static DWORD WINAPI RunServer(void* parg);
	static DWORD WINAPI BounceMessage(void* parg);
	void GetIPAdress(std::vector<std::string>* ipsAddress);
	
	HWND hWnd;

	DWORD   dwRunThreadId;
	HANDLE  hRunThread;
};