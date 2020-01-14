#include "levelupoverlay.h"
#include "game.h"
#include "backbuffer.h"

LevelingUpOverlay::LevelingUpOverlay()
{
}


LevelingUpOverlay::~LevelingUpOverlay()
{
}

void
LevelingUpOverlay::Draw(BackBuffer& backBuffer)
{
	char text[25];
	sprintf_s(text, "Prepare for level %d", Game::GetInstance().GetLevel());
	backBuffer.SetTextColour(255, 255, 255);
	backBuffer.DrawText(Game::GetWidth() / 2 - 250, Game::GetHeight() / 2 - 100, text);
}