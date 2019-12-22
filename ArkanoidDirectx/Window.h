#pragma once
#include "Keyboard.h"
#include "Graphics.h"
#include "Menu.h"
#include "Server.h"
#include <optional>
#include <memory>
#include "resource.h"

class Window
{
public:
	friend class Server;

	Window(int width, int height, LPCSTR name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	static std::optional<int> ProcessMessages();
	
	void SetIPAddress(std::string ipaddress);
	void SetMenuState(Menu::GameState gameState);

	void ShowIPDialog(DLGPROC IPAdressproc);
	HWND GetWindow();

	Menu::GameState GetMenuState();
	Graphics& GetGfx();
	std::shared_ptr<Keyboard> GetKeyboardPointer();

	

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	int width;
	int height;
	std::unique_ptr<Graphics> pGfx;
	std::shared_ptr<Keyboard> kbd;
	std::shared_ptr<Menu> menu;
	HWND hWnd;
	HWND ipAdressDlg;

	class WindowClass
	{

	public:
		static const LPCSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const LPCSTR wndClassName = "Arkanoid";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
};