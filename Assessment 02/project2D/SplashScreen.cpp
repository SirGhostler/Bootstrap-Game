#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	m_GKLogo = m_images.get("./textures/GKLogo.png");
	m_remainingDisplayTime = m_screenDisplayTime;
}

SplashScreen::~SplashScreen()
{
}

bool SplashScreen::onUpdate(float deltaTime)
{
	if (m_remainingDisplayTime < 0)
	{
		exit();
		return true;
	}
	else
	{
		m_remainingDisplayTime -= deltaTime;
		return false;
	}
}

void SplashScreen::onDraw(aie::Renderer2D* renderer)
{
	renderer->drawSprite(m_GKLogo->get(), 0, 0, 1280, 720, 0, 0, 0.0f, 0.0f);
}