#include "KeyBinding.h"

bool KeyBinding::CheckControlls(std::shared_ptr<Keyboard> kbd, Controlls con)
{
	switch (con)
	{
	case Controlls::CreateServer:
		return kbd->KeyIsPressed(createServer);
		break;
	case Controlls::JoinServer:
		return kbd->KeyIsPressed(joinServer);
		break;
	case Controlls::StartGame:
		return kbd->KeyIsPressed(startGame);
		break;
	default:
		return false;
		break;
	}
}
