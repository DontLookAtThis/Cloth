#pragma once

// Global Include
#include "Utility.h"

// Forward Declare
class CSprite;
class Text;


class CAssetMgr
{

#pragma region Singleton
public:

	static CAssetMgr* GetInstance();
	static void DestroyInstance();

private:
	CAssetMgr();
	~CAssetMgr();

	CAssetMgr(const CAssetMgr& _kr) = delete;
	CAssetMgr& operator= (const CAssetMgr& _kr) = delete;

protected:
	static CAssetMgr* s_pAssetMgr;

#pragma endregion

public:

	/**
	 * This is where to import all the game assets
	 */
	void InitializeAssets();

	CSprite* GetSprite(std::string _name) const;
	GLuint GetProgramID(std::string _name) const;
	Text* GetFont(std::string _name) const;

private:

	void CreateProgram(std::string _name, const char* _vertexPath, const char* _fragmentPath);

	void CreateSprite(std::string _name, const char* _pathName);

	void CreateFont(std::string _name, const char* _pathName);

private:
	/** Map collection of sprites with a string name */
	std::map<std::string, CSprite*> m_spriteMap;

	/** Map collection of programs with a string name */
	std::map<std::string, GLuint> m_programMap;

	std::map<std::string, Text*> m_fontMap;

};

