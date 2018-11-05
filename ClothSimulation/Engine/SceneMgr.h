#pragma once
#ifndef _SCENEMGR_H
#define _SCENEMGR_H

// Global Include
#include "Utility.h"

// Forawrd Declare
class CScene;

class CSceneMgr
{
#pragma region Singleton
public:
	// Singleton Methods
	static CSceneMgr* GetInstance();
	static void DestroyInstance();

private:
	// Make singleton by set the constructor inside private
	CSceneMgr();
	~CSceneMgr();

	// Make this class non-copyable
	CSceneMgr(const CSceneMgr& _kr) = delete;
	CSceneMgr& operator= (const CSceneMgr& _kr) = delete;

protected:
	// Singleton Object
	static CSceneMgr* s_pSceneMgr;

#pragma endregion Singleton

public:
	
	// Member Functions
	void InitializeScenes();
	void RenderCurrentScene();
	void UpdateCurrentScene(float _tick);
	void CreateNewScene(std::string _name, CScene* _scene);
	void LoadScene(std::string _name);
	CScene* GetRunningScene() const;


private:
	// Member Variables

	std::map<std::string, CScene*> m_scenes; // Scene Container

	CScene* m_runningScene;


public:

	// Store all the scores
	int m_playerOneScore = 0;
	int m_playerTwoScore = 0;
	int m_playerThreeScore = 0;
	int m_playerFourScore = 0;


	int m_Winner = 0;
	bool P1;
	bool P2;
	bool P3;
	bool P4;
};

#endif // !_SCENEMGR_H