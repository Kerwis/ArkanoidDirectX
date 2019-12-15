#include "Game.h"

Game::Game(Graphics& gfx, std::shared_ptr<Keyboard> input)
{
	player = std::make_unique<Player>(gfx, input);
	ball = std::make_unique<Ball>(gfx);
}

void Game::Update(float dt) noexcept
{
	player->Update(dt);
	player->CheckBounce(bounds);
	ball->Update(dt);
	ball->CheckBounce(player->GetPos(), player->GetSize(), bounds);
}

void Game::Draw(Graphics& gfx) const noexcept
{
	player->Draw(gfx);
	ball->Draw(gfx);
}

Vector2 Game::GetBounds()
{
	return bounds;
}
