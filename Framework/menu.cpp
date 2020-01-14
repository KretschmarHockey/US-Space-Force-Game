#include "menu.h"
#include "game.h"
#include "backBuffer.h"
#include "sprite.h"

#include <SDL_image.h>

Menu::Menu()
: m_Selected(NEW)
{
}


Menu::~Menu()
{
	//delete m_pBackgroundSprite;
	//m_pBackgroundSprite = 0;
}

void
Menu::Initialise(BackBuffer& backBuffer)
{
	//m_pLogo = backBuffer.CreateSprite("assets/US-Space-Force.png");
}


void
Menu::Draw(BackBuffer& backBuffer)
{
	backBuffer.DrawImage(0, 0, "assets/spacebackground.png");
	//backBuffer.DrawSprite(*m_pLogo);

	// New Game Button
	if (m_Selected == NEW)
	{
		backBuffer.SetTextColour(100, 255, 100);
	}
	else
	{
		backBuffer.SetTextColour(200, 200, 200);
	}
	backBuffer.DrawText(65, 65, "New Game");

	// Scores Button
	if (m_Selected == SCORES)
	{
		backBuffer.SetTextColour(100, 255, 100);
	}
	else
	{
		backBuffer.SetTextColour(200, 200, 200);
	}
	backBuffer.DrawText(65, 165, "Scores");

	// Options Button
	if (m_Selected == CONTROLS)
	{
		backBuffer.SetTextColour(100, 255, 100);
	}
	else
	{
		backBuffer.SetTextColour(200, 200, 200);
	}
	backBuffer.DrawText(65, 265, "Controls");

	// Quit Game Button
	if (m_Selected == QUIT)
	{
		backBuffer.SetTextColour(100, 255, 100);
	}
	else
	{
		backBuffer.SetTextColour(200, 200, 200);
	}
	backBuffer.DrawText(65, 365, "Quit Game");
}

void
Menu::MenuUp()
{
	Game::GetInstance().MenuSelect();
	switch (m_Selected)
	{
	case NEW:
		m_Selected = QUIT;
		break;
	case SCORES:
		m_Selected = NEW;
		break;
	case CONTROLS:
		m_Selected = SCORES;
		break;
	case QUIT:
		m_Selected = CONTROLS;
		break;
	};
}

void
Menu::MenuDown()
{
	Game::GetInstance().MenuSelect();
	switch (m_Selected)
	{
	case NEW:
		m_Selected = SCORES;
		break;
	case SCORES:
		m_Selected = CONTROLS;
		break;
	case CONTROLS:
		m_Selected = QUIT;
		break;
	case QUIT:
		m_Selected = NEW;
		break;
	};
}

void
Menu::MenuAccept()
{
	Game::GetInstance().MenuAccept();
	switch (m_Selected)
	{
	case NEW:
		NewGame();
		break;
	case SCORES:
		Scores();
		break;
	case CONTROLS:
		Controls();
		break;
	case QUIT:
		QuitGame();
		break;
	}
}

void
Menu::NewGame()
{
	Game::GetInstance().StartGame();
}

void
Menu::Scores()
{
	Game::GetInstance().ShowScore();
}

void
Menu::Controls()
{
	Game::GetInstance().ShowControls();
}

void
Menu::QuitGame()
{
	Game::GetInstance().Quit();
}