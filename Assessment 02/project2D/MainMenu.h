#pragma once
#include <memory>
#include "Texture.h"
#include "Font.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Renderer2D.h"

typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;
typedef std::shared_ptr<Resource<aie::Font>> FontPtr;

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	bool onUpdate(float deltaTime) override;
	void onDraw(aie::Renderer2D* renderer) override;

	void SetDisplayTime(float time) { m_screenDisplayTime = time; m_remainingDisplayTime = m_screenDisplayTime; }
protected:
	ResourceManager<aie::Texture>	m_images;
	ResourceManager<aie::Font>		m_font;

private:
	float m_screenDisplayTime = 10.0f;
	float m_remainingDisplayTime;

	TexturePtr		m_Background;
	FontPtr			m_Text;
};