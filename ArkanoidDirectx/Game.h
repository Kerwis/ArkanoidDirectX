#pragma once
#include "Graphics.h"
#include "Player.h"
#include "Ball.h"

class Game
{
public:
	Game(Graphics& gfx, std::shared_ptr<Keyboard> input);
	~Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void Update(float dt) noexcept;
	void Draw(Graphics& gfx) const noexcept;
	Vector2 GetBounds();

	std::unique_ptr<Player> player;
	std::unique_ptr<Ball> ball;

private:
	Vector2 bounds = { 30, 25 };
};