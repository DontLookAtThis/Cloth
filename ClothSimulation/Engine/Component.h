#pragma once

// Global Include
#include "Utility.h"
#include <string>
#include <iostream>
// Forward Declare
class CGameObject;

class CComponent
{
public:
	CComponent();
	~CComponent();

protected:

	CGameObject* m_owner;
	bool m_isActive = true;

// Membre Funciton
public:

	virtual void Update(float _tick) {}
	virtual void BeginPlay() {}
	virtual void OnDestroy() {}

	/**
	 * Getter and setter of the "owner" property of the component
	 */
	void SetOwner(CGameObject* _gameObject);
	CGameObject* GetOwner() const;

	/**
	 * Getter and setter of the "active" property of the component
	 */
	void SetActive(bool);
	bool IsActive() const;
	std::string m_ComponentType;
};

