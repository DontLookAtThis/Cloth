// This Include
#include "GameObject.h"

// Local Include
#include "Component.h"
#include "RigidBody2D.h"
#include "SpriteRender.h"
#include "Scene.h"


CGameObject::CGameObject()
{
	m_ShouldDestroyed = false;
	m_isActive = true;
	m_isUpdating = true;
	m_iHealth = 100;
	m_isAlive = true;
}

CGameObject::~CGameObject()
{

}

void CGameObject::SetWorld(CScene * world)
{
	m_Scene = world;
}

void CGameObject::BeginPlay()
{
	for (auto iter : m_components)
	{
		iter->BeginPlay();
	}
}

void CGameObject::Update(float _tick) 
{
	for (auto iter : m_components)
	{
		iter->Update(_tick);
	}
	if (m_iHealth <= 0 && m_isAlive == true)
	{
		m_isAlive = false;
		for (auto it: m_components)
		{
			if (dynamic_cast<CSpriteRender*>(it))
			{

			}
			else if (CRigiBody2D* body = dynamic_cast<CRigiBody2D*>(it))
			{

			}
		}
		//std::cout << "dead" << std::endl;
	}
}

void CGameObject::DestroyObject()
{
	this->m_ShouldDestroyed = true;
}

bool CGameObject::IsActive() const
{
	return m_isActive;
}

void CGameObject::SetActive(bool _b)
{
	m_isActive = _b;

	for (auto component : m_components)
	{
		component->SetActive(_b);
	}
}

bool CGameObject::IsUpdating() const
{
	return m_isUpdating;
}

void CGameObject::SetUpdating(bool _b)
{
	m_isUpdating = _b;
}

void CGameObject::TakeDamage(int _damage)
{
	m_iHealth -= _damage;
}

void CGameObject::SetLocation(glm::vec3 _LocationVec3)
{
	m_transform.position = _LocationVec3;
}

void CGameObject::SetRotation(glm::vec3 _RotationAxisVec3)
{
	m_transform.rotation = _RotationAxisVec3;
}

void CGameObject::SetScale(glm::vec3 _ScaleVec3)
{
	m_transform.scale = _ScaleVec3;
}

glm::vec3 CGameObject::GetLocation()
{
	return m_transform.position;
}

glm::vec3 CGameObject::GetRotation()
{
	return m_transform.rotation;
}

glm::vec3 CGameObject::GetScale()
{
	return m_transform.scale;
}

CScene * CGameObject::GetScene()
{
	if (m_Scene)
	{
		return m_Scene;
	}
	return nullptr;
}

void CGameObject::OnCollisionEnter(CGameObject * CollidedObject)
{
}

void CGameObject::OnColliisionExit(CGameObject * CollidedObject)
{
}

bool CGameObject::ShouldDestroyed() const
{
	return m_ShouldDestroyed;
}