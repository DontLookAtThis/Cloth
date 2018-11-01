#include "ClothLink.h"
#include "ClothNode.h"
CClothLink::CClothLink()
{

}


CClothLink::~CClothLink()
{
	m_Point1 = nullptr;
	m_Point2 = nullptr;
}

CClothLink::CClothLink(CClothNode * Point1, CClothNode * Point2, int LinkInd)
{
	InitializeLinks(Point1, Point2);
	LinkIndice = LinkInd;
}

void CClothLink::InitializeLinks(CClothNode* Point1, CClothNode* Point2)
{
	m_Point1 = Point1;
	m_Point2 = Point2;
}
