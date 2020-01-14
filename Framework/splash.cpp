#include "splash.h"

#include "backbuffer.h"
#include "game.h"
#include "sprite.h"


Splash::Splash()
{

}


Splash::~Splash()
{
	delete m_pfmod;
	m_pfmod = 0;
	delete m_pAUT;
	m_pAUT = 0;
}

void
Splash::Initialise(BackBuffer& backBuffer)
{
	m_pfmod = backBuffer.CreateSprite("assets/fmod.png");
	m_pAUT = backBuffer.CreateSprite("assets/AUT-logo-tab.png");
}

void
Splash::Draw(BackBuffer& backBuffer)
{
	m_pfmod->SetX((Game::GetWidth() / 2) - (m_pfmod->GetWidth() / 2));
	m_pfmod->SetY((Game::GetHeight() / 2) - (m_pfmod->GetHeight() / 2));
	m_pAUT->SetX(Game::GetWidth() - m_pAUT->GetWidth() - 52);
	m_pAUT->SetY(0);
	backBuffer.DrawSprite(*m_pfmod);
	backBuffer.DrawSprite(*m_pAUT);
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(10, Game::GetHeight() - 20, "Music by Patrick de Arteaga");
}
