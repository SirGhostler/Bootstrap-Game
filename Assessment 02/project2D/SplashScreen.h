#pragma once
#include <memory>
#include "Texture.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Renderer2D.h"

typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;

class SplashScreen : public GameState
{
public:
	SplashScreen();
	~SplashScreen();

	bool onUpdate(float deltaTime) override;
	void onDraw(aie::Renderer2D* renderer) override;

	void SetDisplayTime(float time) { m_screenDisplayTime = time; m_remainingDisplayTime = m_screenDisplayTime; }
protected:
	ResourceManager<aie::Texture>	m_images;

private:
	float m_screenDisplayTime = 2.0f;
	float m_remainingDisplayTime;
	
	TexturePtr		m_GKLogo;
};