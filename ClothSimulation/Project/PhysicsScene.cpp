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


#include <cmath>
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
	cloth->AnchorTop();
	cloth->InitializeVertices();
	cloth->InitializeIndices();
	cloth->IntializeConnectionsSquares();
	cloth->InitializeRender();

	CGameObject* Ground;
	Ground = new CGameObject();
	Ground->SetWorld(this);
	//Setting Transform
	Ground->SetLocation(glm::vec3(0, 10, -5));
	Ground->SetScale(glm::vec3(30, 6, 1));
	Ground->SetRotation(glm::vec3(90, 0,90 ));

	Ground->CreateComponent<CSpriteRender>();
	Ground->GetComponent<CSpriteRender>()->SetSprite(CAssetMgr::GetInstance()->GetSprite("WoodBlock"));
	m_vGameObj.push_back(Ground);

	m_mainCamera->m_cameraFacing = Ground->GetLocation();

	InitializeSphere();

}

void CPhysicsScene::UpdateScene(float _tick)
{
	__super::UpdateScene(_tick);

	cloth->Update(_tick);
	if (CInput::GetInstance()->g_cKeyState['1'] == INPUT_HOLD)
	{
		CurrentControlState = CAMERA;
	}
	if (CInput::GetInstance()->g_cKeyState['2'] == INPUT_HOLD)
	{
		CurrentControlState = CLOTH;
	}
	if (CInput::GetInstance()->g_cKeyState['3'] == INPUT_HOLD)
	{
		CurrentControlState = SPHERE;
	}
	if (CInput::GetInstance()->g_cKeyState['0'] == INPUT_HOLD)
	{
		ResetScene();
	}

	if (CurrentControlState == CAMERA)
	{
		if (CInput::GetInstance()->g_cKeyState['w'] == INPUT_HOLD)
		{
			m_mainCamera->m_cameraPosition.z -= 0.1f;
		}
		else if (CInput::GetInstance()->g_cKeyState['s'] == INPUT_HOLD)
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
	}

	
	if (CurrentControlState == SPHERE)
	{
		if (CInput::GetInstance()->g_cKeyState['w'] == INPUT_HOLD)
		{
			SphereTransform.position.z += 2.0f;
		}
		else if (CInput::GetInstance()->g_cKeyState['s'] == INPUT_HOLD)
		{
			SphereTransform.position.z -= 2.0f;
		}

		if (CInput::GetInstance()->g_cKeyState['d'] == INPUT_HOLD)
		{
			SphereTransform.position.x -= 2.0f;
		}
		else if (CInput::GetInstance()->g_cKeyState['a'] == INPUT_HOLD)
		{
			SphereTransform.position.x += 2.0f;
		}

		if (CInput::GetInstance()->g_cKeyState['r'] == INPUT_HOLD)
		{
			SphereTransform.position.y -= 2.0f;
		}
		else if (CInput::GetInstance()->g_cKeyState['f'] == INPUT_HOLD)
		{
			SphereTransform.position.y += 2.0f;
		}
	}

	SphereCollision();



	if (CurrentControlState == CLOTH)
	{
		int width = cloth->m_width;
		int height = cloth->m_height;
		if (CInput::GetInstance()->g_cKeyState['p'] == INPUT_FIRST_PRESS)
		{
			for (unsigned int x = 0; x < cloth->m_Nodes.size(); x++)
			{
				for (unsigned int y = 0; y < cloth->m_Nodes[x].size(); y++)
				{
					cloth->m_Nodes[x][y]->bAnchored = false;
				}
			}
		}
		if (CInput::GetInstance()->g_cKeyState['u'] == INPUT_FIRST_PRESS)
		{
			cloth->ReduceAnchorPoints();
		}
		if (CInput::GetInstance()->g_cKeyState['i'] == INPUT_FIRST_PRESS)
		{
			cloth->InCreaseAnchorPoints();
		}
		if (CInput::GetInstance()->g_cKeyState['j'] == INPUT_FIRST_PRESS)
		{
			for (auto it : cloth->m_AnchoredNodes)
			{
				glm::vec3 loc = it->GetLocation();
				loc.x *= 0.9;
				it->SetLocation(loc);
			}
		}
		if (CInput::GetInstance()->g_cKeyState['k'] == INPUT_FIRST_PRESS)
		{
			for (auto it : cloth->m_AnchoredNodes)
			{
				glm::vec3 loc = it->GetLocation();
				loc.x = loc.x / 9 * 10;
				it->SetLocation(loc);
			}
		}
		if (CInput::GetInstance()->g_cKeyState['r'] == INPUT_FIRST_PRESS)
		{
			cloth->ResetNodes();
			cloth->ResizeCloth(21, 20);
			cloth->AnchorTop();
			cloth->InitializeVertices();
			cloth->InitializeIndices();
			cloth->IntializeConnectionsSquares();
			cloth->InitializeRender();
			cloth->ReinitializeIndices();
			return;
		}

		//if (CInput::GetInstance()->g_cKeyState['k'] == INPUT_FIRST_PRESS)
		//{
		//	for (int i = 0; i < 100; i++)
		//	{
		//		int random = rand() % cloth->m_links.size();

		//		cloth->m_links[random]->KillLink();

		//	}
		//}
		if (height - 1 > 0)
		{
			if (CInput::GetInstance()->g_cKeyState['e'] == INPUT_FIRST_PRESS)
			{
				cloth->ResetNodes();
				cloth->ResizeCloth(width + 1, (height));
				cloth->AnchorTop();
				cloth->InitializeVertices();
				cloth->InitializeIndices();
				cloth->IntializeConnectionsSquares();
				cloth->InitializeRender();
				cloth->ReinitializeIndices();
				return;
			}

			if (CInput::GetInstance()->g_cKeyState['q'] == INPUT_FIRST_PRESS)
			{
				cloth->ResetNodes();
				cloth->ResizeCloth(width - 1, (height));
				cloth->AnchorTop();
				cloth->InitializeVertices();
				cloth->InitializeIndices();
				cloth->IntializeConnectionsSquares();
				cloth->InitializeRender();
				cloth->ReinitializeIndices();
				return;
			}
		}
		if (width - 1 > 0)
		{
			if (CInput::GetInstance()->g_cKeyState['w'] == INPUT_FIRST_PRESS)
			{
				cloth->ResetNodes();
				cloth->ResizeCloth(width, (height + 1));
				cloth->AnchorTop();
				cloth->InitializeVertices();
				cloth->InitializeIndices();
				cloth->IntializeConnectionsSquares();
				cloth->InitializeRender();
				cloth->ReinitializeIndices();
				return;
			}

			if (CInput::GetInstance()->g_cKeyState['s'] == INPUT_FIRST_PRESS)
			{
				cloth->ResetNodes();
				cloth->ResizeCloth(width, (height - 1));
				cloth->AnchorTop();
				cloth->InitializeVertices();
				cloth->InitializeIndices();
				cloth->IntializeConnectionsSquares();
				cloth->InitializeRender();
				cloth->ReinitializeIndices();
				return;
			}
		}
	}
}

