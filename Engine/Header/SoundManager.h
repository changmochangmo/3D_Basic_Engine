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
	void StartSound(TCHAR* pSoundKey, EChannelID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(EChannelID eID);
	void StopAll();

private:
	void LoadSoundFile(); 

private:
	// ���� ���ҽ� ������ ���� ��ü 
	std::unordered_map<TCHAR*, FMOD_SOUND*> m_mapSound;
	// FMOD_CHANNEL : ����ϰ� �ִ� ���带 ������ ��ü 
	FMOD_CHANNEL* m_pChannelArr[(_uint)EChannelID::NumOfChannelID]; 
	// ���� ,ä�� ��ü �� ��ġ�� �����ϴ� ��ü 
	FMOD_SYSTEM* m_pSystem; 

};

END
#endif	