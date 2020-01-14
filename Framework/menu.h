#ifndef __MENU_H__
#define __MENU_H__

class BackBuffer;
class Sprite;

enum Button{ NEW, SCORES, CONTROLS, QUIT };

class Menu
{
public:
	Menu();
	~Menu();

	void Initialise(BackBuffer& backBuffer);
	void Draw(BackBuffer& backBuffer);
	void MenuUp();
	void MenuDown();
	void MenuAccept();

	void NewGame();
	void Scores();
	void Controls();
	void QuitGame();

protected:
	Button m_Selected;
	Sprite* m_pLogo;
};

#endif // __MENU_H__