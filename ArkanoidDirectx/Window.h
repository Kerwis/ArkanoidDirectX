#pragma once
#include <windows.h>    // include the basic windows header file
#include <windowsx.h>
#include "Keyboard.h"
#include <optional>

class Window
{
public:
	Window(const Window&) = delete;
	Window(int width, int height, LPCWSTR name) noexcept;
	~Window();
	static std::optional<int> ProcessMessages();
	Window& operator=(const Window&) = delete;
	Keyboard kbd;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	int width;
	int height;
	HWND hWnd;

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