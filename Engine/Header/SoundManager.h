#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "Engine.h"

BEGIN(Engine)
class ENGINE_DLL CSoundManager final : public CEngine
{
public:
	DECLARE_SINGLETON(CSoundManager)
public:
	void		Awake(void) override;

	void		OnDestroy(void);
public:
	void StartSound(std::wstring soundKey, EChannelID eID);
	void PlayBGM(std::wstring pSoundKey);
	void StopSound(EChannelID eID);
	void StopAll();

private:
	void LoadSoundFile(); 

private:
	// 사운드 리소스 정보를 갖는 객체 
	std::unordered_map<std::wstring, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[(_uint)EChannelID::NumOfChannelID]; 
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 

};

END
#endif	