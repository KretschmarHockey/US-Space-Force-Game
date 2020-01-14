#ifndef __OPTIONSMENU_H__
#define __OPTIONSMENU_H__

#include "backbuffer.h"
#include "sprite.h"

class OptionsMenu
{
public:
	OptionsMenu();
	~OptionsMenu();

	void Initialise(Sprite* ammoSprite, Sprite* podSprite);
	void Draw(BackBuffer& backBuffer);

protected:
	Sprite* m_pAmmoSprite;
	Sprite* m_pPodSprite;
};

#endif // __OPTIONSMENU_H__