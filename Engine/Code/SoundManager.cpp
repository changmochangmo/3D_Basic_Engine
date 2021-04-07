#include "EngineStdafx.h"
#include "SoundManager.h"
#include "DeviceManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSoundManager)

void CSoundManager::Awake(void)
{
	if (FMOD_System_Create(&m_pSystem) != FMOD_OK)
	{
		MSG_BOX(__FILE__, L"FMOD_SYSTEM_CREATE FAILED");
		abort();
	}

	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	if (FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL) != FMOD_OK)
	{
		MSG_BOX(__FILE__, L"FMOD_SYSTEM_INIT FAILED");
		abort();
	}

	LoadSoundFile();
}

void CSoundManager::OnDestroy(void)
{
	for (auto& Mypair : m_mapSound)
	{
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear();
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}



void CSoundManager::StartSound(std::wstring soundKey, EChannelID eID)
{
	std::unordered_map<std::wstring, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter) 
	{
		return (soundKey == iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE; 
	if (FMOD_Channel_IsPlaying(m_pChannelArr[(_uint)eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)eID]);
	}
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlayBGM(std::wstring soundKey)
{
	std::unordered_map<std::wstring, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)
	{
		return (soundKey == iter.first);
	});

	if (iter == m_mapSound.end())
		return;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[(_uint)EChannelID::BGM]);
	FMOD_Channel_SetMode(m_pChannelArr[(_uint)EChannelID::BGM], FMOD_LOOP_NORMAL);
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::StopSound(EChannelID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[(_uint)eID]);
}

void CSoundManager::StopAll()
{
	for (int i = 0 ; i < (_uint)EChannelID::NumOfChannelID ; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundManager::LoadSoundFile()
{
	WIN32_FIND_DATA fd;
	std::wstring curDir = L"..\\..\\Resource\\Sound";
	std::wstring fullFilePath, curFile;

	HANDLE handle = FindFirstFile((curDir + L"\\*").c_str(), &fd);

	if (handle == INVALID_HANDLE_VALUE)
	{
		MSG_BOX(__FILE__, L"Given path is wrong during getting handle in SoundManager");
		abort();
	}

	do
	{
		curFile = fd.cFileName;
		fullFilePath = curDir + L"\\" + curFile;

		if (curFile[0] == '.')
			continue;

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, 
												   WStrToStr(fullFilePath).c_str(), 
												   FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			m_mapSound.emplace(fd.cFileName, pSound);
		}
		
	} while (FindNextFile(handle, &fd));

	FMOD_System_Update(m_pSystem);
}


