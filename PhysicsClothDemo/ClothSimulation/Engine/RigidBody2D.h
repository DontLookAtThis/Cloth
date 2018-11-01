#pragma once

// Inherited Include
#include "Component.h"
#include "Utility.h"
#include <vector>
class CRigiBody2D : public CComponent
{

public:
	float fRadius;
	CRigiBody2D();
	virtual ~CRigiBody2D();

	virtual void Update(float _tick) override;
	virtual void BeginPlay() override;
	virtual void OnDestroy() override;
	b2Body* GetBody();
	
	void CreateBody(b2World* _world, b2BodyType BodyType,
		bool bCanRotate = true, bool bHasFixture = true, float Density = 1.0f, float Friction = 0.3f, int fixtureType = 0);
	void CreateSensorCube(b2World* _world, b2BodyType BodyType,
		bool bCanRotate = true, bool bHasFixture = true, float Density = 1.0f, float Friction = 0.3f);
	void CreateBodyCircle(b2World* _world, b2BodyType BodyType,
		bool bCanRotate = true, bool bHasFixture = true, float Density = 1.0f, float Friction = 0.3f, int fixtureType = 0);
	void CreateGravityWell(b2World* _world, float fRadius, bool bHasFixture = true, float Strength = 0.0f);
	void DestroyGravityWell();	

	void SetBodyType(b2BodyType _bodyType);
	b2BodyType GetBodyType() const;

	void SetCanRotate(bool _b);
	bool GetCanRotate() const;

	void SetHasFixture(bool _b);
	bool GetHasFixture() const;

	void OnCollisionEnter(CRigiBody2D* collidedRigiBody);
	void OnCollisionExit(CRigiBody2D* collidedRigiBody);
	Transform m_transform;
	bool m_bHasGravityWell = false;

private:

	void CreateBody();


private:

	b2Body* m_body;
	b2Body* m_GravityWell;
	std::vector<b2Body*>BodiesColliding;
	// Properties that can be set either before or after the body being declared
	b2BodyType m_bodyType;
	bool m_bCanRotate;
	bool m_bHasFixture;
	float m_density;
	float m_friction;
	float m_GravityStrength;
	int m_fixtureType;

};