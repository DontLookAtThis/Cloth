#pragma once
#include "Engine/GameObject.h"
#include <vector>

class CClothNode : public CGameObject 
{
public:
	CClothNode();
	~CClothNode();

	virtual void BeginPlay() override;
	virtual void Update(float _tick) override;

	int GetNodeNum();
	void SetNodeNum(int Num);
	void AddConnectedNode(CClothNode* Node);

	void Wind(float _Force);
	void ApplyForce(glm::vec3 _Force);
	float mass = 3.0f;

	glm::vec3 SingleFrameAcceleration;
	glm::vec3 ConsistentVelocity;

	bool bAnchored;
private:

	int iNodeNum;
	std::vector<CClothNode*> ConnectedNodes;


};