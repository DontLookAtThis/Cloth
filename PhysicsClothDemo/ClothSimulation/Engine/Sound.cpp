//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Sound.cpp
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
//

//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2017 Media Design School
//
// File Name	:	CSound.cpp
// Description	:	main implementation for CSound
// Author		:	Steven Zhao
// Mail 		:	steven.zha7447@mediadesign.school.nz
//

// Library Includes //

// Local Includes //

// This Includes //
#include "Sound.h"

// Static Variables //

// Static Function Prototypes //

// Types //
using namespace std;
CSound * CSound::pSound;
CSound * CSound::GetInstance()
{
	if (!pSound)
	{
		pSound = new CSound();
	}
	return pSound;
}

void CSound::DestroyInstance()
{
	if (pSound)//If the Instance exists
	{
		delete pSound; //Deletes instance
		pSound = nullptr; //Set the pointer to nullptr
	}
}

bool CSound::Init()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&SoundMgr);
	if (result != FMOD_OK)
		return false;

	result = SoundMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
		return false;
	return true;
}

const bool CSound::AddSound()
{
	FMOD_RESULT result;
	result = SoundMgr->createSound("Resources/Sounds/BackgroundMusic.wav", FMOD_DEFAULT, 0, &bgMusic);
	result = SoundMgr->createSound("Resources/Sounds/BoxDrop.wav", FMOD_DEFAULT, 0, &BoxDrop);
	bgMusic->setMode(FMOD_LOOP_NORMAL);
	result = SoundMgr->createSound("Resources/Sounds/CollectPowerUp.wav", FMOD_DEFAULT, 0, &CollectPowerUp);
	bgMusic->setMode(FMOD_LOOP_NORMAL);
	result = SoundMgr->createSound("Resources/Sounds/GrappleHook.wav", FMOD_DEFAULT, 0, &GrappleHook);
	bgMusic->setMode(FMOD_LOOP_NORMAL);
	result = SoundMgr->createSound("Resources/Sounds/PlayerDeath.wav", FMOD_DEFAULT, 0, &PlayerDeath);
	bgMusic->setMode(FMOD_LOOP_NORMAL);
	result = SoundMgr->createSound("Resources/Sounds/Railgun.mp3", FMOD_DEFAULT, 0, &RailGun);
	bgMusic->setMode(FMOD_LOOP_NORMAL);
	return true;
}

// Constructor //
CSound::CSound()
{

}

// Destructor //
CSound::~CSound()
{

}

