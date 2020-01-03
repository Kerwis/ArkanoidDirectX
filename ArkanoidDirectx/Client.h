#pragma once
#include "headers.h"
#include "Window.h"
#include "PlayerBoard.h"

class Client
{
public:
	Client(HWND hWnd);
	~Client() = default;
	Client(const Client&) = delete;
	Client& operator=(const Client&) = delete;

	struct ClientInfo
	{
		bool connected = false;
		bool gameStart = false;
		int playerID = -1;
		std::shared_ptr<BoardInfo> pmypi;
		std::shared_ptr<BoardInfo> popi;
		SOCKET ConnectSocket = INVALID_SOCKET;
		HWND hWnd;
	};
	void WaitForIPAddressAndRunServer();
	DLGPROC GetIPDialogProc();
	static bool JoinServer(ClientInfo* ci, std::string ipaddress);
	ClientInfo ci;
private:

	static DWORD WINAPI WaitAndRun(void* parg);
	static DWORD WINAPI WaitForIP(void* parg);
	static bool ipaddressloaded;
	static std::string ipaddress;
	static void SetIPAddress(TCHAR* ip);
	static int is_valid_ip(char* ip_str);
	static int valid_digit(char* ip_str);

	DWORD   dwRunThreadId = 0;
	HANDLE  hRunThread = nullptr;
	//ipget
	static INT_PTR CALLBACK IPAdressproc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};