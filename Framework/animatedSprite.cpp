// COMP710 GP 2D Framework 2019

// This includes:
#include "animatedSprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{

}


AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	m_numberOfFrames = x;

	SDL_Rect frame;

	// Add the x coordinate to the frame coordinate container.
	for (int i = 0; i < m_numberOfFrames; i++)
	{
		frame.x = m_frameWidth * i;
		frame.y = 0;
		frame.w = m_frameWidth;
		frame.h = m_frameWidth;
		m_SpriteClips.push_back(frame);
	}
}

void
AnimatedSprite::Process(float deltaTime)
{
	if (m_animating)
	{
		// If not paused...
		if (!m_paused)
		{
			// Count the time elapsed.
			m_timeElapsed += deltaTime;
		}

		// If the time elapsed is greater than the frame speed.
		if (m_timeElapsed > m_frameSpeed)
		{
			// Move to the next frame.
			m_currentFrame++;

			// Reset the time elapsed counter.
			m_timeElapsed = 0;
		}

		// If the current frame is greater than the number
		// of the frame in this animation...
		if (m_currentFrame >= m_numberOfFrames)
		{
			// Reset to the first frame.
			m_currentFrame = 0;

			// Stop the animation if it is not looping...
			if (!m_loop)
			{
				m_animating = false;
			}
		}
	}
}

void
AnimatedSprite::Draw(BackBuffer& backBuffer)
{
	// Draw the particular frame into the backbuffer.
	//SDL_Rect* currentFrame = &m_SpriteClips[m_currentFrame];
	SDL_Rect currentFrame = m_SpriteClips[m_currentFrame];
	backBuffer.DrawAnimatedSprite(*this, m_x, m_y, &currentFrame);

	// What is the current frame's x coordinate?
	// What is the frame width?
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}