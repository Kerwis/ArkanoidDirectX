#pragma once
#include <windows.h>    // include the basic windows header file
#include <windowsx.h>
#include "Keyboard.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window
{
public:
	Window(int width, int height, LPCWSTR name) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	static std::optional<int> ProcessMessages();
	
	Graphics& Gfx();
	std::shared_ptr<Keyboard> GetKeyboardPointer();

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
	std::shared_ptr<Keyboard> kbd;

	class WindowClass
	{

	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;

	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const LPCWSTR wndClassName = L"Arkanoid";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
};