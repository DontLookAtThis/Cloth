#pragma once

#include "Engine/Scene.h"

class CPhysicsScene : public CScene
{
public:
	CPhysicsScene();
	virtual ~CPhysicsScene();

	virtual void ConfigurateScene(bool _bPhysicsEnabled) override;
	virtual void ConfigurateScene() override;
	virtual void UpdateScene(float _tick) override;
	virtual void RenderScene() override;
private:
	class CCloth* cloth;
};