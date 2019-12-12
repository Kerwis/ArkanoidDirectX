#pragma once
#include "Window.h"
#include "GameTimer.h"

class App
{
private:
	int windowWidth = 640;
	int windowHeight = 480;
	const LPCWSTR WindowName = L"Arkanoid";

public:
	App();
	
	//Start game loop
	int Go();
private:
	//main frame
	void DoFrame();
	Window wnd;
	GameTimer timer;
};