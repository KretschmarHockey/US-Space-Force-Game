#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__

class BackBuffer;

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void Draw(BackBuffer& backBuffer);
};

#endif // __PAUSEMENU_H__