#include "PhysicsScene.h"
#include "ClothNode.h"
#include "Cloth.h"
#include "Engine/Camera.h"
#include "Engine/GameObject.h"
#include "Engine/SpriteRender.h"
#include "Engine/AssetMgr.h"
#include "ClothLink.h"
#include "ClothNode.h"

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
	Ground->SetLocation(glm::vec3(0, 20, -5));
	Ground->SetScale(glm::vec3(30, 6, 1));
	Ground->SetRotation(glm::vec3(90, 0,90 ));

	Ground->CreateComponent<CSpriteRender>();
	Ground->GetComponent<CSpriteRender>()->SetSprite(CAssetMgr::GetInstance()->GetSprite("WoodBlock"));
	m_vGameObj.push_back(Ground);

	m_mainCamera->m_cameraFacing = Ground->GetLocation();

}

void CPhysicsScene::UpdateScene(float _tick)
{
	__super::UpdateScene(_tick);

	cloth->Update(_tick);
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

	if (CInput::GetInstance()->g_cKeyState['r'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.y -= 0.1f;
	}
	else if (CInput::GetInstance()->g_cKeyState['f'] == INPUT_HOLD)
	{
		m_mainCamera->m_cameraPosition.y += 0.1f;
	}

	if (CInput::GetInstance()->g_cKeyState['p'] == INPUT_FIRST_PRESS)
	{
		for (int x = 0; x < cloth->m_Nodes.size(); x++)
		{
			for (int y = 0; y < cloth->m_Nodes[x].size(); y++)
			{
				cloth->m_Nodes[x][y]->bAnchored = false;
			}
		}
	}

	if (CInput::GetInstance()->g_cKeyState['k'] == INPUT_FIRST_PRESS)
	{
		int random = rand() % cloth->m_links.size();

		cloth->m_links[random]->KillLink();
		cloth->ReinitializeIndices();
	}

}

void CPhysicsScene::RenderScene()
{
	__super::RenderScene();

	cloth->RenderCloth();
}
