#include "Cloth.h"
#include "ClothNode.h"
#include "Engine/AssetMgr.h"
#include "PhysicsScene.h"
#include "Engine/Scene.h"
#include "Engine/Camera.h"
#include "ClothLink.h"

CCloth::CCloth()
{
	fVerticeGap = 10.0f;
	IndiceCountC = 0;
}

CCloth::~CCloth()
{
}

void CCloth::BeginPlay()
{
	__super::BeginPlay();
}

void CCloth::Update(float _tick)
{
	__super::Update(_tick);


	for (unsigned int x = 0; x < m_Nodes.size(); x++)
	{
		for (unsigned int y = 0; y < m_Nodes[x].size(); y++)
		{
			m_Nodes[x][y]->Update(_tick);
		}
	}

	for (auto it : m_links)
	{
		it->Update(_tick);
	}

	ReinitializeVertices();
	ReinitializeIndices();
}

void CCloth::ResizeCloth(int _width, int _height)
{
	m_width = _width;
	m_height = _height;

	m_Nodes.resize(_width);
	for (unsigned int x = 0; x < m_Nodes.size(); x++)
	{
		m_Nodes[x].resize(_height);
		for (unsigned int y = 0; y < m_Nodes[x].size(); y++)
		{
			m_Nodes[x][y] = new CClothNode();
			m_Nodes[x][y]->SetNodeNum((m_Nodes.size() * y) + x);
			m_Nodes[x][y]->SetLocation(glm::vec3(this->GetLocation().x + x * fVerticeGap, this->GetLocation().y + y * fVerticeGap, this->GetLocation().z));
		}
	}

}

void CCloth::ResetNodes()
{
	if (!m_Nodes.empty())
	{
		for (auto it : m_Nodes)
		{
			for (auto it2 : it)
			{
				delete it2;
			}
			it.clear();
		}
		m_Nodes.clear();
	}

	if (!m_links.empty())
	{
		for (auto it : m_links)
		{
			delete it;
		}
		m_links.clear();
	}

	if (!m_AnchoredNodes.empty())
	{
		m_AnchoredNodes.clear();
	}

	IndiceCountC = 0;
	m_width = 0;
	m_height = 0;
}

void CCloth::InitializeVertices()
{
	for (int X = 0; X < m_Nodes.size(); X++)
	{
		for (int Y = 0; Y < m_Nodes[X].size(); Y++)
		{
			vertices.push_back(m_Nodes[X][Y]->GetLocation().x);
			vertices.push_back(m_Nodes[X][Y]->GetLocation().y);
			vertices.push_back(m_Nodes[X][Y]->GetLocation().z);
		}
	}
}

void CCloth::InitializeIndices()
{
	int IndicePos = 0;
	for (int X = 0; X < (m_Nodes.size() -1); X++)
	{
		for (int Y = 0; Y < (m_Nodes[X].size() -1); Y++)
		{
			//indices.push_back(X * m_width + Y);
			//indices.push_back(X * m_width + (Y + 1));
			m_links.push_back((new CClothLink(m_Nodes[X][Y], m_Nodes[X][Y + 1], this)));

			//indices.push_back(X * m_width + Y);
			//indices.push_back((X + 1)* m_width + Y);
			m_links.push_back((new CClothLink(m_Nodes[X][Y], m_Nodes[(X + 1)][Y], this)));

			//Crosses

			//indices.push_back(X * m_width + Y);
			//indices.push_back((X + 1)* m_width + (Y + 1));
			m_links.push_back((new CClothLink(m_Nodes[X][Y], m_Nodes[(X + 1)][(Y + 1)], true, this)));

			//indices.push_back(X * m_width + (Y + 1));
			//indices.push_back((X + 1)* m_width + Y);
			m_links.push_back((new CClothLink(m_Nodes[X][(Y + 1)], m_Nodes[(X + 1)][Y], true, this)));
		}
	}

	for (int Y = 0; Y < (m_height - 1); Y++)
	{
		//indices.push_back((Y + 1)* (m_width - 1) + Y);
		//indices.push_back((Y + 2) * (m_width - 1) + (Y + 1));

		m_links.push_back((new CClothLink(m_Nodes[m_width - 1][Y], m_Nodes[m_width - 1][Y + 1], this)));
	}
	for (int X = 0; X < (m_width - 1); X++)
	{
		//indices.push_back((m_height *(m_width - 1) + m_height - 1) + X);
		//indices.push_back((m_height *(m_width - 1) + m_height - 1) + X + 1);
		m_links.push_back((new CClothLink(m_Nodes[X][m_height - 1], m_Nodes[X +1][m_height - 1],this)));
	}

	ReinitializeIndices();

	IndiceCountC = indices.size();
}

void CCloth::IntializeConnectionsSquares()
{
	int IndicePos = 0;
	for (int X = 0; X < m_width; X++)
	{
		for (int Y = 0; Y < m_height; Y++)
		{
			//CONDITION X Is Not on either edge
			if (X - 1 > 0 && X + 1 < m_width)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X + 1][Y]);
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X - 1][Y]);
			}
			//CONDITION X is On the left edge
			else if (X - 1 > 0)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X - 1][Y]);
			}
			//CONDITION X is On the right edge
			else if (X + 1 < m_width)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X + 1][Y]);
			}
			
			//CONDITION Y Is Not on either edge
			if (Y - 1 > 0 && Y + 1 < m_height)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X][Y + 1]);
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X][Y - 1]);
			}
			//CONDITION X is On the Top edge
			else if (Y - 1 > 0)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X][Y - 1]);
			}
			//CONDITION X is On the Bottom edge
			else if (Y + 1 < m_height)
			{
				m_Nodes[X][Y]->AddConnectedNode(m_Nodes[X][Y + 1]);
			}
		}
	}
}

