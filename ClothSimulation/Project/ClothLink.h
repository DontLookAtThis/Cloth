#pragma once


class CClothLink
{
public:
	CClothLink();
	~CClothLink();
	CClothLink(class CClothNode* Point1, class CClothNode* Point2);
	CClothLink(class CClothNode* Point1, class CClothNode* Point2, bool bCross);
	void InitializeLinks(class CClothNode* Point1, class CClothNode* Point2);
	void KillLink();


	class CClothNode* m_Point1;
	class CClothNode* m_Point2;

	bool bLinkAlive;

	float Stiffness = 0.5f;
	float RestingDistance = 10.0f;

	void Update(float _dTime);
};