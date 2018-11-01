// This include
#include "SpriteRender.h"

// Local Include
#include "GameObject.h"
#include "Sprite.h"
#include "AssetMgr.h"

CSpriteRender::CSpriteRender() 
{
	m_sprite = CAssetMgr::GetInstance()->GetSprite("DefaultSprite");
	m_programID = CAssetMgr::GetInstance()->GetProgramID("DefaultSpriteProgram");
	xMultiplier = 1.0f;
	yMultiplier = 1.0f;
	bSpriteActive = true;
}

CSpriteRender::~CSpriteRender() {}

void CSpriteRender::BeginPlay()
{
	__super::BeginPlay();
}

void CSpriteRender::Render(CCamera* _camera)
{
	
	if (GetOwner()->IsActive() == false
		|| m_sprite == nullptr || bSpriteActive == false)
	{
		return;
	}

	m_sprite->RenderSprite(GetOwner()->m_transform, 
		_camera, m_programID, xMultiplier, yMultiplier);
}

void CSpriteRender::SetSprite(CSprite* _sprite)
{
	m_sprite = _sprite;
}

void CSpriteRender::SetSprite(std::string _name)
{
	m_sprite = CAssetMgr::GetInstance()->GetSprite(_name);
}

void CSpriteRender::SetProgram(GLuint _programID)
{
	m_programID = _programID;
}

CSprite* CSpriteRender::GetSprite()
{
	if (m_sprite)
	{
		return m_sprite;
	}
	return nullptr;
}