void CPhysicsScene::RenderScene()
{
	__super::RenderScene();
	RenderSphere();
	cloth->RenderCloth();
}

void CPhysicsScene::InitializeSphere()
{
	fSphereRadius = 50.0f;
	const int sections = 20;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;
	double M_PI = 3.14159265358979;
	float Spherevertices[(sections) * (sections)* vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = float(cos(phi)) * float(sin(theta));
			float y = float(cos(theta));
			float z = float(sin(phi) * sin(theta));

			Spherevertices[offset] = x * fSphereRadius;
			Spherevertices[offset + 1] = y * fSphereRadius;
			Spherevertices[offset + 2] = z * fSphereRadius;

			Spherevertices[offset + 3] = x;
			Spherevertices[offset + 4] = y;
			Spherevertices[offset + 5] = z;

			Spherevertices[offset + 6] = (float)i / (sections - 1);
			Spherevertices[offset + 7] = (float)j / (sections - 1);

			theta += (M_PI / (sections - 1));
			offset += 8;
		}
		phi += (2 * M_PI) / (sections - 1);
	}


	GLuint Sphereindices[(sections) * (sections)* indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; i++)
	{
		for (int j = 0; j < sections; j++)
		{
			Sphereindices[offset] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			Sphereindices[offset + 1] = (((i + 1) % sections) * sections) + (j);
			Sphereindices[offset + 2] = (i * sections) + (j);

			Sphereindices[offset + 3] = (i * sections) + ((j + 1) % sections);
			Sphereindices[offset + 4] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			Sphereindices[offset + 5] = (i * sections) + (j);

			offset += 6;
		}
	}

	offset = 0;
	GLuint VBO;
	GLuint EBO;

	glGenVertexArrays(1, &m_sVAO);
	glBindVertexArray(m_sVAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Spherevertices), Spherevertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Sphereindices), Sphereindices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	m_iSphereIndicesCount = sizeof(Sphereindices) / sizeof(GLuint);

	SphereTransform.position = glm::vec3(0,0,-50);
}

