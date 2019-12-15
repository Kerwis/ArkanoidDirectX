#include "Game.h"

Game::Game(Graphics& gfx, std::shared_ptr<Keyboard> input)
{
	player = std::make_unique<Player>(gfx, input);
	ball = std::make_unique<Ball>(gfx);
}

void Game::Update(float dt) noexcept
{
	player->Update(dt);
	ball->Update(dt);
	ball->CheckBounce(player->GetPos(), player->GetSize());
}

void Game::Draw(Graphics& gfx) const noexcept
{
	player->Draw(gfx);
	ball->Draw(gfx);
}
