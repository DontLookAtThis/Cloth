
// This Include
#include "AssetMgr.h"

// Engine Include
#include "ShaderLoader.h"
#include "Sprite.h"
#include "TextLoader.h"
#include "Debug.h"

// Static Variable
CAssetMgr* CAssetMgr::s_pAssetMgr = nullptr;

CAssetMgr* CAssetMgr::GetInstance()
{
	if (s_pAssetMgr == nullptr)
	{
		s_pAssetMgr = new CAssetMgr();
	}

	return s_pAssetMgr;
}

void CAssetMgr::DestroyInstance()
{
	delete s_pAssetMgr;
	s_pAssetMgr = nullptr;
}

CAssetMgr::CAssetMgr() {}
CAssetMgr::~CAssetMgr() {}

void CAssetMgr::InitializeAssets()
{
	/** Initialize Programs */
	CreateProgram("DefaultSpriteProgram", "Engine/Shaders/Sprite.vs", "Engine/Shaders/Sprite.fs");
	CreateProgram("DefaultTextPrograrm", "Engine/Shaders/Text.vs", "Engine/Shaders/Text.fs");
	CreateProgram("ClothProgram", "Engine/Shaders/Cloth.vs", "Engine/Shaders/Cloth.fs");
	CreateProgram("TerrainProgram", "Engine/Shaders/Terrain.vs", "Engine/Shaders/Terrain.fs");
	CreateProgram("SphereProgram", "Engine/Shaders/Sphere.vs", "Engine/Shaders/Sphere.fs");
	/** Initialize Sprites */
	CreateSprite("DefaultSprite", "Resources/Sprites/DefaultSprite.png");
	CreateSprite("Triangle", "Resources/Sprites/Player2.png");
	CreateSprite("Block", "Resources/Sprites/Block.png");
	CreateSprite("Player", "Resources/Sprites/spaceship.png");
	CreateSprite("Birdie", "Resources/Sprites/Bird.png");
	CreateSprite("WoodBlock", "Resources/Sprites/Wood elements/elementWood019.png");
	CreateSprite("Pig", "Resources/Sprites/Happy_pig.png");
	CreateSprite("Ground", "Resources/Sprites/Other/grass.png");
	CreateSprite("Sling", "Resources/Sprites/Slingshot.png");
	CreateSprite("Gravity", "Resources/Sprites/GravityWell.png");
	CreateSprite("DeathSensor", "Resources/Sprites/DeathSensor.png");
	CreateSprite("ControlMenu", "Resources/Sprites/ControlsMenu.png");

	//Player Sprite
	CreateSprite("Player1", "Resources/Sprites/Player1.png");
	CreateSprite("Player2", "Resources/Sprites/Player2.png");
	CreateSprite("Player3", "Resources/Sprites/Player3.png");
	CreateSprite("Player4", "Resources/Sprites/Player4.png");

	CreateSprite("Gate", "Resources/Sprites/gate.png");
	CreateSprite("Collectable", "Resources/Sprites/collectable.png");
	CreateSprite("Background", "Resources/Sprites/space.jpg");
	//Block Sprite
	CreateSprite("1Block", "Resources/Sprites/Block.png");
	CreateSprite("2Block", "Resources/Sprites/2Block.png");
	CreateSprite("3Block", "Resources/Sprites/3Block.png");
	CreateSprite("4Block", "Resources/Sprites/4Block.png");
	CreateSprite("5Block", "Resources/Sprites/5Block.png");
	CreateSprite("6Block", "Resources/Sprites/6Block.png");
	CreateSprite("7Block", "Resources/Sprites/7Block.png");
	CreateSprite("8Block", "Resources/Sprites/8Block.png");
	CreateSprite("9Block", "Resources/Sprites/9Block.png");
	CreateSprite("10Block", "Resources/Sprites/10Block.png");
	CreateSprite("11Block", "Resources/Sprites/11Block.png");

	CreateSprite("Box", "Resources/Sprites/Box.png");
	//Font
	CreateFont("SpaceFont", "Resources/Fonts/Space.ttf");
}


CSprite* CAssetMgr::GetSprite(std::string _name) const
{
	for (auto iter = m_spriteMap.begin(); iter != m_spriteMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab sprite from name.");
	return nullptr;
}

GLuint CAssetMgr::GetProgramID(std::string _name) const
{
	for (auto iter = m_programMap.begin(); iter != m_programMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab program ID from name.");
	return NULL;
}

Text* CAssetMgr::GetFont(std::string _name) const
{
	for (auto iter = m_fontMap.begin(); iter != m_fontMap.end(); ++iter)
	{
		if (iter->first == _name)
		{
			return iter->second;
		}
	}

	CDebug::Log("Unable to grab Font from name.");
	return nullptr;
}

void CAssetMgr::CreateProgram(std::string _name, const char* _vertexPath, const char* _fragmentPath)
{
	GLuint newProgram = ShaderLoader::CreateProgram(_vertexPath, _fragmentPath);

	m_programMap.insert(std::pair<std::string, GLuint>(_name, newProgram));
}

void CAssetMgr::CreateSprite(std::string _name, const char* _pathName)
{
	CSprite* newSprite = new CSprite();
	newSprite->CreateSprite(_pathName);

	m_spriteMap.insert(std::pair<std::string, CSprite*>(_name, newSprite));
}

void CAssetMgr::CreateFont(std::string _name, const char* _pathName)
{
	Text* newFont = new Text(_pathName);

	m_fontMap.insert(std::pair<std::string, Text*>(_name, newFont));
}