void CPhysicsScene::RenderSphere()
{
	glUseProgram(CAssetMgr::GetInstance()->GetProgramID("SphereProgram"));

	glm::vec3 positionSphere = SphereTransform.position;
	glm::vec3 scaleSphere = glm::vec3(SphereTransform.scale.x, SphereTransform.scale.y, SphereTransform.scale.z);
	glm::vec3 rotationSphere = SphereTransform.rotation;


	glm::mat4 objTranslateSphere = glm::translate(glm::mat4(), positionSphere);
	glm::mat4 objScaleSphere = glm::scale(glm::mat4(), scaleSphere);
	glm::mat4 objRotationSphere;// = glm::rotate(glm::mat4(), glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
	objRotationSphere = glm::rotate(glm::mat4(), glm::radians(rotationSphere.x), glm::vec3(1.0f, 0.0f, 0.0f)); //x
	objRotationSphere = glm::rotate(objRotationSphere, glm::radians(rotationSphere.y), glm::vec3(0.0f, 1.0f, 0.0f)); //y
	objRotationSphere = glm::rotate(objRotationSphere, glm::radians(rotationSphere.z), glm::vec3(0.0f, 0.0f, 1.0f)); //Z
	glm::mat4 modelSphere = objTranslateSphere * objRotationSphere * objScaleSphere;


	glm::mat4 MVP = m_mainCamera->GetProj() * m_mainCamera->GetView() * modelSphere;

	GLuint MVPLoc = glGetUniformLocation(CAssetMgr::GetInstance()->GetProgramID("TerrainProgram"), "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(m_sVAO);			  // Bind VAO
	glDrawElements(GL_TRIANGLES, m_iSphereIndicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);			  // Unbind VAO
	glUseProgram(0);
	//glPolygonMode(GL_FRONT, GL_FILL);
}

void CPhysicsScene::SphereCollision()
{
	for (unsigned int x = 0; x < cloth->m_Nodes.size(); x++)
	{
		for (unsigned int y = 0; y < cloth->m_Nodes[x].size(); y++)
		{
			if (cloth->m_Nodes[x][y]->bAnchored) continue;

			glm::vec3 loc = cloth->m_Nodes[x][y]->GetLocation();
			glm::vec3 Dir = loc - SphereTransform.position;
			float PenetrationLenght = (fSphereRadius + 5.0f) - glm::length(Dir);
			if (PenetrationLenght > 0)
			{
				cloth->m_Nodes[x][y]->SetLocation(loc + (glm::normalize(Dir) * PenetrationLenght));
			}
		}
	}
}

void CPhysicsScene::ResetScene()
{
	cloth->ResetNodes();
	cloth->ResizeCloth(20, 20);
	cloth->InitializeVertices();
	cloth->InitializeIndices();
	cloth->IntializeConnectionsSquares();
	cloth->InitializeRender();

	SphereTransform.position = glm::vec3(0, 0, -50);
}
