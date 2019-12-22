#pragma once
#include "Keyboard.h"
#include <memory>

class KeyBinding
{
public:
	enum class Controlls
	{
		CreateServer,
		JoinServer,
		StartGame,
	};

	KeyBinding() = default;
	~KeyBinding() = default;
	KeyBinding(const KeyBinding&) = delete;
	KeyBinding& operator=(const KeyBinding&) = delete;

	bool CheckControlls(std::shared_ptr<Keyboard> kbd, Controlls con);

private:
	int createServer = 0x31;
	int joinServer = 0x32;
	int startGame = 0x34;
};