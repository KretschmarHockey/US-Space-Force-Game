#include "scoremenu.h"
#include "game.h"

Score::Score()
{
}


Score::~Score()
{
}

void
Score::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 100, 100);
	backBuffer.DrawText(200, 100, "High Scores");
	backBuffer.SetTextColour(100, 100, 200);
	backBuffer.DrawText(250, 200, "Score");
	backBuffer.DrawText(500, 200, "Level");
	backBuffer.DrawText(750, 200, "Name");
	backBuffer.SetTextColour(200, 200, 200);
	char place[4];
	for (int i = 0; i < 10; i++)
	{
		snprintf(place, 4, "%d.", i+1);
		backBuffer.SetTextColour(100, 200, 100);
		backBuffer.DrawText(180, 250 + i * 50, place);

		int i_score = *(Game::GetInstance().GetHighScoreBoard()->GetScore(i));
		char c_score[(((sizeof i_score) * CHAR_BIT) + 2) / 3 + 2];
		sprintf_s(c_score, "%d", i_score);
		int i_level = *(Game::GetInstance().GetHighScoreBoard()->GetLevel(i));
		char c_level[(((sizeof i_score) * CHAR_BIT) + 2) / 3 + 2];
		sprintf_s(c_level, "%d", i_level);

		backBuffer.SetTextColour(200, 200, 200);
		backBuffer.DrawText(250, 250 + i * 50, c_score);
		backBuffer.DrawText(500, 250 + i * 50, c_level);
		backBuffer.DrawText(750, 250 + i * 50, Game::GetInstance().GetHighScoreBoard()->GetName(i)->c_str());
	}

	backBuffer.SetDrawColour(200, 200, 200);
	backBuffer.DrawRectangle(150, 850, 340, 905);
	backBuffer.DrawText(165, 850, "(B)ack");
}

void
Score::LoadHighScore(HighScore* highscore)
{
	m_pHighscore = highscore;
}