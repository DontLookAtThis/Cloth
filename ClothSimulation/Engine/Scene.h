#pragma once
#ifndef SCENE_H
#define SCENE_H

// Global Include
#include "Utility.h"
// Forward Declaration
class CGameObject;
class CCamera;
class CCubeMap;
class CTextLabel;
class CContactListener;
class CSpaceShip;

class CScene
{
public:
	CScene();
	virtual ~CScene();

	/**
	 * Create all the game object that is build into the scene
	 * at the beginning here. This will be running first when
	 * the scene start.
	 */
	virtual void ConfigurateScene(bool _bPhysicsEnabled);
	virtual void ConfigurateScene();
	/**
	 * Update all the contained object and logic of the game
	 * every frame
	 */
	virtual void UpdateScene(float _tick);
	/**
	 * After ConfigurationScene() run, the scene is ready to be
	 * run. This function will run and calls all the BeginPlay()
	 * inside each gameobject and all the logic needs to be run
	 * for the scene.
	 */
	virtual void BeginPlay();

	virtual void RenderScene();
	virtual void ResetScene();

	//void CheckCollision();
	void SetPhysicsEnabled(bool _bPhysicsEnabled);

	void Instantiate(CGameObject* _gameobj);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos);
	void Instantiate(CGameObject* _gameobj, glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rotation);
	void DestroyObject(CGameObject* _gameobj);

	CGameObject* FindGameObject(std::string _name) const;
	std::vector<CGameObject*> FindGameObjectAll(std::string _name) const;
	CGameObject* FindObjectWithTag(std::string _tag) const;
	std::vector<CGameObject*> FindObjectWithTagAll(std::string _tag) const;


	b2World* GetWorld() const;
	CCamera* GetMainCamera() const;

	std::vector<CGameObject*> GetObjectVec() const;
	//std::map<std::string, std::shared_ptr<CTextLabel>> m_mTextList;
	std::vector<CTextLabel*> m_vTextLabel;

public:

	std::string m_sceneName;

	bool bPhysicsEnabled;

protected:
	

	CCamera* m_mainCamera;

	CCubeMap* m_cubemap;

	std::vector<CGameObject*> m_vGameObj;

	b2Vec2 m_gravity;
	b2World* m_box2DWorld;
	CContactListener* m_ContactListener;

private:

};

#endif // !SCENE_H