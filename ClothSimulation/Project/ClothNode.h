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
private:

	int iNodeNum;
	std::vector<CClothNode*> ConnectedNodes;
};