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
	void StartSound(TCHAR* pSoundKey, _uint ID);
	void StartSound(TCHAR* pSoundKey, _uint ID, _float3 thisPosition, _float3 otherPosition);
	void StartSound(TCHAR* pSoundKey, _uint ID, const float volume);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(_uint ID);
	void StopAll();

	// 실행중이면 true
	_bool IsPlaying(_uint eID);
	// 0.f ~ 1.f 
	void SetVolume(_uint ID, _float3 thisPosition, _float3 otherPosition);
	void SetVolume(_uint ID, float fVolume);
	// 0.f ~ 1.f 
	void VolumeIncrease(_uint ID, float fVolume);

private:
	void LoadSoundFile();

private:
	// 사운드 리소스 정보를 갖는 객체 
	std::unordered_map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[(_uint)EChannelID::NumOfChannelID];
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem;

	//
	float m_fVolume[(_uint)EChannelID::NumOfChannelID];
};

END
#endif	