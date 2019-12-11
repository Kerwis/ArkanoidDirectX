#pragma once
#include "Window.h"
#include "GameTimer.h"

class App
{
public:
	App();
	
	//Start game loop
	int Go();
private:
	//main frame
	void DoFrame();
	Window wnd;
	GameTimer timer;

	int windowWidth = 640;
	int windowHeight = 480;
	const LPCWSTR pClassName = L"Game";
};