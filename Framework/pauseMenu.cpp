#include "pauseMenu.h"
#include "game.h"
#include "backbuffer.h"


PauseMenu::PauseMenu()
{
}


PauseMenu::~PauseMenu()
{
}

void
PauseMenu::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(Game::GetWidth() / 2 - 160, Game::GetHeight() / 2 - 20, "Game paused");
}