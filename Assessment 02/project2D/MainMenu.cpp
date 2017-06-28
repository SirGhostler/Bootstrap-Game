#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_Background = m_images.get("./textures/MainMenuBackground.png");
	m_Text = m_font.get("./font/consolas.ttf", 32);
	m_remainingDisplayTime = m_screenDisplayTime;
}


MainMenu::~MainMenu()
{
}

bool MainMenu::onUpdate(float deltaTime)
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

void MainMenu::onDraw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_Background->get(), 0, 0, 1280, 720, 0, 0, 0.0f, 0.0f);
}
