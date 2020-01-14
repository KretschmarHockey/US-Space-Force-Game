// COMP710 GP 2D Framework 2019

// This includes:
#include "game.h"
#include "playership.h"
#include "enemy.h"
#include "explosion.h"
#include "animatedsprite.h"
#include "pod.h"
#include "gameoverlay.h"
#include "splash.h"
#include "bullet.h"
#include "sprite.h"
#include "iniparser.h"
#include "menu.h"
#include "levelupoverlay.h"
#include "gameoveroverlay.h"
#include "pauseMenu.h"
#include "scoremenu.h"
#include "collectible.h"
#include "particleemitter.h"
#include "completeoverlay.h"
#include "scoreinput.h"
#include "optionsmenu.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "wtypes.h"
#include "fmod.hpp"
#include "fmod_errors.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fmod.h>

// Static Members:
Game* Game::sm_pInstance = 0;
int Game::height = 1080;
int Game::width = 1920;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_pSoundSystem(0)
	, m_pChannel(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, m_pPlayership(0)
	, m_pPlayershipSprite(0)
	, m_vEnemies(0)
	, m_pEnemyshipSprite(0)
	, m_vExplosion(0)
	, m_pExplosionSprite(0)
	, m_vPods(0)
	, m_pPodSprite(0)
	, m_vBullets(0)
	, m_pBulletSprite(0)
	, m_pCollectible(0)
	, m_pAmmoSprite(0)
	, m_pOverlay(0)
	, m_pLevelingUpOverlay(0)
	, m_pGOOverlay(0)
	, m_pScoreScreen(0)
	, m_state(SPLASH)
	, m_pSplash(0)
	, m_pMenu(0)
	, m_pParticleEmitter(0)
	, m_pIniParser(0)
{

}

Game::~Game()
{
	delete m_pInputHandler;
	m_pInputHandler = 0;
	delete m_pPlayership;
	m_pPlayership = 0;
	delete m_pPlayershipSprite;
	m_pPlayershipSprite = 0;
	for (size_t i = 0; i < m_vEnemies.size(); ++i)
	{
		delete m_vEnemies[i];
		m_vEnemies[i] = 0;
	}
	delete m_pEnemyshipSprite;
	m_pEnemyshipSprite = 0;
	for (size_t i = 0; i < m_vPods.size(); i++)
	{
		delete m_vPods[i];
		m_vPods[i] = 0;
	}
	for (size_t i = 0; i < m_vExplosion.size(); i++)
	{
		delete m_vExplosion[i];
		m_vExplosion[i] = 0;
	}
	delete m_pExplosionSprite;
	m_pExplosionSprite = 0;
	delete m_pPodSprite;
	m_pPodSprite = 0;
	for (size_t i = 0; i < m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = 0;
	}
	delete m_pBulletSprite;
	m_pBulletSprite = 0;
	delete m_pCollectible;
	m_pCollectible = 0;
	delete m_pAmmoSprite;
	m_pAmmoSprite = 0;
	delete m_pOverlay;
	m_pOverlay = 0;
	delete m_pLevelingUpOverlay;
	m_pLevelingUpOverlay = 0;
	delete m_pScoreScreen;
	m_pScoreScreen = 0;
	delete m_pGOOverlay;
	m_pGOOverlay = 0;
	delete m_pCompleteOverlay;
	m_pCompleteOverlay = 0;
	delete m_pSplash;
	m_pSplash = 0;
	delete m_pMenu;
	m_pMenu = 0;
	delete m_pPauseMenu;
	m_pPauseMenu = 0;
	m_pParticleEmitter->KillParticles();
	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
	delete m_pIniParser;
	m_pIniParser = 0;
	delete m_pHighScore;
	m_pHighScore = 0;
	delete m_pScoreInput;
	m_pScoreInput = 0;
	delete m_pOptionsMenu;
	m_pOptionsMenu = 0;
	m_pLifeGained->release();
	m_pPlayerExplosionSound->release();
	m_pEnemySpawnedSound->release();
	m_pPodCollectedSound->release();
	m_pCollectibleSpawnedSound->release();
	m_pBulletShotSound->release();
	m_pMusic->release();
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
}

bool 
Game::Initialise()
{
	width = 0;
	height = 0;
	GetDesktopResolution(width, height);
	srand((unsigned int) time(NULL));

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	if (!InitialiseSoundSystem())
	{
		LogManager::GetInstance().Log("SoundSystem Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(0x00, 0x00, 0x00);

	// Loading sprites
	m_pPlayershipSprite = m_pBackBuffer->CreateSprite("assets/playership.png");
	m_pEnemyshipSprite = m_pBackBuffer->CreateSprite("assets/enemy.png");
	m_pExplosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets/explosion.png");
	m_pPodSprite = m_pBackBuffer->CreateSprite("assets/pod.png");
	m_pBulletSprite = m_pBackBuffer->CreateSprite("assets/playerBullet.png");
	m_pAmmoSprite = m_pBackBuffer->CreateSprite("assets/ammo.png");
	m_pDebrisSpriteSheet = m_pBackBuffer->CreateSprite("assets/debris.png");

	m_pExplosionSprite->SetFrameWidth(32);
	m_pExplosionSprite->AddFrame(5);
	m_pExplosionSprite->SetFrameSpeed(0.2f);
	m_pExplosionSprite->SetLooping(false);

	// Overlay
	m_pOverlay = new Overlay();
	m_pLevelingUpOverlay = new LevelingUpOverlay();
	m_pPauseMenu = new PauseMenu();
	m_pGOOverlay = new GOOverlay();
	m_pScoreScreen = new Score();
	m_pCompleteOverlay = new CompleteOverlay();
	m_pScoreInput = new ScoreInput();
	m_pOptionsMenu = new OptionsMenu();
	m_pOptionsMenu->Initialise(m_pAmmoSprite, m_pPodSprite);

	// Particle Emitter
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(m_pDebrisSpriteSheet);
	m_pParticleEmitter->SetFrameWidth(8);
	m_pParticleEmitter->DivideSpriteSheet(8);

	// Splash
	m_pSplash = new Splash();
	m_pSplash->Initialise(*m_pBackBuffer);

	// Menu
	m_pMenu = new Menu();
	m_pHighScore = new HighScore();
	m_pMusic->setMode(FMOD_LOOP_NORMAL);
	m_pMusic->setLoopCount(-1);
	m_pSoundSystem->playSound(m_pMusic, 0, false, &m_pChannel);

	// Debug Settings
	m_state = SPLASH;

	// Load .ini
	m_pIniParser = new IniParser();
	m_pIniParser->LoadIniFile("settings.ini");

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);

	switch (m_state)
	{
	case SPLASH:
		break;
	case MENU:
		m_pInputHandler->ProcessMenuInput(*m_pMenu);
		break;
	case GAMEPLAY:
		m_pInputHandler->ProcessGameInput(*this);
		break;
	case LEVELINGUP:
		break;
	case PAUSED:
		m_pInputHandler->ProcessPauseInput(*this);
		break;
	case GAMEOVER:
		break;
	case SCORE:
	case S_CONTROLS:
		m_pInputHandler->ProcessScoreInput(*this);
		break;
	case COMPLETE:
		break;
	case SCOREINPUT:
		m_pInputHandler->ProcessTextInput(*m_pScoreInput);
		break;
	default:
		break;
	}
	
	
	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		
		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);
	
		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}

		// DEBUG STUB:
//		char buffer[64];
//		sprintf(buffer, "%f", deltaTime);
//		LogManager::GetInstance().Log(buffer);

		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{
	// Explosion

	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Update Sound System
	m_pSoundSystem->update();

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:
	switch (m_state)
	{
	case SPLASH:
		m_pSplash->m_fSplashTimer -= deltaTime;
		if (m_pSplash->m_fSplashTimer < 0)
		{
			m_state = MENU;
		}
		break;
	case MENU:
		break;
	case GAMEPLAY:
		// Process Player
		if (!m_pPlayership->IsDead())
		{
			m_pPlayership->Process(deltaTime);

			// Countdown Invincibility Timer
			if (m_pPlayership->m_fInvincibilityTimer > 0)
			{
				m_pPlayership->m_fInvincibilityTimer -= deltaTime;
				if (m_pPlayership->m_fInvincibilityTimer < 0)
				{
					m_pPlayership->SetInvincibility(false);
				}
			}

			// Countdown Collectible Timer
			if (m_fCollectibleTimer > 0)
			{
				m_fCollectibleTimer -= deltaTime;
				if (m_fCollectibleTimer < 0)
				{
					SpawnCollectible();
				}
			}

			// Process Enemies and collision with player
			for (auto pEnemy = m_vEnemies.begin(); pEnemy != m_vEnemies.end();)
			{
				(*pEnemy)->Process(deltaTime);

				// Collision
				if (!m_pPlayership->IsInvincible())
				{
					if (CheckCollision((*pEnemy), m_pPlayership))
					{
						m_pPlayership->SetDead(true);
						m_pSoundSystem->playSound(m_pPlayerExplosionSound, 0, false, &m_pChannel);
					}
				}

				// Remove dead Enemies
				if ((*pEnemy)->IsDead())
				{
					delete *pEnemy;
					pEnemy = m_vEnemies.erase(pEnemy);
					AddScore(50);
				}
				else
				{
					++pEnemy;
				}
			}

			// Process pods and collision with player
			for (auto pPod = m_vPods.begin(); pPod != m_vPods.end();)
			{
				(*pPod)->Process(deltaTime);

				// Collision with Player
				if (CheckCollision((*pPod), m_pPlayership))
				{
					(*pPod)->SetDead(true);
					m_pSoundSystem->playSound(m_pPodCollectedSound, 0, false, &m_pChannel);
				}

				// Remove dead Pods
				if ((*pPod)->IsDead())
				{
					delete *pPod;
					pPod = m_vPods.erase(pPod);
					AddScore(10);
				}
				else
				{
					++pPod;
				}
			}

			// Process collectibles and collision with player
			if (m_pCollectible)
			{
				if (!m_pCollectible->IsDead())
				{
					m_pCollectible->Process(deltaTime);
					if (CheckCollision(m_pCollectible, m_pPlayership))
					{
						CollectCollectible();
					}
				}
				else
				{
					delete m_pCollectible;
					m_pCollectible = 0;
				}
			}

			// Process bullets and collision with enemies
			for (auto pBullet = m_vBullets.begin(); pBullet != m_vBullets.end();)
			{
				(*pBullet)->Process(deltaTime);

				// Contact with enemy
				for (auto pEnemy = m_vEnemies.begin(); pEnemy != m_vEnemies.end(); ++pEnemy)
				{
					if (CheckCollision((*pBullet), (*pEnemy)))
					{
						(*pBullet)->SetDead(true);
						(*pEnemy)->SetDead(true);
						m_pSoundSystem->playSound(m_pEnemyExplosionSound, 0, false, &m_pChannel);
						Explosion* explosion = new Explosion();
						explosion->Initialise(m_pExplosionSprite);
						explosion->SetPosition((*pEnemy)->GetPositionX(), (*pEnemy)->GetPositionY());
						m_pExplosionSprite->StartAnimating();
						m_vExplosion.push_back(explosion);

						m_pParticleEmitter->AddParticle(20, (*pEnemy)->GetPositionX(), (*pEnemy)->GetPositionY());
					}
				}

				// Remove Dead Bullets
				if ((*pBullet)->IsDead())
				{
					delete *pBullet;
					pBullet = m_vBullets.erase(pBullet);
				}
				else
				{
					++pBullet;
				}
			}

			if (m_vPods.size() == 0)
			{
				LevelUp();
			}

			// Process Explosion Animation
			for (auto pExplosion = m_vExplosion.begin(); pExplosion != m_vExplosion.end();)
			{
				if ((*pExplosion)->GetAnimatedSprite()->IsAnimating())
				{
					(*pExplosion)->GetAnimatedSprite()->Process(deltaTime);
					++pExplosion;
				}
				else
				{
					delete *pExplosion;
					pExplosion = m_vExplosion.erase(pExplosion);
				}
			}

			// Process Particles
			if (m_pParticleEmitter)
			{
				if (m_pParticleEmitter->HasParticles())
				{
					m_pParticleEmitter->Process(deltaTime);
				}
			}

		}
		else if (m_iLives > 1)
		{
			Respawn();
			m_iLives--;
			m_pOverlay->SetLives(m_iLives);
		}
		else
		{
			LoseGame();
		}
		break;
	case LEVELINGUP:
		m_pLevelingUpOverlay->m_fLevelUpOverlayTimer -= deltaTime;
		if (m_pLevelingUpOverlay->m_fLevelUpOverlayTimer < 0)
		{
			m_state = GAMEPLAY;
			m_pLevelingUpOverlay->m_fLevelUpOverlayTimer = 5;
			StartLevel();
		}
		break;
	case PAUSED:
		break;
	case GAMEOVER:
		m_pGOOverlay->m_fGOOverlayTimer -= deltaTime;
		if (m_pGOOverlay->m_fGOOverlayTimer < 0)
		{
			if (m_pHighScore->IsEmpty())
			{
				m_pIniParser->LoadHighScore("highscore.ini");
			}
			if (m_iScore > m_pHighScore->GetLowestScore())
			{
				m_state = SCOREINPUT;
				m_pScoreInput->Initialise();
			}
			else
			{
				m_state = MENU;
			}
			m_pGOOverlay->m_fGOOverlayTimer = 10;
		}
		break;
	case SCORE:
		break;
	case COMPLETE:
		m_pCompleteOverlay->m_fCompleteOverlayTimer -= deltaTime;
		if (m_pCompleteOverlay->m_fCompleteOverlayTimer < 0)
		{
			if (m_iScore > m_pHighScore->GetLowestScore())
			{
				m_state = SCOREINPUT;
				m_pScoreInput->Initialise();
			}
			else
			{
				m_state = MENU;
			}

			m_pCompleteOverlay->m_fCompleteOverlayTimer = 10;
		}
		break;
	case SCOREINPUT:
		m_pScoreInput->Process(deltaTime);
		break;
	default:
		break;
	}
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	switch (m_state)
	{
	case SPLASH:
		m_pSplash->Draw(backBuffer);
		break;
	case MENU:
		m_pMenu->Draw(backBuffer);
		break;
	case GAMEPLAY:
	case PAUSED:
		// Playership
		if (!m_pPlayership->IsDead())
		{
			m_pPlayership->Draw(backBuffer);
		}

		// Enemies
		for (size_t i = 0; i < m_vEnemies.size(); i++)
		{
			if (!m_vEnemies[i]->IsDead())
			{
				m_vEnemies[i]->Draw(backBuffer);
			}
		}

		// Pods
		for (size_t i = 0; i < m_vPods.size(); i++)
		{
			if (!m_vPods[i]->IsDead())
			{
				m_vPods[i]->Draw(backBuffer);
			}
		}

		// Collectible
		if (m_pCollectible)
		{
			if (!m_pCollectible->IsDead())
			{
				m_pCollectible->Draw(backBuffer);
			}
		}

		// Bullets
		for (size_t i = 0; i < m_vBullets.size(); i++)
		{
			if (!m_vBullets[i]->IsDead())
			{
				m_vBullets[i]->Draw(backBuffer);
			}
		}

		// Explosion
		for (size_t i = 0; i < m_vExplosion.size(); i++)
		{
			if (m_vExplosion[i]->GetAnimatedSprite()->IsAnimating())
			{
				m_vExplosion[i]->Animate(backBuffer);
			}
		}

		// Particles
		if (m_pParticleEmitter->HasParticles())
		{
			m_pParticleEmitter->Draw(backBuffer);
		}

		m_pOverlay->Draw(backBuffer);
		if (m_state == PAUSED)
		{
			m_pPauseMenu->Draw(backBuffer);
			m_pOverlay->Draw(backBuffer);
		}
		break;
	case LEVELINGUP:
		m_pLevelingUpOverlay->Draw(backBuffer);
		break;
	case GAMEOVER:
		m_pGOOverlay->Draw(backBuffer);
		break;
	case SCORE:
		m_pScoreScreen->Draw(backBuffer);
		break;
	case COMPLETE:
		m_pCompleteOverlay->Draw(backBuffer);
		break;
	case SCOREINPUT:
		m_pScoreInput->Draw(backBuffer);
		break;
	case S_CONTROLS:
		m_pOptionsMenu->Draw(backBuffer);
	default:
		break;
	}
	
	backBuffer.Present();
}

bool
Game::CheckCollision(Entity* entityOne, Entity* entityTwo)
{
	return entityOne->IsCollidingWith(*entityTwo);
}

void
Game::StartLevel()
{
	// Playership instance
	m_pPlayership = new Playership();
	m_pPlayership->Initialise(m_pPlayershipSprite);
	m_pPlayership->SetPosition(static_cast <float> (width / 2), (height - 100.0f - m_pPlayershipSprite->GetHeight()));
	
	// Enemy Instance
	std::vector<Enemy*> emptyEnemy;
	m_vEnemies.swap(emptyEnemy);
	for (int i = 0; i < m_pIniParser->GetValueAsInt(std::to_string(m_iLevel), "enemies"); i++)
	{
		Enemy* enemy = new Enemy();
		enemy->Initialise(m_pEnemyshipSprite);
		enemy->SetPosition(static_cast <float> (width / 2), static_cast <float> (-m_pEnemyshipSprite->GetHeight()));

		m_vEnemies.push_back(enemy);
	}

	// Pod instance
	std::vector<Pod*> emptyPods;
	m_vPods.swap(emptyPods);
	for (int i = 0; i < m_pIniParser->GetValueAsInt("pod", "number"); i++)
	{
		Pod* pod = new Pod();
		pod->Initialise(m_pPodSprite);
		pod->SetPosition(static_cast <float> (rand() % width), rand() % height - 100.0f);
		pod->SetHorizontalVelocity(rand() % 600 - 300.0f);
		pod->SetVerticalVelocity(rand() % 600 - 300.0f);

		m_vPods.push_back(pod);
	}

	// Collectible Instance
	m_pCollectible = new Collectible();
	m_pCollectible->Initialise(m_pAmmoSprite);
	m_pCollectible->Kill();

	std::vector<Bullet*> emptyBullets;
	m_vBullets.swap(emptyBullets);
}

void
Game::LevelUp()
{
	m_iLevel++;

	// Kill Spaceship
	delete m_pPlayership;
	m_pPlayership = 0;

	// Kill All Enemies
	for (auto pEnemy = m_vEnemies.begin(); pEnemy != m_vEnemies.end();)
	{
		delete *pEnemy;
		pEnemy = m_vEnemies.erase(pEnemy);
	}

	// Kill All Bullets
	for (auto pBullet = m_vBullets.begin(); pBullet != m_vBullets.end();)
	{
		delete *pBullet;
		pBullet = m_vBullets.erase(pBullet);
	}

	delete m_pCollectible;
	m_pCollectible = 0;

	if (m_pParticleEmitter->HasParticles())
	{
		m_pParticleEmitter->KillParticles();
	}

	m_pSoundSystem->playSound(m_pLevelUpSound, 0, false, &m_pChannel);

	if (m_iLevel > 45)
	{
		WinGame();
	}
	else
	{
		m_pOverlay->LevelUp();

		m_state = LEVELINGUP;
	}
}

int
Game::GetLevel()
{
	return m_iLevel;
}

int
Game::GetScore()
{
	return m_iScore;
}

void
Game::Respawn()
{
	delete m_pPlayership;
	m_pPlayership = 0;

	m_pPlayership = new Playership();
	m_pPlayership->Initialise(m_pPlayershipSprite);
	m_pPlayership->SetPosition(static_cast <float> (width / 2), height - 100.0f - m_pPlayershipSprite->GetHeight());
	m_pPlayership->SetInvincibleTimer(3);
	m_pPlayership->SetInvincibility(true);

	m_iBullets = 0;
	m_pOverlay->SetBullets(m_iBullets);
}

void
Game::SetSpaceshipHorizontalSpeed(float speed)
{
	m_pPlayership->SetHorizontalVelocity(speed);
	if (speed < 0)
	{
		m_pPlayership->SetDirection(LEFT);
	}
	else if (speed > 0)
	{
		m_pPlayership->SetDirection(RIGHT);
	}
}

void
Game::SetSpaceshipVerticalSpeed(float speed)
{
	m_pPlayership->SetVerticalVelocity(speed);
}

void
Game::StopSpaceshipHorizontal()
{
	m_pPlayership->SetHorizontalVelocity(0);
}

void
Game::StopSpaceshipVertical()
{
	m_pPlayership->SetVerticalVelocity(0);
}

void
Game::FireBullet()
{
	if (m_iBullets > 0)
	{
		m_pSoundSystem->playSound(m_pBulletShotSound, 0, false, &m_pChannel);
		// Create Bullet
		Bullet* bullet = new Bullet();
		bullet->Initialise(m_pBulletSprite);
		bullet->SetPosition(m_pPlayership->GetPositionX() + (m_pPlayershipSprite->GetHeight() / 2) - (m_pBulletSprite->GetHeight() / 2),
			m_pPlayership->GetPositionY() + (m_pPlayershipSprite->GetHeight() / 2) - (m_pBulletSprite->GetHeight() / 2));

		// Set Velocity
		if (m_pPlayership->GetDirection() == LEFT)
		{
			bullet->SetHorizontalVelocity(-900);
		}
		else
		{
			bullet->SetHorizontalVelocity(900);
		}

		// Add to vector
		m_vBullets.push_back(bullet);
		m_iBullets--;
		m_pOverlay->SetBullets(m_iBullets);
	}
}

void
Game::SetPlayerInvincibility(bool invincibility)
{
	m_pPlayership->SetInvincibility(invincibility);
}

void
Game::SpawnCollectible()
{
	m_pSoundSystem->playSound(m_pCollectibleSpawnedSound, 0, false, &m_pChannel);
	m_pCollectible = new Collectible();
	m_pCollectible->SetRandomType();
	m_pCollectible->Initialise(m_pAmmoSprite);
	m_fCollectibleTimer = (rand() % 30) + 10.0f;
}

void
Game::CollectCollectible()
{
	switch (m_pCollectible->GetType())
	{
	case AMMO:
		m_iBullets += 5;
		m_pOverlay->SetBullets(m_iBullets);
		break;
	default:
		break;
	}
	m_pSoundSystem->playSound(m_pPodCollectedSound, 0, false, &m_pChannel);
	m_pCollectible->Kill();
}

void
Game::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom - 50;
}

