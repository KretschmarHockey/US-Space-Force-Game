#ifndef __SCOREMENU_H__
#define __SCOREMENU_H__

#include "highscores.h"
#include "backbuffer.h"

class Score
{
public:
	Score();
	~Score();

	void LoadHighScore(HighScore* highscore);
	void Draw(BackBuffer& backBuffer);

protected:
	HighScore* m_pHighscore;
};

#endif // __SCORE_H__