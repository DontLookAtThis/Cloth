#pragma once


class CClothLink
{
public:
	CClothLink();
	~CClothLink();
	CClothLink(class CClothNode* Point1, class CClothNode* Point2, int LinkInd);
	void InitializeLinks(class CClothNode* Point1, class CClothNode* Point2);

	class CClothNode* m_Point1;
	class CClothNode* m_Point2;

	int LinkIndice;
};