int
Game::GetHeight()
{
	return height;
}

int
Game::GetWidth()
{
	return width;
}

State
Game::GetState()
{
	return m_state;
}

void
Game::SetState(State state)
{
	m_state = state;
}

void
Game::MenuSelect()
{
	m_pSoundSystem->playSound(m_pMenuSelectSound, 0, false, &m_pChannel);
}

void
Game::MenuAccept()
{
	m_pSoundSystem->playSound(m_pMenuAcceptSound, 0, false, &m_pChannel);
}

void
Game::StartGame()
{
	m_state = GAMEPLAY;
	m_iScore = m_pIniParser->GetValueAsInt("game", "startingScore");
	m_iLives = m_pIniParser->GetValueAsInt("game", "startingLives");
	m_iLevel = m_pIniParser->GetValueAsInt("game", "startingLevel");
	m_iBullets = m_pIniParser->GetValueAsInt("game", "startingBullets");
	m_fCollectibleTimer = m_pIniParser->GetValueAsFloat("game", "collectibleTimer");
	m_pOverlay->SetScore(m_iScore);
	m_pOverlay->SetLives(m_iLives);
	m_pOverlay->SetLevel(m_iLevel);
	m_pOverlay->SetBullets(m_iBullets);
	m_pGOOverlay->SetGOOverlayTimer(Game::GetInstance().GetIniParser()->GetValueAsFloat("game", "gameOverScreenLength"));
	m_pCompleteOverlay->SetCompleteOverlayTimer(Game::GetInstance().GetIniParser()->GetValueAsFloat("game", "gameOverScreenLength"));
	StartLevel();
}

