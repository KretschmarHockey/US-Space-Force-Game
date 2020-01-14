#include "scoreinput.h"
#include "backbuffer.h"
#include "game.h"


ScoreInput::ScoreInput()
{
}


ScoreInput::~ScoreInput()
{

}

void
ScoreInput::Initialise()
{
	SDL_StartTextInput();
}


void
ScoreInput::Process(float deltaTime)
{

}

void
ScoreInput::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(150, 100, "You made a high score!");
	backBuffer.DrawText(150, 150, "Please enter your name.");
	backBuffer.SetDrawColour(200, 200, 200);
	backBuffer.DrawRectangle(150, 350, 250, 400);
	backBuffer.DrawText(165, 350, "OK");
	if (m_bRenderText)
	{
		backBuffer.SetTextColour(100, 200, 100);
		if (m_inputText != "")
		{
			backBuffer.DrawText(150, 250, m_inputText.c_str());
		}
		else
		{
			backBuffer.DrawText(150, 250, " ");
		}
	}
}

std::string
ScoreInput::GetText()
{
	return m_inputText;
}

void
ScoreInput::Append(char* key)
{
	m_inputText += key;
}

void
ScoreInput::BackSpace()
{
	m_inputText.pop_back();
}

void
ScoreInput::Copy()
{
	SDL_SetClipboardText(m_inputText.c_str());
}

void
ScoreInput::Paste()
{
	m_inputText = SDL_GetClipboardText();
}

void
ScoreInput::Rerender()
{
	m_bRenderText = true;
}

void
ScoreInput::Submit()
{
	int score = Game::GetInstance().GetScore();
	int level = Game::GetInstance().GetLevel();
	Game::GetInstance().GetHighScoreBoard()->SubmitScore(&score, &level, &m_inputText);
	Game::GetInstance().ShowScore();
}