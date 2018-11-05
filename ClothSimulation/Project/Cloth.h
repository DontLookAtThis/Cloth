#pragma once
//Engine
#include "Engine/GameObject.h"


//External
#include <vector>
class CCloth : public CGameObject 
{
public:
	//Constructor and Decontructor
	CCloth();
	~CCloth();
	//Virtual Functions
	virtual void BeginPlay() override;
	virtual void Update(float _tick) override;


	//Non Virtual Functions
	void ResizeCloth(int _width, int _height);
	void ResetNodes();

	void InitializeVertices();
	void InitializeIndices();
	void IntializeConnectionsSquares();
	void ReinitializeVertices();
	void ReinitializeIndices();

	void RenderCloth();
	void InitializeRender();

	std::vector<std::vector<class CClothNode*>> m_Nodes;
	std::vector<class CClothLink*> m_links;

private:



	int IndiceCountC;
	GLuint m_vaoC; // Vertex Array Obj
	GLuint m_vboC; // Texture Obj
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	float fVerticeGap;

	int m_width;
	int m_height;

	GLuint ClothVBO;
	GLuint ClothVAO;
	GLuint ClothEBO;
};