void
Game::LoseGame()
{
	m_state = GAMEOVER;
	delete m_pPlayership;
	m_pPlayership = 0;
	for (size_t i = 0; i < m_vEnemies.size(); i++)
	{
		delete m_vEnemies[i];
		m_vEnemies[i] = 0;
	}
	for (size_t i = 0; i < m_vPods.size(); i++)
	{
		delete m_vPods[i];
		m_vPods[i] = 0;
	}
	for (size_t i = 0; i < m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = 0;
	}
	delete m_pCollectible;
	m_pCollectible = 0;
	
}

void
Game::WinGame()
{
	m_state = COMPLETE;
	delete m_pPlayership;
	m_pPlayership = 0;
	for (size_t i = 0; i < m_vEnemies.size(); i++)
	{
		delete m_vEnemies[i];
		m_vEnemies[i] = 0;
	}
	for (size_t i = 0; i < m_vPods.size(); i++)
	{
		delete m_vPods[i];
		m_vPods[i] = 0;
	}
	for (size_t i = 0; i < m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = 0;
	}
	delete m_pCollectible;
	m_pCollectible = 0;
}

void
Game::PauseGame()
{
	if (m_state != PAUSED)
	{
		m_state = PAUSED;
	}
	else
	{
		m_state = GAMEPLAY;
	}
}

