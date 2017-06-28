#include "Object.h"

Object::Object(Vector3& a_pos, const float a_fRotation, TexturePtr a_Texture)
{
	// Init Matrix to Identify
	m_LocalTransform = new Matrix3();

	// Set Facing
	m_LocalTransform->setRotateZ(a_fRotation);

	// Set Facing
	m_v3Direction = m_LocalTransform->forward;

	// Set Position
	m_LocalTransform->position = a_pos;
	(*m_LocalTransform)[2] = a_pos;

	// Set Texture
	m_texture = a_Texture;

	m_GlobalTransform = new Matrix3();
	*m_GlobalTransform = *m_LocalTransform;

	m_Children = new std::vector<Object*>();
}

void Object::Update(const float a_fDeltaTime)
{
	if (m_Parent)
	{
		*m_GlobalTransform = *(m_Parent->m_GlobalTransform) * *m_LocalTransform;
		// m_GlobalTransform->position += m_v3Velocity * a_fDeltaTime
		// (*m_GlobalTransform)[2] // Position Column
		//m_GlobalTransform->position = m_GlobalTransform->position + (m_v3Velocity * a_fDeltaTime);
		// Update last Local Position due to Global update
		//m_LocalTransform->position = m_Parent->m_GlobalTransform->position - m_GlobalTransform->position;
	}
	else
	{
		m_LocalTransform->position = m_LocalTransform->position + (m_v3Velocity * a_fDeltaTime);
		*m_GlobalTransform = *m_LocalTransform;
	}
	// Update Children
	for (int i = 0; i < (int)m_Children->size(); ++i)
	{
		m_Children->at(i)->Update(a_fDeltaTime);
	}
}

void Object::Draw(aie::Renderer2D* a_Render)
{
	if (bflipped)
	{
		a_Render->setUVRect(0, 0, -1, 1);
	}

	a_Render->drawSpriteTransformed3x3(m_texture.get()->get(), (float*)m_GlobalTransform);
	a_Render->setUVRect(0, 0, 1, 1);

	for (int i = 0; i < (int)m_Children->size(); ++i)
	{
		m_Children->at(i)->Draw(a_Render);
	}
}

void Object::SetSpeed(const float a_fSpeed)
{
	m_fSpeed = a_fSpeed;
	m_v3Velocity = a_fSpeed * m_GlobalTransform->forward;
}

void Object::SetRotation(const float a_fRotation)
{
	m_LocalTransform->setRotateZ(a_fRotation);
	m_v3Velocity = m_fSpeed * m_LocalTransform->forward;
}

void Object::SetParent(Object* a_Parent)
{
	if (a_Parent)
	{
		if (a_Parent)
		{
			//m_Parent->m_Children->erase();
		}
		// Set Parent
		m_Parent = a_Parent;
		// Update Positional Offset in Local
		m_LocalTransform->position = m_LocalTransform->position - m_Parent->m_GlobalTransform->position;
		m_LocalTransform->position.v3z = 1;
		// Update Rotational Offset in Local

		m_Parent->m_Children->push_back(this);
	}
}

Object::~Object()
{
	delete m_LocalTransform;
	delete m_GlobalTransform;
}
