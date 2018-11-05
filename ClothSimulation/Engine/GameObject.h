#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#pragma once
// Global Include
#include "Utility.h"

// Forward Declare
class CGameObject;
class CComponent;
class CScene;

// Declare a Transform struct

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	// Properties
	std::string m_tag;
	std::string m_name;
	Transform m_transform;

	int m_iHealth = 100;
	CScene* m_Scene;
	std::vector<CComponent*> m_components;

	void SetLocation(glm::vec3 _LocationVec3);
	void SetRotation(glm::vec3 _RotationAxisVec3);
	void SetScale(glm::vec3 _ScaleVec3);

	glm::vec3 GetLocation();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	CScene* GetScene();
protected:
	
	bool m_isUpdating;
	bool m_ShouldDestroyed;
	bool m_isActive;
	bool m_isAlive;

public:
	/**
	* Initialize the object
	* Call right after the scene initialize
	*/
	void SetWorld(CScene* world);
	virtual void BeginPlay();
	/*
	 * Call every frame
	 */
	virtual void Update(float _tick);
	/**
	* Try get the component of the gameobject
	*/
	template<typename T>
	T* GetComponent() const;
	/*
	 *Check if the object should be destroyed on thie frame
	 */
	bool ShouldDestroyed() const;
	/*
	 *Destroy current gameobject and set it to inactive 
	 *of the garbage cleaning next frame
	 */
	void DestroyObject();
    /*
	 *Check if the obejct is active which determent it should update or not
	 */
	bool IsActive() const;
	/*
	 * Set active state for a object
	 */
	void SetActive(bool);

	/*
	* Get and Set updating state for a object
	*/
	bool IsUpdating() const;
	void SetUpdating(bool);

	void TakeDamage(int _damage);




	virtual void OnCollisionEnter(CGameObject* CollidedObject);
	virtual void OnColliisionExit(CGameObject* CollidedObject);

	/**
	 * Creates a component and push to the vector
	 */
	template<typename T>
	T* CreateComponent();

};

template<typename T>
T* CGameObject::CreateComponent()
{
	CComponent* newComponent = new T();
	newComponent->SetOwner(this);

	T* resultComponent = dynamic_cast<T*>(newComponent);

	if (resultComponent != nullptr)
	{
		m_components.push_back(resultComponent);
	}

	return resultComponent;
}

template<typename T>
T* CGameObject::GetComponent() const
{

	for (CComponent* iter : m_components)
	{
		T* component = dynamic_cast<T*>(iter);
		if (component != nullptr)
		{
			return component;
		}
	}

	return nullptr;
}

#endif // !GAMEOBJECT_H