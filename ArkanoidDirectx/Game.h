#pragma once
#include "Graphics.h"
#include "PlayerBoard.h"
#include "LocalControl.h"
#include "NetworkControl.h"

class Game
{
public:
	Game(Graphics& gfx, std::shared_ptr<Keyboard> input, int boardWidth, int boardHeight);
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update(float dt, HWND hWnd) noexcept;
	void Draw(Graphics& gfx) const noexcept;

	Vector2 GetBounds();
	bool IsStart();
	void StartSingleGame(std::shared_ptr<BoardInfo> pi, Graphics& gfx);
	void StartMultiGame(std::shared_ptr<BoardInfo> pmypi, std::shared_ptr<BoardInfo> popi, Graphics& gfx);
private:
	std::unique_ptr<PlayerBoard> playerOne = nullptr;
	std::unique_ptr<PlayerBoard> playerTwo = nullptr;
	std::shared_ptr<Keyboard> kbd = nullptr;
	bool isStart = false;
	bool isMulti = false;
	Vector2 bounds = { 30, 25 };
	int boardWidth = -1;
	int boardHeight = -1;
	Score playerOneScore;
	Score playerTwoScore;
};