#pragma once
#include <Windows.h>
#include <string>

class Menu
{
public:
	enum class GameState
	{
		Menu,
		WaitingForPlayer,
		JoiningServer,
		MultiGamePlay,
		SingleGamePlay,
	};
	Menu(int width, int height);
	~Menu() = default;

	void Show(HWND hWnd);
	void SetState(GameState gameState);
	void SetIPAddress(std::string ipaddress);
	GameState GetState();
private:
	GameState gameState;
	int width;
	int height;
	std::string IPAddress;
	void ShowTitle(HDC hWnd); 
	void ShowOptions(HDC hWnd);
	void ShowJoiningServer(HDC hWnd);
	void ShowWaitForPlayer(HDC hWnd);
};
