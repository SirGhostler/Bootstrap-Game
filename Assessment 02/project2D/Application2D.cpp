#include "Application2D.h"

// Including All Resources
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Object.h"

// Including Math
#include "Vector2.h"

// Including Game States
#include "eGameState.h"
#include "SplashScreen.h"
#include "MainMenu.h"

#include <iostream>

Application2D::Application2D()
{
}

Application2D::~Application2D()
{
}

bool Application2D::startup()
{
	//=========================================================
	// Create Game States
	gameStateManager = new GameStateManager((int)eGameState::STATE_COUNT);
	gameStateManager->registerState((int)eGameState::SPLASH, new SplashScreen());
	gameStateManager->registerState((int)eGameState::MAINMENU, new MainMenu());

	gameStateManager->pushState((int)eGameState::MAINMENU);
	gameStateManager->pushState((int)eGameState::SPLASH);
	
	//=========================================================

	//=========================================================
	// Create Collision
	box1 = AABB(30, 104, 15, 52);
	box2 = AABB(30, 104, 15, 52);
	box3 = AABB(28, 28, 14, 14);
	//=========================================================
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	TexturePtr m_ShipTexture = m_images.get("./textures/ship.png");
	TexturePtr m_PongPaddleTexture = m_images.get("./textures/pong.png");
	TexturePtr m_PongBallTexture = m_images.get("./textures/pongball.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_audio = new aie::Audio("./audio/powerup.wav");
	m_paddle = new aie::Audio("./audio/ballhitpaddle.wav");
	m_wall = new aie::Audio("./audio/ballhitwall.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	std::cout << "images loaded: " << m_images.getCount() << std::endl;
	std::cout << "fonts loaded: " << m_fonts.getCount() << std::endl;

//============================================================
// AIE Objects
//============================================================
	//m_Parent = new Object(Vector3(320, 300, 1), 0, m_ShipTexture);
	//m_Parent->SetSpeed(0);
	//m_Parent->SetRotation(0);

	//m_Child = new Object(Vector3(640, 300, 1), 0, m_ShipTexture);
	//m_Child->SetSpeed(0);
	//m_Child->SetRotation(0);
	//m_Child->SetParent(m_Parent);
	//m_Child->bflipped = true;
	
//============================================================
// Pong Objects
//============================================================
	m_PongPaddleP1 = new Object(Vector3(50, 360, 1), 0, m_PongPaddleTexture);
	m_PongPaddleP1->SetSpeed(0);
	m_PongPaddleP1->SetRotation(0);

	m_PongPaddleP2 = new Object(Vector3(1230, 360, 1), 0, m_PongPaddleTexture);
	m_PongPaddleP2->SetSpeed(0);
	m_PongPaddleP2->SetRotation(0);

	m_PongBall = new Object(Vector3(640, 360, 1), 0, m_PongBallTexture);
	m_PongBall->SetSpeed(0);
	m_PongBall->SetRotation(0);
	
	return true;
}

void Application2D::shutdown()
{	
	std::cout << "images loaded: " << m_images.getCount() << std::endl;
	//delete m_player;
	m_images.collectGarbage();
	std::cout << "images loaded: " << m_images.getCount() << std::endl;

	delete m_audio;
	delete m_font;
	delete m_PongPaddleP1;
	delete m_PongPaddleP2;
	delete m_PongBall;
	//delete m_Parent;
	//delete m_Child;

	delete m_2dRenderer;
}

void Application2D::update(float deltaTime)
{
	m_timer += deltaTime;
	// input example
	aie::Input* input = aie::Input::getInstance();
	 //m_Parent->Update(deltaTime);
	 //m_Child->Update(deltaTime);

	gameStateManager->update(deltaTime);

	float paddleSpeed = 420.0f;

//============================================================
// Collision:
//============================================================
// Hitbawxes
	// Ball collision with Player 1
	isColliding = AABB::CollisionCheck(box1, box3);
	if (AABB::CollisionCheck(box1, box3))
	{
		std::cout << "Collision! Ball has collided with Player 1!" << std::endl;
	}
	if (box1.CollidesWith(box3))
	{
		std::cout << "Player 1 collision with Ball! - Member wise!" << std::endl;
	}

	// Ball collision with Player 2
	isColliding = AABB::CollisionCheck(box2, box3);

	if (AABB::CollisionCheck(box2, box3))
	{
		std::cout << "Collision! Ball has collided with Player 2!" << std::endl;
	}
	if (box2.CollidesWith(box3))
	{
		std::cout << "Player 2 collision with Ball! - Member wise!" << std::endl;
	}

	// Reads out hit turn and hit count for the ball
	std::cout << "Ball Hit Turn: " << ballHasBeenHitBy << std::endl;
	std::cout << "Ball Hit Count: " << ballHits	<< std::endl;
	std::cout << "Ball Fwd Speed: " << ballSpeedHor << std::endl;
	std::cout << "Ball Upw Speed: " << ballSpeedVer << std::endl;

	if (box1.CollidesWith(box3) || box2.CollidesWith(box3))
	{
		++ballHits;
		if (ballHasBeenHitBy == 0)
		{
			ballHasBeenHitBy = 1;
			m_PongBall->m_GlobalTransform->position.v3x = m_PongBall->m_GlobalTransform->position.v3x - (15 + ballHits * deltaTime);
		}
		else if (ballHasBeenHitBy == 1)
		{
			ballHasBeenHitBy = 0;
			m_PongBall->m_GlobalTransform->position.v3x = m_PongBall->m_GlobalTransform->position.v3x + (15 + ballHits * deltaTime);
		}
	}

//============================================================
// Ball and Paddle Velocity/Position:
//============================================================
// Speed, yada yada. Oh, and inputs
	// Increments the horizontal speed of the ball on each hit with the paddle
	if (ballHasBeenHitBy == 0)
	{
		ballSpeedHor = 200.0f + (ballHits * 40.0f);
	}
	if (ballHasBeenHitBy == 1)
	{
		ballSpeedHor = -200.0f - (ballHits * 40.0f);
	}

	// Clamps the horizontal speed
	if (ballSpeedHor > 850.0f && ballHasBeenHitBy == 0)
	{
		ballSpeedHor = 850.0f;
	}
	if (ballSpeedHor < -850.0f && ballHasBeenHitBy == 1)
	{
		ballSpeedHor = -850.0f;
	}

	// Sets the vertical speed of the ball
	// Top
	if (box1.CollidesWith(box3) && (m_PongBall->m_GlobalTransform->position.v3y > m_PongPaddleP1->m_GlobalTransform->position.v3y + (box1.halfHeight - box3.halfHeight)) ||
		box2.CollidesWith(box3) && (m_PongBall->m_GlobalTransform->position.v3y > m_PongPaddleP2->m_GlobalTransform->position.v3y + (box2.halfHeight - box3.halfHeight)))
	{
		++ballHits;
		ballSpeedVer = 2.0f;
	}

	// Bottom
	if (box1.CollidesWith(box3) && (m_PongBall->m_GlobalTransform->position.v3y < m_PongPaddleP1->m_GlobalTransform->position.v3y - (box1.halfHeight - box3.halfHeight)) ||
		box2.CollidesWith(box3) && (m_PongBall->m_GlobalTransform->position.v3y < m_PongPaddleP2->m_GlobalTransform->position.v3y - (box2.halfHeight - box3.halfHeight)))
	{
		++ballHits;
		ballSpeedVer = -2.0f;
	}

	// Clamps the vertical speed
	if (ballSpeedVer > 100.0f)
	{
		ballSpeedVer = 100.0f;
	}
	if (ballSpeedVer < -100.0f)
	{
		ballSpeedVer = -100.0f;
	}

	// Flip ball ver speed
	if ((m_PongBall->m_GlobalTransform->position.v3y >= 720) || (m_PongBall->m_GlobalTransform->position.v3y <= 0))
	{
		ballSpeedVer = -ballSpeedVer;
	}

	// Set ball speed for both angles
	m_PongBall->m_GlobalTransform->position = m_PongBall->m_GlobalTransform->position + (m_PongBall->m_GlobalTransform->right * ballSpeedHor * deltaTime);
	m_PongBall->m_GlobalTransform->position.v3y = m_PongBall->m_GlobalTransform->position.v3y + (50.0f * ballSpeedVer * deltaTime);

	// Paddle
	// Controls/Inputs
	if (input->isKeyDown(aie::INPUT_KEY_UP) && m_PongPaddleP1->m_GlobalTransform->position.v3y < 650)
	 {
		 m_PongPaddleP1->m_GlobalTransform->position = m_PongPaddleP1->m_GlobalTransform->position + (m_PongPaddleP1->m_GlobalTransform->forward * paddleSpeed * deltaTime);
	 }
	if (input->isKeyDown(aie::INPUT_KEY_DOWN) && m_PongPaddleP1->m_GlobalTransform->position.v3y > 70)
	{
		m_PongPaddleP1->m_GlobalTransform->position = m_PongPaddleP1->m_GlobalTransform->position + (m_PongPaddleP1->m_GlobalTransform->forward * -paddleSpeed * deltaTime);
	}

	box1.v2Position = Vector2(m_PongPaddleP1->m_GlobalTransform->position.v3x, m_PongPaddleP1->m_GlobalTransform->position.v3y);

	if (input->isKeyDown(aie::INPUT_KEY_W) && m_PongPaddleP2->m_GlobalTransform->position.v3y < 650)
	{
		m_PongPaddleP2->m_GlobalTransform->position = m_PongPaddleP2->m_GlobalTransform->position + (m_PongPaddleP2->m_GlobalTransform->forward * paddleSpeed * deltaTime);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S) && m_PongPaddleP2->m_GlobalTransform->position.v3y > 70)
	{
		m_PongPaddleP2->m_GlobalTransform->position = m_PongPaddleP2->m_GlobalTransform->position + (m_PongPaddleP2->m_GlobalTransform->forward * -paddleSpeed * deltaTime);
	}

	box2.v2Position = Vector2(m_PongPaddleP2->m_GlobalTransform->position.v3x, m_PongPaddleP2->m_GlobalTransform->position.v3y);
	box3.v2Position = Vector2(m_PongBall->m_GlobalTransform->position.v3x, m_PongBall->m_GlobalTransform->position.v3y);

//============================================================
// SOUND:
//============================================================
	///Ball.y - Paddle.y + HalfPaddleHeight
	///Ball.y - Paddle.y - HalfPaddleHeight

	if (box1.CollidesWith(box3) || box2.CollidesWith(box3))
		m_paddle->play();

	if ((m_PongBall->m_GlobalTransform->position.v3y >= 720) || (m_PongBall->m_GlobalTransform->position.v3y <= 0))
		m_wall->play();

//============================================================
// GAME OVER:
//============================================================
// If the ball hits either end of the screen
	// Player 1
	if (m_PongBall->m_GlobalTransform->position.v3x > 1280)
	{
		std::cout << "Game Over! Player 1 wins!" << std::endl;
	}
	// Player 2
	if (m_PongBall->m_GlobalTransform->position.v3x < 0)
	{
		std::cout << "Game Over! Player 2 wins!" << std::endl;
	}

	// if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	// {
	//	 float rotationSpeed = 5.0f;
	//	 Matrix3 rotation;
	//	 rotation.setRotateZ(rotationSpeed * deltaTime);
	//	 *m_Parent->m_GlobalTransform = *m_Parent->m_GlobalTransform * rotation;
	// }

	// if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	// {	 
	//	 float rotationSpeed = -5.0f;
	//	 Matrix3 rotation;
	//	 rotation.setRotateZ(rotationSpeed * deltaTime);
	//	 *m_Parent->m_GlobalTransform = *m_Parent->m_GlobalTransform * rotation;
	// }

	// if (input->isKeyDown(aie::INPUT_KEY_W))
	// {
	///*	 m_Child->m_LocalTransform->position = m_Child->m_LocalTransform->position + (m_Child->m_LocalTransform->forward * 50.0f * deltaTime);*/
	//	 box1.y += speed * deltaTime;
	// }

	// if (input->isKeyDown(aie::INPUT_KEY_S))
	// {
	///*	 m_Child->m_LocalTransform->position = m_Child->m_LocalTransform->position + (m_Child->m_LocalTransform->forward * 50.0f * -deltaTime);*/
	//	 box1.y -= speed * deltaTime;
	// }

	// if (input->isKeyDown(aie::INPUT_KEY_A))
	// {
	//	 //float rotationSpeed = 5.0f;
	//	 //Matrix3 rotation;
	//	 //rotation.setRotateZ(rotationSpeed * deltaTime);
	//	 //*m_Child->m_LocalTransform = *m_Child->m_LocalTransform * rotation;
	//	 box1.x -= speed * deltaTime;
	// }

	// if (input->isKeyDown(aie::INPUT_KEY_D))
	// {
	//	 //float rotationSpeed = -5.0f;
	//	 //Matrix3 rotation;
	//	 //rotation.setRotateZ(rotationSpeed * deltaTime);
	//	 //*m_Child->m_LocalTransform = *m_Child->m_LocalTransform * rotation;
	//	 box1.x += speed * deltaTime;
	// }

	// *m_Child->m_GlobalTransform = *m_Parent->m_GlobalTransform * *m_Child->m_LocalTransform;

//============================================================
// GENERAL:
//============================================================
	// example of audio
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		m_audio->play();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	Vector2 shipInterp;
	shipT += (deltaTime / 5.0f) * shipDir;

	if (shipT < 0)
	{
		shipDir = 1;
		shipT = 0;
	}

	else if(shipT > 1)
	{
		shipDir = -1;
		shipT = 1;
	}

	shipXPos = shipInterp.linearInterpolation(0.0f, (float)getWindowWidth(), shipT);
}

void Application2D::draw()
{
	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	gameStateManager->draw(m_2dRenderer);
	// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0, 0, 1, 1);

	//m_2dRenderer->drawSprite(m_shipTexture, shipXPos, 400, 0, 0, m_timer, 1);

	//m_Parent->Draw(m_2dRenderer);

	//m_Child->Draw(m_2dRenderer);

	m_PongBall->Draw(m_2dRenderer);

	m_2dRenderer->setRenderColour(0, 0, 1);
	m_PongPaddleP1->Draw(m_2dRenderer);

	m_2dRenderer->setRenderColour(1, 0, 0);
	m_PongPaddleP2->Draw(m_2dRenderer);

	m_2dRenderer->setRenderColour(1, 1, 1);

	// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);
	
	// output some text, uses the last used colour
	 //char fps[32];
	 //sprintf_s(fps, 32, "FPS: %i", getFPS());
	 //m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	 //m_2dRenderer->drawText(m_font, "Press Space for sound!", 0, 720 - 64);

	if (isColliding)
	{
		m_2dRenderer->setRenderColour(1, 1, 0);
	}
	DrawAABB(box1, m_2dRenderer);
	DrawAABB(box2, m_2dRenderer);
	DrawAABB(box3, m_2dRenderer);
	m_2dRenderer->setRenderColour(1, 1, 1);

	// done drawing sprites
	m_2dRenderer->end();
}

void Application2D::DrawAABB(const AABB& a_AABB, aie::Renderer2D* a_Renderer)
{
	// LHS
	a_Renderer->drawLine(a_AABB.x - a_AABB.halfWidth, a_AABB.y - a_AABB.halfHeight,
		a_AABB.x - a_AABB.halfWidth, a_AABB.y + a_AABB.halfHeight);
	// Top
	a_Renderer->drawLine(a_AABB.x - a_AABB.halfWidth, a_AABB.y + a_AABB.halfHeight,
		a_AABB.x + a_AABB.halfWidth, a_AABB.y + a_AABB.halfHeight);
	// RHS
	a_Renderer->drawLine(a_AABB.x + a_AABB.halfWidth, a_AABB.y + a_AABB.halfHeight,
		a_AABB.x + a_AABB.halfWidth, a_AABB.y - a_AABB.halfHeight);
	// LHS
	a_Renderer->drawLine(a_AABB.x + a_AABB.halfWidth, a_AABB.y - a_AABB.halfHeight,
		a_AABB.x - a_AABB.halfWidth, a_AABB.y - a_AABB.halfHeight);
}