void
Game::ShowScore()
{
	if (m_pHighScore->IsEmpty())
	{
		m_pIniParser->LoadHighScore("highscore.ini");
	}
	m_pScoreScreen->LoadHighScore(m_pHighScore);

	m_state = SCORE;
}

void
Game::ShowControls()
{
	m_state = S_CONTROLS;
}

void
Game::ShowMenu()
{
	m_pSoundSystem->playSound(m_pMenuAcceptSound, 0, false, &m_pChannel);
	m_state = MENU;
}

void 
Game::Quit()
{
	m_looping = false;
}

IniParser*
Game::GetIniParser()
{
	return m_pIniParser;
}

HighScore*
Game::GetHighScoreBoard()
{
	return m_pHighScore;
}

void
Game::AddScore(int x)
{
	if (m_iScore % 5000 > (m_iScore + x) % 5000)
	{
		m_iLives++;
		m_pOverlay->SetLives(m_iLives);
	}

	m_iScore += x;
	m_pOverlay->SetScore(m_iScore);
}

bool
Game::InitialiseSoundSystem()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_pSoundSystem); // Create the main system object
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->init(512, FMOD_INIT_NORMAL, 0); // Initialize FMOD
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/collectible_collected.wav", FMOD_DEFAULT, 0, &m_pPodCollectedSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/collectible_spawned.wav", FMOD_DEFAULT, 0, &m_pCollectibleSpawnedSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/enemy_spaceship_explosion.wav", FMOD_DEFAULT, 0, &m_pEnemyExplosionSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/enemy_spawned.wav", FMOD_DEFAULT, 0, &m_pEnemySpawnedSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/life_gained.wav", FMOD_DEFAULT, 0, &m_pLifeGained);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/player_spaceship_explosion.wav", FMOD_DEFAULT, 0, &m_pPlayerExplosionSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/shooting.wav", FMOD_DEFAULT, 0, &m_pBulletShotSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/menu_select.wav", FMOD_DEFAULT, 0, &m_pMenuSelectSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/menu_accept.wav", FMOD_DEFAULT, 0, &m_pMenuAcceptSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/portal_travel.wav", FMOD_DEFAULT, 0, &m_pLevelUpSound);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	result = m_pSoundSystem->createSound("assets/Interplanetary Odyssey.wav", FMOD_DEFAULT, 0, &m_pMusic);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return (false);
	}

	return (true);
}