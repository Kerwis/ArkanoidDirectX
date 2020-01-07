#pragma once
#include <memory>
#include <bitset>
#include "Keyboard.h"
#include "Graphics.h"
#include "Player.h"
#include "Ball.h"
#include "Plate.h"
#include "PlayerControl.h"
#include "Wall.h"
struct BoardInfo
{
	int id;
	Vector2 playerPosition;
	Vector2 ballPosition;
	std::bitset<10>  plates[20];
	bool ready;
	bool localControl;
	bool lock = false;
};

struct Score
{
	bool end;
	bool win;
};

class PlayerBoard
{
public:

	PlayerBoard(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input, int boardWidth, int boardHeight);
	~PlayerBoard() = default;
	PlayerBoard(const PlayerBoard&) = delete;
	PlayerBoard& operator=(const PlayerBoard) = delete;

	void InitElements(float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input);
	Score Update(float dt) noexcept;
	void Draw(Graphics& gfx) const noexcept;
	bool IsBlock();
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Wall> wallL;
	std::unique_ptr<Wall > wallR;
	std::unique_ptr<Wall > wallU;
	std::vector <std::unique_ptr<Plate>> plates;
	std::shared_ptr<BoardInfo> myInfo;
	Vector2 bounds = { 35, -35 };

	int width = 20;
	int height = 10;
};