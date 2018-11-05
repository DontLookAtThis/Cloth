// This Include
#include "Time.h"

// Local Include
#include "Engine/Utility.h"

// Static Variable
CTime* CTime::s_pTime = nullptr;

CTime* CTime::GetInstance()
{
	if (s_pTime == nullptr)
	{
		s_pTime = new CTime();
	}
	
	return s_pTime;
}

void CTime::DestroyInstance()
{
	delete s_pTime;
	s_pTime = nullptr;
}

void CTime::Initialize()
{
	oldTime = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	TickTime = 0.01666666f;
	deltaTimeTick = 0.0f;
}

void CTime::Update()
{
	newTime = (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = newTime - oldTime;

	oldTime = newTime;
	deltaTimeTick += deltaTime;
	if (deltaTimeTick >= TickTime)
	{
		deltaTimeTick = 0.0f;
	}
}

float CTime::GetDeltaTime() const
{
	return deltaTime;
}

float CTime::GetTick() const
{
	return deltaTimeTick;
}
