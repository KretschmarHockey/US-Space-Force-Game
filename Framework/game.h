// COMP710 GP 2D Framework 2019
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "fmod.hpp"
#include "menu.h"
#include "iniParser.h"

enum State { SPLASH, MENU, GAMEPLAY, LEVELINGUP, PAUSED, GAMEOVER, SCORE, COMPLETE, SCOREINPUT, S_CONTROLS };

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Playership;
class Enemy;
class Explosion;
class AnimatedSprite;
class Entity;
class Pod;
class Bullet;
class Overlay;
class Splash;
class IniParser;
class Menu;
class PauseMenu;
class LevelingUpOverlay;
class Collectible;
class ParticleEmitter;
class GOOverlay;
class Score;
class CompleteOverlay;
class ScoreInput;
class OptionsMenu;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();
	void GetDesktopResolution(int& horizontal, int& vertical);
	static int GetHeight();
	static int GetWidth();
	State GetState();
	bool InitialiseSoundSystem();
	void SetState(State state);

	void StopSpaceshipHorizontal();
	void StopSpaceshipVertical();
	void SetSpaceshipHorizontalSpeed(float speed);
	void SetSpaceshipVerticalSpeed(float speed);

	void FireBullet();

	void SetPlayerInvincibility(bool invincibility);

	void StartGame();
	void StartLevel();
	void LevelUp();
	void MenuSelect();
	void MenuAccept();
	int GetLevel();
	int GetScore();
	void Respawn();
	void LoseGame();
	void PauseGame();
	void WinGame();
	void SpawnCollectible();
	void CollectCollectible();
	void ShowScore();
	void ShowMenu();
	void AddScore(int x);
	void ShowControls();

	IniParser* GetIniParser();
	HighScore* GetHighScoreBoard();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	bool CheckCollision(Entity* entityOne, Entity* entityTwo);


private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	
protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	FMOD::System* m_pSoundSystem;
	FMOD::Channel* m_pChannel;
	ParticleEmitter* m_pParticleEmitter;
	IniParser* m_pIniParser;
	bool m_looping;
	State m_state;
	int m_iScore;
	int m_iLevel;
	int m_iLives;
	int m_iBullets;
	float m_fCollectibleTimer;

	static int height;
	static int width;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Player
	Playership* m_pPlayership;
	Sprite* m_pPlayershipSprite;
	FMOD::Sound* m_pLifeGained;
	FMOD::Sound* m_pPlayerExplosionSound;

	// Enemy
	std::vector<Enemy*> m_vEnemies;
	Sprite* m_pEnemyshipSprite;
	FMOD::Sound* m_pEnemyExplosionSound;
	FMOD::Sound* m_pEnemySpawnedSound;

	// Explosion
	std::vector<Explosion*> m_vExplosion;
	AnimatedSprite* m_pExplosionSprite;

	// Pods
	std::vector<Pod*> m_vPods;
	Sprite* m_pPodSprite;
	FMOD::Sound* m_pPodCollectedSound;

	// Bullet
	std::vector<Bullet*> m_vBullets;
	Sprite* m_pBulletSprite;
	FMOD::Sound* m_pBulletShotSound;

	// Collectible
	Collectible* m_pCollectible;
	FMOD::Sound* m_pCollectibleSpawnedSound;

	// Ammo
	Sprite* m_pAmmoSprite;

	// Debris
	Sprite* m_pDebrisSpriteSheet;

	// Overlay
	Overlay* m_pOverlay;
	LevelingUpOverlay* m_pLevelingUpOverlay;
	Splash* m_pSplash;
	Menu* m_pMenu;
	PauseMenu* m_pPauseMenu;
	GOOverlay* m_pGOOverlay;
	Score* m_pScoreScreen;
	HighScore* m_pHighScore;
	CompleteOverlay* m_pCompleteOverlay;
	ScoreInput* m_pScoreInput;
	OptionsMenu* m_pOptionsMenu;
	FMOD::Sound* m_pMenuSelectSound;
	FMOD::Sound* m_pMenuAcceptSound;
	FMOD::Sound* m_pLevelUpSound;
	FMOD::Sound* m_pMusic;
	
private:
};

#endif // __GAME_H__
