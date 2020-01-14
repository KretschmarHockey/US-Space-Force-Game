#ifndef __LEVELINGUPOVERLAY_H__
#define __LEVELINGUPOVERLAY_H__

class BackBuffer;

class LevelingUpOverlay
{
public:
	LevelingUpOverlay();
	~LevelingUpOverlay();

	void Draw(BackBuffer& backBuffer);

	float m_fLevelUpOverlayTimer = 5;
};

#endif // __LEVELINGUPOVERLAY_H__