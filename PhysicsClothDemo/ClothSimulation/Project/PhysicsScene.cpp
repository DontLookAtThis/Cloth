#include "PhysicsScene.h"
#include "ClothNode.h"
#include "Cloth.h"
#include "Engine/Camera.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteRender.h"
#include "Engine/AssetMgr.h"


#include "Engine/Input.h"
CPhysicsScene::CPhysicsScene()
{

}

CPhysicsScene::~CPhysicsScene()
{
	
}

void CPhysicsScene::ConfigurateScene(bool _bPhysicsEnabled)
{
	__super::ConfigurateScene(_bPhysicsEnabled);


	m_mainCamera = new CCamera();

	cloth = new CCloth();
	cloth->SetWorld(this);
	cloth->ResetNodes();
	cloth->ResizeCloth(20, 20);
	cloth->InitializeVertices();
	cloth->InitializeIndices();
	cloth->IntializeConnectionsSquares();
	cloth->InitializeRender();

}

void CPhysicsScene::ConfigurateScene()
{
	__super::ConfigurateScene();


	m_mainCamera = new CCamera();
	cloth = new CCloth();
	cloth->SetWorld(this);
	//Setting Transform
	cloth->SetLocation(glm::vec3(-100, -100, 0));
	cloth->SetScale(glm::vec3(2, 2, 2));
	cloth->SetRotation(glm::vec3(0, 0, 0));

	cloth->ResetNodes();
	cloth->ResizeCloth(20, 20);
	cloth->InitializeVertices();
	cloth->InitializeIndices();
	cloth->IntializeConnectionsSquares();
	cloth->InitializeRender();

	CGameObject* Ground;
	Ground = new CGameObject();
	Ground->SetWorld(this);
	//Setting Transform
	Ground->SetLocation(glm::vec3(0, 10, -2));
	Ground->SetScale(glm::vec3(5, 5, 1));
	Ground->SetRotation(glm::vec3(90, 0,90 ));

	Ground->CreateComponent<CSpriteRender>();
	Ground->GetComponent<CSpriteRender>()->SetSprite(CAssetMgr::GetInstance()->GetSprite("WoodBlock"));
	m_vGameObj.push_back(Ground);

}

void CPhysicsScene::UpdateScene(float _tick)
{
	__super::UpdateScene(_tick);


	if (CInput::GetInstance()->g_cKeyState['w'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.z -= 0.1f;
	}
	else if(CInput::GetInstance()->g_cKeyState['s'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.z += 0.1f;
	}

	if (CInput::GetInstance()->g_cKeyState['d'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.x -= 0.1f;
	}
	else if (CInput::GetInstance()->g_cKeyState['a'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.x += 0.1f;
	}
}

void CPhysicsScene::RenderScene()
{
	__super::RenderScene();

	cloth->RenderCloth();
}
