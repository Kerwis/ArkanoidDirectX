#include "Game.h"

Game::Game(Graphics& gfx, std::shared_ptr<Keyboard> input)
	:kbd(input)
{
}

Vector2 Game::GetBounds()
{
	return bounds;
}

bool Game::IsStart()
{
	return isStart;
}

void Game::StartSingleGame(std::shared_ptr<BoardInfo> pi, Graphics& gfx)
{
	isStart = true;
	playerOne = std::make_unique<PlayerBoard>(pi, 1, gfx, std::make_shared<LocalControl>(kbd));
}

void Game::StartMultiGame(std::shared_ptr<BoardInfo> pmypi, std::shared_ptr<BoardInfo> popi, Graphics& gfx)
{
	isStart = true;
	isMulti = true;
	playerOne = std::make_unique<PlayerBoard>(pmypi, 1, gfx, std::make_shared<LocalControl>(kbd));
	playerTwo = std::make_unique<PlayerBoard>(popi, -1, gfx, std::make_shared<NetworkControl>(popi));
}

void Game::Update(float dt) noexcept
{
	playerOne->Update(dt);
	if (isMulti)
	{
		playerTwo->Update(dt);
	}
}

void Game::Draw(Graphics& gfx) const noexcept
{
	playerOne->Draw(gfx);
	if (isMulti)
	{
		playerTwo->Draw(gfx);
	}
}

