#pragma once


#include "Engine\Utility.h"

class CContactListener : public b2ContactListener
{
public:
	CContactListener();
	virtual ~CContactListener() override;

	virtual void BeginContact(b2Contact* _contact) override;
	virtual void EndContact(b2Contact* _contact) override;
	virtual void PostSolve(b2Contact* _contact, const b2ContactImpulse* impulse) override;
	virtual void PreSolve(b2Contact* _contact, const b2Manifold* oldManifold) override;
};