#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator= (const Keyboard&) = delete;

	//key
	bool KeyIsPressed(unsigned char keycode) const noexcept;
	void Reset();
private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;

	static constexpr unsigned int nKeys = 256u;
	std::bitset<nKeys> keyStates;
};

