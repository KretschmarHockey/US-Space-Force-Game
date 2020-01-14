#ifndef __SPLASH_H__
#define __SPLASH_H__

class BackBuffer;
class Sprite;

class Splash
{
public:
	Splash();
	~Splash();

	void Initialise(BackBuffer& backBuffer);
	void Draw(BackBuffer& backBuffer);
	float m_fSplashTimer = 10;

protected:
	Sprite* m_pfmod;
	Sprite* m_pAUT;

};



#endif // __SPLASH_H__