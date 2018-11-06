#include "ClothLink.h"
#include "ClothNode.h"
#include "Engine/Time.h"
#include "Cloth.h"
CClothLink::CClothLink()
{
	bLinkAlive = true;
	TearDistance = RestingDistance * 3.0f;
}


CClothLink::~CClothLink()
{
	m_Point1 = nullptr;
	m_Point2 = nullptr;
}

CClothLink::CClothLink(CClothNode * Point1, CClothNode * Point2, class CCloth* cloth)
{
	InitializeLinks(Point1, Point2);
	bLinkAlive = true;
	TearDistance = RestingDistance * 3.0f;
	m_cloth = cloth;
}

CClothLink::CClothLink(CClothNode * Point1, CClothNode * Point2, bool bCross, class CCloth* cloth)
{
	InitializeLinks(Point1, Point2);
	if (bCross)
	{
		RestingDistance = sqrtf(((RestingDistance * RestingDistance) * 2));
	}
	bLinkAlive = true;
	TearDistance = RestingDistance * 3.0f;
	m_cloth = cloth;
}

void CClothLink::InitializeLinks(CClothNode* Point1, CClothNode* Point2)
{
	m_Point1 = Point1;
	m_Point2 = Point2;
}

void CClothLink::KillLink()
{
	bLinkAlive = false;
}

void CClothLink::Update(float _dTime)
{
	if (!bLinkAlive) return;
	glm::vec3 DeltaV = m_Point1->GetLocation() - m_Point2->GetLocation();

	if (glm::length(DeltaV) <= 0.0f)
	{
		return;
	}
	float DeltaLength = glm::length(DeltaV);// sqrtf(((DeltaV.x * DeltaV.x) + (DeltaV.y * DeltaV.y) + (DeltaV.z * DeltaV.z)));
	if (DeltaLength >= TearDistance)
	{
		KillLink();
	}
	if (DeltaLength >= TearDistance && bLinkAlive)
	{
		std::cout << "haxks" << std::endl;
	}
	//if (DeltaLength > RestingDistance)
//	{
		float Difference = (DeltaLength - RestingDistance) / DeltaLength;

		float im1 = 1 / m_Point1->mass;
		float im2 = 1 / m_Point2->mass;

		glm::vec3 point1Change = (DeltaV * (im1 / (im1 + im2)) * Stiffness * Difference); //* float(util::PIXELUNIT); //* CTime::GetInstance()->GetDeltaTime() * float(util::PIXELUNIT);
		glm::vec3 point2Change = (DeltaV * (im2 / (im1 + im2)) * Stiffness * Difference); //* float(util::PIXELUNIT); //* CTime::GetInstance()->GetDeltaTime() * float(util::PIXELUNIT);

		if (!m_Point1->bAnchored)
		{
			m_Point1->SetLocation(m_Point1->GetLocation() - point1Change);
		}
		if (!m_Point2->bAnchored)
		{
			m_Point2->SetLocation(m_Point2->GetLocation() + point2Change);
		}
//	}


	////SALLY TUTORIAL CODE 
	//glm::vec3 dis = DeltaV * (1 - RestingDistance / DeltaLength);

	//if (!m_Point1->bAnchored)
	//{
	//	m_Point1->SetLocation(m_Point1->GetLocation() - (dis * 0.5f));
	//}
	//if (!m_Point2->bAnchored)
	//{
	//	m_Point2->SetLocation(m_Point2->GetLocation() + (dis * 0.5f));
	//}
}
