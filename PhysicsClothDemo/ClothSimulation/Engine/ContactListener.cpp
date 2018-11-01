#include "ContactListener.h"
#include "Engine\RigidBody2D.h"


CContactListener::CContactListener()
{
}

CContactListener::~CContactListener()
{
}

void CContactListener::BeginContact(b2Contact* _contact)
{
	//Get 2 bodies colliding
	CRigiBody2D* bodyA = static_cast<CRigiBody2D*>(_contact->GetFixtureA()->GetBody()->GetUserData());
	CRigiBody2D* bodyB = static_cast<CRigiBody2D*>(_contact->GetFixtureB()->GetBody()->GetUserData());;

	if (!_contact->GetFixtureB()->IsSensor())
	{
		bodyA->OnCollisionEnter(bodyB);
	}
	if (!_contact->GetFixtureA()->IsSensor())
	{
		bodyB->OnCollisionEnter(bodyA);
	}
}

void CContactListener::EndContact(b2Contact * _contact)
{
	CRigiBody2D* bodyA = static_cast<CRigiBody2D*>(_contact->GetFixtureA()->GetBody()->GetUserData());
	CRigiBody2D* bodyB = static_cast<CRigiBody2D*>(_contact->GetFixtureB()->GetBody()->GetUserData());;

	if (!_contact->GetFixtureB()->IsSensor())
	{
		bodyA->OnCollisionExit(bodyB);
	}
	if (!_contact->GetFixtureA()->IsSensor())
	{
		bodyB->OnCollisionExit(bodyA);
	}
}

void CContactListener::PostSolve(b2Contact * _contact, const b2ContactImpulse * impulse)
{
}

void CContactListener::PreSolve(b2Contact * _contact, const b2Manifold * oldManifold)
{
}
