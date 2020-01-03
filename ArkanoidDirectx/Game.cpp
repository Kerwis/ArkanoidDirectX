#include "Game.h"

Game::Game(Graphics& gfx, std::shared_ptr<Keyboard> input, int boardWidth, int boardHeight)
	: boardWidth(boardWidth), boardHeight(boardHeight), kbd(input)
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
	playerOne = std::make_unique<PlayerBoard>(pi, 1, gfx, std::make_shared<LocalControl>(kbd), boardWidth, boardHeight);
}

void Game::StartMultiGame(std::shared_ptr<BoardInfo> pmypi, std::shared_ptr<BoardInfo> popi, Graphics& gfx)
{
	isStart = true;
	isMulti = true;
	playerOne = std::make_unique<PlayerBoard>(pmypi, 1, gfx, std::make_shared<LocalControl>(kbd), boardWidth, boardHeight);
	playerTwo = std::make_unique<PlayerBoard>(popi, -1, gfx, std::make_shared<NetworkControl>(popi), boardWidth, boardHeight);
}

void Game::Update(float dt, HWND hWnd) noexcept
{
	playerOneScore = playerOne->Update(dt);
	if (isMulti)
	{
		playerTwoScore = playerTwo->Update(dt);
	}
	if (playerOneScore.end || (isMulti && playerTwoScore.end))
	{
		if (playerOneScore.end && (isMulti && playerTwoScore.end))
		{
			//debug desynchron?
			MessageBox(hWnd, "Desynchron", "Posible error", MB_OK);
		}
		if (playerOneScore.win)
		{
			MessageBox(hWnd, "You win!", "Congratulation!", MB_OK);
		}
		else
		{
			MessageBox(hWnd, "You lost", "Next time!", MB_OK);
		}
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

