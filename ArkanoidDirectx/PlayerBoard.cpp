#include "PlayerBoard.h"



PlayerBoard::PlayerBoard(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input)
{
	myInfo = playerInfo;
	InitElements(myInfo, rotation, gfx, input);
}

void PlayerBoard::InitElements(std::shared_ptr<BoardInfo> playerInfo, float rotation, Graphics& gfx, std::shared_ptr<PlayerControl> input)
{
	playerInfo->playerPosition = { 0, -32 * rotation };
	playerInfo->ballPosition = { 0, -18 * rotation };
	Vector2 ballSpeed = { 0,-15 * rotation };
	Vector2 ballSize = { 1,1 };
	Vector2 wallpos = { -bounds.x - 1, 0 };
	Vector2 wallsize = { 1,-bounds.y };
	wallL = std::make_unique<Wall>(wallpos, wallsize, gfx);
	wallpos.x *= -1;
	wallR = std::make_unique<Wall>(wallpos, wallsize, gfx);
	bounds.y *= rotation;
	player = std::make_unique<Player>(&(playerInfo->playerPosition), gfx, input);
	ball = std::make_unique<Ball>(&(playerInfo->ballPosition), ballSpeed, ballSize, input, gfx);

	for (int i = -10; i < 0; i++)
	{
		for (int j = -10; j <= 10; j++)
		{
			Vector2 pos = { j * 3, i * 2.5 * (float)rotation };
			plates.push_back(std::make_unique<Plate>(gfx, pos));
		}
	}
}

void PlayerBoard::Update(float dt) noexcept
{
	player->Update(dt);
	player->CheckBounce(bounds);
	ball->Update(dt);
	ball->CheckBounce(*player, bounds);
	int i = 0;
	for (auto& p : plates)
	{
		if (p->CheckHit(*ball))
		{
			plates.erase(plates.begin() + i);
			break;
		}
		i++;
	}
}

void PlayerBoard::Draw(Graphics& gfx) const noexcept
{
	wallL->Draw(gfx);
	wallR->Draw(gfx);
	player->Draw(gfx);
	ball->Draw(gfx);
	for (auto& p : plates)
	{
		p->Draw(gfx);
	}
}