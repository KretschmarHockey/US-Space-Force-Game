#include "optionsmenu.h"



OptionsMenu::OptionsMenu()
{
}


OptionsMenu::~OptionsMenu()
{
}

void
OptionsMenu::Initialise(Sprite* ammoSprite, Sprite* podSprite)
{
	m_pAmmoSprite = ammoSprite;
	m_pPodSprite = podSprite;
}

void
OptionsMenu::Draw(BackBuffer& backBuffer)
{
	backBuffer.SetTextColour(200, 100, 100);
	backBuffer.DrawText(150, 100, "Controls:");
	backBuffer.DrawText(1000, 100, "Instructions:");
	backBuffer.SetTextColour(200, 200, 200);
	backBuffer.DrawText(150, 150, "Left Joystick = Move");
	backBuffer.DrawText(150, 200, "(A) = Shoot");
	backBuffer.DrawText(1000, 150, "Collect all   to advance to");
	backBuffer.DrawText(1000, 200, "next level.");
	backBuffer.DrawText(1000, 250, "Avoid Spaceships.");
	backBuffer.DrawText(1000, 300, "Reach Level 45.");
	backBuffer.DrawText(1000, 350, "Collect   for ammo.");

	backBuffer.SetDrawColour(200, 200, 200);
	backBuffer.DrawRectangle(150, 850, 340, 905);
	backBuffer.DrawText(165, 850, "(B)ack");

	m_pPodSprite->SetX(1253);
	m_pPodSprite->SetY(170);
	backBuffer.DrawSprite(*m_pPodSprite);

	m_pAmmoSprite->SetX(1174);
	m_pAmmoSprite->SetY(360);
	backBuffer.DrawSprite(*m_pAmmoSprite);
}