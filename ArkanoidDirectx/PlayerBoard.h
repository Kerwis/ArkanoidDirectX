#pragma once
#include <memory>
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
};
class PlayerBoard
{
public:

	PlayerBoard(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input);
	~PlayerBoard() = default;

	void InitElements(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input);
	void Update(float dt) noexcept;
	void Draw(Graphics& gfx) const noexcept;
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Wall> wallL;
	std::unique_ptr<Wall > wallR;
	std::vector <std::unique_ptr<Plate>> plates;
	std::shared_ptr<BoardInfo> myInfo;
	Vector2 bounds = { 35, -35 };
};