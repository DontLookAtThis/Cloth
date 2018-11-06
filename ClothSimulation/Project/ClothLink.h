#pragma once


class CClothLink
{
public:
	CClothLink();
	~CClothLink();
	CClothLink(class CClothNode* Point1, class CClothNode* Point2, class CCloth* cloth);
	CClothLink(class CClothNode* Point1, class CClothNode* Point2, bool bCross, class CCloth* cloth);
	void InitializeLinks(class CClothNode* Point1, class CClothNode* Point2);
	void KillLink();


	class CClothNode* m_Point1;
	class CClothNode* m_Point2;
	class CCloth* m_cloth;

	bool bLinkAlive;

	float Stiffness = 0.5f;
	float RestingDistance = 10.0f;
	float MinimumDistance = 2.0f;

	float TearDistance;

	void Update(float _dTime);
};