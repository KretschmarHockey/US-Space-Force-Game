// COMP710 GP 2D Framework 2019
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;
class Menu;
class ScoreInput;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessGameInput(Game& game);
	void ProcessMenuInput(Menu& menu);
	void ProcessPauseInput(Game& game);
	void ProcessScoreInput(Game& game);
	void ProcessTextInput(ScoreInput& scoreinput);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_Joystick* m_pGameController;

private:

};

#endif // __INPUTHANDER_H__
