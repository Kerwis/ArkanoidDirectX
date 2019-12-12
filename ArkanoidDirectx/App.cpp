#include "App.h"

App::App()
	:
	wnd(windowWidth, windowHeight, WindowName)
{}

int App::Go()
{
	while (true)
	{
		//process messages
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	wnd.Gfx().EndFrame();
}
