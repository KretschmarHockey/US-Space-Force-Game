#ifndef __COMPLETEOVERLAY_H__
#define __COMPLETEOVERLAY_H__

class BackBuffer;

class CompleteOverlay
{
public:
	CompleteOverlay();
	~CompleteOverlay();

	void Draw(BackBuffer& backBuffer);

	void SetCompleteOverlayTimer(float time);

	float m_fCompleteOverlayTimer;
};

#endif // __COMPLETEOVERLAY_H__