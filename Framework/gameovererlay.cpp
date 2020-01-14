#include "gameoveroverlay.h"
#include "game.h"
#include "backbuffer.h"



GOOverlay::GOOverlay()
{
}


GOOverlay::~GOOverlay()
{
}

void
GOOverlay::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(Game::GetWidth() / 2 - 150, Game::GetHeight() / 2 - 100, "Game Over");
}

void
GOOverlay::SetGOOverlayTimer(float time)
{
	m_fGOOverlayTimer = time;
}