void CCloth::ReinitializeVertices()
{
	vertices.clear();
	for (int Y = 0; Y < m_height; Y++)
	{
		for (int X = 0; X < m_width; X++)
		{
			vertices.push_back(m_Nodes[X][Y]->GetLocation().x);
			vertices.push_back(m_Nodes[X][Y]->GetLocation().y);
			vertices.push_back(m_Nodes[X][Y]->GetLocation().z);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, ClothVBO);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(GLfloat),
		&vertices[0],
		GL_STATIC_DRAW);
}

void CCloth::ReinitializeIndices()
{
	indices.clear();
	for (auto it : m_links)
	{
		if (it->bLinkAlive)
		{
			indices.push_back(it->m_Point1->GetNodeNum());
			indices.push_back(it->m_Point2->GetNodeNum());
		}
	}
	IndiceCountC = indices.size();
	std::cout << IndiceCountC << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ClothEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		&indices[0],
		GL_STATIC_DRAW);
}

void CCloth::RenderCloth()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(CAssetMgr::GetInstance()->GetProgramID("TerrainProgram"));

	glm::vec3 position = m_transform.position;
	glm::vec3 scale = m_transform.scale;
	glm::vec3 rotation = m_transform.rotation;

	glm::mat4 objTranslate = glm::translate(glm::mat4(), position);
	glm::mat4 objScale = glm::scale(glm::mat4(), scale);
	glm::mat4 objRotation;// = glm::rotate(glm::mat4(), glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
	objRotation = glm::rotate(glm::mat4(), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); //x
	objRotation = glm::rotate(objRotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); //y
	objRotation = glm::rotate(objRotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); //Z

	glm::mat4 model = objTranslate * objRotation * objScale;
	
	glm::mat4 MVP = GetScene()->GetMainCamera()->GetProj() * GetScene()->GetMainCamera()->GetView();
	GLint MVPLoc = glGetUniformLocation(CAssetMgr::GetInstance()->GetProgramID("TerrainProgram"), "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));


	glPolygonMode(GL_FRONT, GL_LINE);
	glBindVertexArray(ClothVAO);
	glDrawElements(GL_LINES, IndiceCountC, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glDisable(GL_BLEND);
	glUseProgram(0);
	glPolygonMode(GL_FRONT, GL_FILL);
}

void CCloth::InitializeRender()
{


	//VBO
	glGenVertexArrays(1, &ClothVAO);
	glBindVertexArray(ClothVAO);
	//VBO
	glGenBuffers(1, &ClothVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ClothVBO);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(GLfloat),
		&vertices[0],
		GL_STATIC_DRAW);
	//EBO
	glGenBuffers(1, &ClothEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ClothEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		&indices[0],
		GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

void CCloth::AnchorTop()
{
	if (m_Nodes.empty())return;
	for (auto it : m_Nodes)
	{
		it[0]->bAnchored = true;
		iAnchorPointCount = m_Nodes.size();
		m_AnchoredNodes.push_back(it[0]);
	}
}

void CCloth::ReduceAnchorPoints()
{
	if (iAnchorPointCount <= 1)
	{
		return;
	}

	int width = m_width;
	int height = m_height;
	ResetNodes();
	ResizeCloth(width, height);
	InitializeVertices();
	InitializeIndices();
	IntializeConnectionsSquares();
	InitializeRender();
	ReinitializeIndices();

	iAnchorPointCount = iAnchorPointCount / 2;

	for (auto it : m_AnchoredNodes)
	{
		it->bAnchored = false;
	}

	int AnchorGap = m_width / iAnchorPointCount;
	int counter = 0;
	m_AnchoredNodes.clear();
	for (auto it : m_Nodes)
	{
		if (counter % AnchorGap == 0)
		{
			it[0]->bAnchored = true;
			iAnchorPointCount = m_Nodes.size();
			m_AnchoredNodes.push_back(it[0]);
		}
		counter++;
	}
	m_Nodes[m_Nodes.size() - 1][0]->bAnchored = true;
	m_AnchoredNodes.push_back(m_Nodes[m_Nodes.size() - 1][0]);
	iAnchorPointCount = m_AnchoredNodes.size();
}

void CCloth::InCreaseAnchorPoints()
{
	if (iAnchorPointCount >= m_width) return;

	int width = m_width;
	int height = m_height;
	ResetNodes();
	ResizeCloth(width, height);
	InitializeVertices();
	InitializeIndices();
	IntializeConnectionsSquares();
	InitializeRender();
	ReinitializeIndices();

	for (auto it : m_AnchoredNodes)
	{
		it->bAnchored = false;
	}

	iAnchorPointCount *= 2;
	if (iAnchorPointCount >= m_width)
	{
		iAnchorPointCount = m_width;
		m_AnchoredNodes.clear();
		for (auto it : m_Nodes)
		{
			it[0]->bAnchored = true;
			iAnchorPointCount = m_Nodes.size();
			m_AnchoredNodes.push_back(it[0]);
		}
		return;
	}

	int AnchorGap = m_width / iAnchorPointCount;
	int counter = 0;
	m_AnchoredNodes.clear();
	for (auto it : m_Nodes)
	{
		if (counter % AnchorGap == 0)
		{
			it[0]->bAnchored = true;
			iAnchorPointCount = m_Nodes.size();
			m_AnchoredNodes.push_back(it[0]);
		}
		counter++;
	}
	m_Nodes[m_Nodes.size() - 1][0]->bAnchored = true;
	m_AnchoredNodes.push_back(m_Nodes[m_Nodes.size() - 1][0]);
	iAnchorPointCount = m_AnchoredNodes.size();
}
