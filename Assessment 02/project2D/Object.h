#pragma once

#include <vector>
#include "Vector3.h"
#include "Matrix3.h"
#include "Texture.h"

#include "Renderer2D.h"
#include "ResourceManager.h"

typedef std::shared_ptr<Resource<aie::Texture>> TexturePtr;

class Object
{
public:
	Object(Vector3& a_pos, const float a_fRotation, TexturePtr a_Texture);
	virtual ~Object();// = 0 {};

	// Update Position and Rotation as f(Parent)
	// Update Position as f(Velocity)
	// Update Children
	virtual void Update(const float a_fDeltaTime);

	void Draw(aie::Renderer2D* a_Render);
	void SetSpeed(const float a_fSpeed);
	void SetRotation(const float a_fRotation);
	void SetParent(Object* a_Parent);
	bool bflipped = false;

	Object* m_Parent = nullptr;
	std::vector<Object*>* m_Children = nullptr;

	Matrix3* m_GlobalTransform = nullptr;
	Matrix3* m_LocalTransform = nullptr;

	float m_fSpeed = 0.0f;
    Vector3 m_v3Direction = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_v3Velocity = Vector3(0.0f, 0.0f, 0.0f);

private:
	TexturePtr m_texture;
};

