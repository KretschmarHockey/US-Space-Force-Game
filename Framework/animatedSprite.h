// COMP710 GP 2D Framework 2019

#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"

#include <SDL.h>
#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:

	// Fields:
public:

protected:
	std::vector<SDL_Rect> m_SpriteClips;

	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	int m_currentFrame;
	int m_numberOfFrames;

	bool m_paused;
	bool m_loop;
	bool m_animating;


private:
};

#endif // __ANIMATEDSPRITE_H__