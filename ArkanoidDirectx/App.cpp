#include "App.h"

App::App()
	:
	wnd(windowWidth, windowHeight, WindowName)
{

	game = std::make_unique<Game>(wnd.GetGfx(), wnd.GetKeyboardPointer(), boardWidth, boardHeight);
	keys = std::make_unique<KeyBinding>();

	wnd.GetGfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 100.0f));

	wnd.SetMenuState(Menu::GameState::Menu);
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
	switch (wnd.GetMenuState())
	{
	case  Menu::GameState::Menu:
		CheckInput();
		break;
	case  Menu::GameState::WaitingForPlayer:
		CheckServerStatus();
		break;
	case  Menu::GameState::JoiningServer:
		CheckServerStatus();
		break;
	case Menu::GameState::MultiGamePlay:
		DoMultiGameFrame();
		break;
	case  Menu::GameState::SingleGamePlay:
		DoSingleGameFrame();
		break;
	default:
		break;
	}

}

void App::DoMultiGameFrame()
{
	DoSingleGameFrame();
}

void App::DoSingleGameFrame()
{
	wnd.GetGfx().ClearBuffer(0.0, 0.2, 0.4);

	auto dt = timer.Mark();
	game->Update(dt, wnd.GetWindow());
	game->Draw(wnd.GetGfx());

	wnd.GetGfx().EndFrame();
}

void App::CheckInput()
{
	if (keys->CheckControlls(wnd.GetKeyboardPointer(), KeyBinding::Controlls::CreateServer))
	{
		if (server == nullptr)
		{
			server = std::make_unique<Server>(wnd.GetWindow());
		}

		std::string ip = server->CreateServer();
		wnd.SetIPAddress(ip);
		CopyStringToClipboard(ip);

		//autoconnect
		if (client == nullptr)
		{
			client = std::make_unique<Client>(wnd.GetWindow());
		}
		client->JoinServer(&(client->ci), ip);
		client->WaitForIPAddressAndRunServer();

		wnd.SetMenuState(Menu::GameState::WaitingForPlayer);
	}
	if (keys->CheckControlls(wnd.GetKeyboardPointer(), KeyBinding::Controlls::JoinServer))
	{
		if (client == nullptr)
		{
			client = std::make_unique<Client>(wnd.GetWindow());
		}
		wnd.ShowIPDialog(client->GetIPDialogProc());
		client->WaitForIPAddressAndRunServer();

		wnd.SetMenuState(Menu::GameState::JoiningServer);
	}
	if(keys->CheckControlls(wnd.GetKeyboardPointer(), KeyBinding::Controlls::StartGame))
	{
		wnd.SetMenuState(Menu::GameState::SingleGamePlay);
		timer.Mark();
		game->StartSingleGame(std::make_shared<BoardInfo>(), wnd.GetGfx());
	}
}

void App::CheckServerStatus()
{
	if (client->ci.gameStart)
	{
		std::shared_ptr<BoardInfo> pmypi, popi;
		pmypi = std::make_shared<BoardInfo>();
		popi = std::make_shared<BoardInfo>();
		pmypi->id = client->ci.playerID;
		popi->id = client->ci.playerID + 1 % 2;
		client->ci.pmypi = pmypi;
		client->ci.popi = popi;
		game->StartMultiGame(pmypi, popi, wnd.GetGfx());
		timer.Mark();
		wnd.SetMenuState(Menu::GameState::MultiGamePlay);
	}
}

void App::CopyStringToClipboard(const std::string& text)
{
	//OpenClipboard(0); Caused an exception when paste to join server IP dialog - now we unable to paste value there - but we prevented crash //TODO find somebody that can explain that!!!
	OpenClipboard(wnd.GetWindow());
	EmptyClipboard();
	SIZE_T size = text.size() + 1;
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, size);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), text.c_str(), size);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

