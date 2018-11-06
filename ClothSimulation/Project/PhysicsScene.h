#pragma once

#include "Engine/Scene.h"
#include "Engine/Utility.h"

enum ControlState
{
	CAMERA,
	SPHERE,
	CLOTH,
	WIND,
};

class CPhysicsScene : public CScene
{
public:
	CPhysicsScene();
	virtual ~CPhysicsScene();

	virtual void ConfigurateScene(bool _bPhysicsEnabled) override;
	virtual void ConfigurateScene() override;
	virtual void UpdateScene(float _tick) override;
	virtual void RenderScene() override;

	void InitializeSphere();
	void RenderSphere();
	void SphereCollision();

	void ResetScene();
private:
	class CCloth* cloth;
	
	Transform SphereTransform;
	float fSphereRadius;
	GLuint m_sVAO;
	int m_iSphereIndicesCount;

	ControlState CurrentControlState;
};