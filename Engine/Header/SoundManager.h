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

	// �������̸� true
	_bool IsPlaying(_uint eID);
	// 0.f ~ 1.f 
	void SetVolume(_uint ID, _float3 thisPosition, _float3 otherPosition);
	void SetVolume(_uint ID, float fVolume);
	// 0.f ~ 1.f 
	void VolumeIncrease(_uint ID, float fVolume);

private:
	void LoadSoundFile();

private:
	// ���� ���ҽ� ������ ���� ��ü 
	std::unordered_map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[(_uint)EChannelID::NumOfChannelID];
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem;

	//
	float m_fVolume[(_uint)EChannelID::NumOfChannelID];
};

END
#endif	