#include "EngineStdafx.h"
#include "SoundManager.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSoundManager)

void CSoundManager::Awake(void)
{
	FMOD_System_Create(&m_pSystem);

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile();

	SetVolume((_uint)EChannelID::BGM, 0.5f);
}

void CSoundManager::OnDestroy(void)
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}



void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID)
{
	std::unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[ID]);
		m_fVolume[ID] = 1.f;
	}
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID, _float3 thisPosition, _float3 otherPosition)
{
	std::unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[ID]);
		m_fVolume[ID] = 1.f;
	}
	// 볼륨조절
	SetVolume(ID, thisPosition, otherPosition);
}

void CSoundManager::StartSound(TCHAR * pSoundKey, _uint ID, const float volume)
{
}

void CSoundManager::PlayBGM(TCHAR * pSoundKey)
{
	std::unordered_map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return !lstrcmp(pSoundKey, iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)EChannelID::BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[(_uint)EChannelID::BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StopSound(_uint ID)
{
	FMOD_Channel_Stop(m_pChannelArr[ID]);
}

void CSoundManager::StopAll()
{
	for (int i = 0; i < (_uint)EChannelID::NumOfChannelID; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

_bool CSoundManager::IsPlaying(_uint ID)
{
	FMOD_BOOL bPlay = FALSE;
	if (FMOD_Channel_IsPlaying(m_pChannelArr[ID], &bPlay))
		return false;
	else
		return true;
}

void CSoundManager::SetVolume(_uint ID, _float3 thisPosition, _float3 otherPosition)
{
	_float3 dis = otherPosition - thisPosition;
	float disForVolume = D3DXVec3Length(&dis);

	if (1000.f <= disForVolume)
		m_fVolume[ID] = 0.f;

	float volume = 1.f - disForVolume / 1000.f;

	m_fVolume[ID] = volume;

	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::SetVolume(_uint ID, float fVolume)
{
	if (fVolume > 1.f)
		fVolume = 1.f;
	else if (fVolume < 0.f)
		fVolume = 0.f;
	else
		m_fVolume[ID] = fVolume;

	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::VolumeIncrease(_uint ID, float fVolume)
{
	m_fVolume[ID] += fVolume;

	if (m_fVolume[ID] > 1.f)
		m_fVolume[ID] = 1.f;
	else if (m_fVolume[ID] < 0.f)
		m_fVolume[ID] = 0.f;
	FMOD_Channel_SetVolume(m_pChannelArr[ID], m_fVolume[ID]);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::LoadSoundFile()
{
	_finddata_t fd;

	long handle = _findfirst("../../Resource/Sound/*.*", &fd);

	if (handle == 0)
		return;

	int iResult = 0;

	char szCurPath[128] = "../../Resource/Sound/";
	char szFullPath[128] = "";

	do
	{
		strcpy_s(szFullPath, szCurPath);
		strcat_s(szFullPath, fd.name);

		if (fd.name[0] == '.')
		{
			iResult = _findnext(handle, &fd);
			continue;
		}

		FMOD_SOUND* pSound = nullptr;

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1;

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		iResult = _findnext(handle, &fd);
	} while (iResult != -1);

	FMOD_System_Update(m_pSystem);
	_findclose(handle);
}


