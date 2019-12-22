#pragma once
#include "Player.h"
#include "Window.h"
#include "GameTimer.h"
#include "Game.h"
#include "KeyBinding.h"
#include "Server.h"
#include "Client.h"

class App
{
private:
	int windowWidth = 800;
	int windowHeight = 600;
	const LPCSTR WindowName = "Arkanoid";

public:
	App();
	~App() = default;
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	//Start game loop
	int Go();
private:


	//main frame
	void DoFrame();
	void DoMultiGameFrame();
	void DoSingleGameFrame();
	void CheckInput();
	void CheckServerStatus();
	void CopyStringToClipboard(const std::string &text);
	Window wnd;
	std::unique_ptr<Game> game;
	std::unique_ptr<KeyBinding> keys;
	std::unique_ptr<Server> server;
	std::unique_ptr<Client> client;
	GameTimer timer;
};