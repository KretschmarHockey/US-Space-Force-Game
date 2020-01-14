#include "completeoverlay.h"
#include "game.h"
#include "backbuffer.h"


CompleteOverlay::CompleteOverlay()
{
}


CompleteOverlay::~CompleteOverlay()
{
}

void
CompleteOverlay::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(Game::GetWidth() / 2 - 250, Game::GetHeight() / 2 - 100, "Congrats You Won");
}

void
CompleteOverlay::SetCompleteOverlayTimer(float time)
{
	m_fCompleteOverlayTimer = time;
}