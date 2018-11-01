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
// Mail         : richard.wul7481@mediadesign.school.nz
//

#ifndef CSound_H
#define CSound_H
#pragma once
#include "Utility.h"

class CSound
{
	// Member Functions //
public:
	static CSound* GetInstance();
	static void DestroyInstance();
	bool Init();
	const bool AddSound();
	FMOD::System * SoundMgr;
	//Spliting different Channels
	FMOD::Sound* bgMusic;
	FMOD::Sound* BoxDrop;
	FMOD::Sound* CollectPowerUp;
	FMOD::Sound* GrappleHook;
	FMOD::Sound* PlayerDeath;
	FMOD::Sound* RailGun;
	FMOD::Channel* BgMusicChannel;
	FMOD::Channel* PickUpSoundChannel;
	FMOD::Channel* PowerUpChannel;
	FMOD::Channel* OtherChannel;
private:


	CSound();
	~CSound();
	static CSound* pSound;
	CSound(CSound const&) = delete; //Deletes copy constructor
	void operator = (CSound const&) = delete; //Deletes the operator assgined to the copy constructor

};

#endif // !CSound_H
