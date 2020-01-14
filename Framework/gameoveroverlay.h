#ifndef __GOOVERLAY_H__
#define __GOOVERLAY_H__

class BackBuffer;

class GOOverlay
{
public:
	GOOverlay();
	~GOOverlay();

	void Draw(BackBuffer& backBuffer);

	void SetGOOverlayTimer(float time);

	float m_fGOOverlayTimer;
};

#endif // __GOOVERLAY_H__

