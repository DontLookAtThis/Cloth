#include "ClothNode.h"

CClothNode::CClothNode()
{
}

CClothNode::~CClothNode()
{
	ConnectedNodes.clear();
	iNodeNum = -1;
}

void CClothNode::BeginPlay()
{
	__super::BeginPlay();
}

void CClothNode::Update(float _tick)
{
	__super::Update(_tick);
}

int CClothNode::GetNodeNum()
{
	if (iNodeNum)
	{
		return iNodeNum;
	}
	return -1;
}

void CClothNode::SetNodeNum(int Num)
{
	if (Num >= 0)
	{
		iNodeNum = Num;
	}
	else
	{
		std::cout << "Error when assigning Node Number" << std::endl;
	}
}

void CClothNode::AddConnectedNode(CClothNode * Node)
{
	ConnectedNodes.push_back(Node);
}
