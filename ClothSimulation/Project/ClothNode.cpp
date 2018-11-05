#include "ClothNode.h"
#include "Engine/Time.h"
CClothNode::CClothNode()
{
}

CClothNode::~CClothNode()
{
	ConnectedNodes.clear();
	iNodeNum = -1;
	bAnchored = false;
}

void CClothNode::BeginPlay()
{
	__super::BeginPlay();
}

void CClothNode::Update(float _tick)
{
	__super::Update(_tick);



	if (bAnchored) return;

	//float grav = 9.8f *  CTime::GetInstance()->GetDeltaTime();
	//std::cout << grav << std::endl;

	int constWind = 10;
	float randWind = float((rand() % (constWind * 100))) / 100.0f;

	//Wind(randWind);
	ApplyForce((glm::vec3(0.0f, 9.8f * mass, 0.0f))); //* CTime::GetInstance()->GetDeltaTime()));
	SingleFrameAcceleration -= ConsistentVelocity * 0.9f / mass;


	glm::vec3 FinalVelocity = (ConsistentVelocity += SingleFrameAcceleration);

	SetLocation(GetLocation() + FinalVelocity);

	SingleFrameAcceleration = glm::vec3(0, 0, 0);


	if (iNodeNum == 0)
	{
		std::cout << ConsistentVelocity.y << std::endl;
	}
}

int CClothNode::GetNodeNum()
{
	if (iNodeNum >= 0)
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

void CClothNode::Wind(float _Force)
{
	ApplyForce(glm::vec3(0.0f, 0.0f, _Force));// *CTime::GetInstance()->GetDeltaTime());
}

void CClothNode::ApplyForce(glm::vec3 _Force)
{
	SingleFrameAcceleration += _Force / mass / float(util::PIXELUNIT);
}
