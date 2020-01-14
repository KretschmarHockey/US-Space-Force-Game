// COMP710 GP 2D Framework 2019

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "menu.h"
#include "scoreinput.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		// Exception
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	LogManager::GetInstance().Log("Controller detected!");

	return (true);
}

void 
InputHandler::ProcessGameInput(Game& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.Quit();
			}
			else if (event.key.keysym.sym == SDLK_LEFT)
			{
				game.SetSpaceshipHorizontalSpeed(-500);
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				game.SetSpaceshipHorizontalSpeed(500);
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				game.SetSpaceshipVerticalSpeed(-500);
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				game.SetSpaceshipVerticalSpeed(500);
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				game.FireBullet();
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				game.PauseGame();
			//}
			//else if (event.key.keysym.sym == SDLK_i) // Set Invincibility to True
			//{
			//	game.SetPlayerInvincibility(true);
			//}
			//else if (event.key.keysym.sym == SDLK_u) // Set Invincibility to False
			//{
			//	game.SetPlayerInvincibility(false);
			//}
			//else if (event.key.keysym.sym == SDLK_c)
			//{
			//	game.SpawnCollectible();
			//}
			}
		}		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				game.FireBullet();
			}
			else if (event.jbutton.button == 7) // Start Button
			{
				game.PauseGame();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
			{
				game.StopSpaceshipHorizontal();
			}
			else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
			{
				game.StopSpaceshipVertical();
			}
		}
		else if (event.type == SDL_JOYAXISMOTION)
		{
			if (event.jaxis.value > 11000 || event.jaxis.value < -11000)
			{
				if (event.jaxis.axis == 0) // Horizontal Movement
				{
					game.SetSpaceshipHorizontalSpeed(event.jaxis.value / 65.0f);
				}
				if (event.jaxis.axis == 1) // Vertical Movement
				{
					game.SetSpaceshipVerticalSpeed(event.jaxis.value / 65.0f);
				}
			}
			else
			{
				if (event.jaxis.axis == 0) // Horizontal Movement
				{
					game.SetSpaceshipHorizontalSpeed(0);
				}
				if (event.jaxis.axis == 1) // Vertical Movement
				{
					game.SetSpaceshipVerticalSpeed(0);
				}
			}
		}	
	}
}

void
InputHandler::ProcessMenuInput(Menu& menu)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
			{
				menu.MenuUp();
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				menu.MenuDown();
			}
			else if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_RETURN)
			{
				menu.MenuAccept();
			}
		}
		else if (event.type == SDL_JOYHATMOTION)
		{
			if (event.jhat.value == SDL_HAT_UP)
			{
				menu.MenuUp();
			}
			else if (event.jhat.value == SDL_HAT_DOWN)
			{
				menu.MenuDown();
			}
		}
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A)
{
	menu.MenuAccept();
}
		}
	}
}

void
InputHandler::ProcessPauseInput(Game& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_p)
			{
				game.PauseGame();
			}
		}
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			if (event.jbutton.button == 7) // Start Button
			{
				game.PauseGame();
			}
		}
	}
}

void
InputHandler::ProcessScoreInput(Game& game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			if (event.jbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				game.ShowMenu();
			}
		}
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_b || event.key.keysym.sym == SDLK_ESCAPE)
			{
				game.ShowMenu();
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if ((event.button.x > 150) && (event.button.x < 340) && (event.button.y > 850) && (event.button.y < 905))
				{
					game.ShowMenu();
				}
			}
		}
	}
}

void
InputHandler::ProcessTextInput(ScoreInput& scoreinput)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		// Special key input
		if (event.type == SDL_KEYDOWN)
		{
			// Backspace
			if (event.key.keysym.sym == SDLK_BACKSPACE && scoreinput.GetText().length() > 0)
			{
				scoreinput.BackSpace();
				scoreinput.Rerender();
			}
			// Copy
			else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				scoreinput.Copy();
			}
			// Paste
			else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				scoreinput.Paste();
				scoreinput.Rerender();
			}
			else if (event.key.keysym.sym == SDLK_RETURN)
			{
				scoreinput.Submit();
			}
		}
		// Special text input
		else if (event.type == SDL_TEXTINPUT)
		{
			// Not Copy or Paste
			if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')))
			{
				scoreinput.Append(event.text.text);
				scoreinput.Rerender();
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if ((event.button.x > 150) && (event.button.x < 250) && (event.button.y > 350) && (event.button.y < 400))
				{
					scoreinput.Submit();
				}
			}
		}
	}
}