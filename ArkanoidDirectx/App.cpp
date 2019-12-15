#include "App.h"
#include "Player.h"

App::App()
	:
	wnd(windowWidth, windowHeight, WindowName)
{

	game = std::make_unique<Game>(wnd.Gfx(), wnd.GetKeyboardPointer());

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

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
	wnd.Gfx().ClearBuffer(0.0, 0.2, 0.4);

	auto dt = timer.Mark();
	game->Update(dt);
	game->Draw(wnd.Gfx());

	wnd.Gfx().EndFrame();
}
