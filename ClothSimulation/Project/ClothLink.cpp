#include "ClothLink.h"
#include "ClothNode.h"
#include "Engine/Time.h"
CClothLink::CClothLink()
{
}


CClothLink::~CClothLink()
{
	m_Point1 = nullptr;
	m_Point2 = nullptr;
}

CClothLink::CClothLink(CClothNode * Point1, CClothNode * Point2)
{
	InitializeLinks(Point1, Point2);
}

CClothLink::CClothLink(CClothNode * Point1, CClothNode * Point2, bool bCross)
{
	InitializeLinks(Point1, Point2);
	if (bCross)
	{
		RestingDistance = sqrtf(((RestingDistance * RestingDistance) * 2));
	}

}

void CClothLink::InitializeLinks(CClothNode* Point1, CClothNode* Point2)
{
	m_Point1 = Point1;
	m_Point2 = Point2;
}

void CClothLink::Update(float _dTime)
{
	glm::vec3 DeltaV = m_Point1->GetLocation() - m_Point2->GetLocation();

	if (glm::length(DeltaV) <= 0.0f) return;
	float DeltaLength = glm::length(DeltaV);// sqrtf(((DeltaV.x * DeltaV.x) + (DeltaV.y * DeltaV.y) + (DeltaV.z * DeltaV.z)));
	float Difference = (DeltaLength - RestingDistance) / DeltaLength;

	float im1 = 1 / m_Point1->mass;
	float im2 = 1 / m_Point2->mass;

	glm::vec3 point1Change = (DeltaV * (im1 / (im1 + im2)) * Stiffness * Difference); //* float(util::PIXELUNIT); //* CTime::GetInstance()->GetDeltaTime() * float(util::PIXELUNIT);
	glm::vec3 point2Change = (DeltaV * (im2 / (im1 + im2)) * Stiffness * Difference); //* float(util::PIXELUNIT); //* CTime::GetInstance()->GetDeltaTime() * float(util::PIXELUNIT);


	//int num1 = m_Point1->GetNodeNum();
	//int num2 = m_Point2->GetNodeNum();
	//if (num1 == 0 && num2 == 20)
	//{
	//	std::cout << "Point 1 -" << point1Change.x  << " -- " << point1Change.y << " -- " << point1Change.z << std::endl;
	//	std::cout << "Point 2 -" << point2Change.x << " -- " << point2Change.y << " -- " << point2Change.z << std::endl;
	//}
	if (!m_Point1->bAnchored)
	{
		m_Point1->SetLocation(m_Point1->GetLocation() - point1Change);
	}
	if (!m_Point2->bAnchored)
	{
		m_Point2->SetLocation(m_Point2->GetLocation() + point2Change);
	}
	//m_Point1->SingleFrameAcceleration -= point1Change;
	//m_Point2->SingleFrameAcceleration -= point2Change;
}
