#pragma once
#include "Application.h"
#include "Renderer2D.h"

// Including All Resources
#include "ResourceManager.h"
#include "Player.h"
#include "Audio.h"
#include "Object.h"

// Including Math
#include "AABB.h"
#include "GameStateManager.h"

typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;
typedef std::shared_ptr<Resource<aie::Font>> FontPtr;

class Application2D : public aie::Application
{
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void DrawAABB(const AABB& a_AABB, aie::Renderer2D* a_Renderer);

protected:
	//=========================================================
	// AABB Collision
	AABB box1;
	AABB box2;
	AABB box3;
	bool isColliding;
	//=========================================================

	//=========================================================
	// Resource Manager
	ResourceManager<aie::Texture>	m_images;
	ResourceManager<aie::Font>		m_fonts;
	Player*							m_player;
	//=========================================================

	//=========================================================
	// Game State Manager
	GameStateManager*	gameStateManager;
	//=========================================================

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Texture*		m_bulletCharTexture;
	aie::Texture*		m_saberCharTexture;

	aie::Texture*		m_pongPaddleTexture;
	aie::Texture*		m_pongBallTexture;

	aie::Texture*		m_trainingStageTexture;

	aie::Font*			m_font;
	aie::Audio*			m_audio;
	aie::Audio*			m_paddle;
	aie::Audio*			m_wall;

	float m_cameraX, m_cameraY;
	float m_timer;

	Matrix3 m_ParentTransform;
	Matrix3 m_ParentLocalTransform;
	aie::Texture* m_ParentTexture;

	Matrix3 m_ChildTransform;
	Matrix3 m_ChildLocalTransform;
	aie::Texture* m_ChildTexture;

	float shipXPos = 0;
	float shipT = 0.1f;
	float shipDir = 1;

	Object* m_Parent;
	Object* m_Child;

	Object* m_PongPaddleP1;
	Object* m_PongPaddleP2;
	Object* m_PongBall;

	float ballHits = 0.0f;
	float ballHasBeenHitBy = 0;
	float ballSpeedHor = 200.0f;
	float ballSpeedVer = 0.0f;
};