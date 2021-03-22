#include "stdafx.h"
#include "EventScene.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "WndApp.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

CEventScene::CEventScene() : m_bpm(0.f), m_startCount(0.f), m_isBGMStart(false), m_count(0)
, m_eventTimer(0.f)
, m_isEventStart(false)
, m_isEventEnd(false)
, m_eventCount(0)
, m_curPlaySoundTime(0.f)
, m_shakeTime(0.f)
, m_countDown(0.f)
, m_isCameraStart(false)
{
}


CEventScene::~CEventScene()
{
}

SHARED(Engine::CScene) CEventScene::Create()
{
	SHARED(CEventScene) pScene(new CEventScene, Engine::SmartDeleter<CEventScene>);

	Engine::CSceneManager::GetInstance()->SetSceneName(L"EventScene");

	return pScene;
}

void CEventScene::Awake(void)
{
	__super::Awake();

	SetWindowText(Engine::GET_HANDLE, m_name.c_str());

	Engine::CSoundManager::GetInstance()->StopAll();

	InitLayers();
	InitPrototypes();
}

void CEventScene::Start(void)
{
	__super::Start();

	SpawnNormalBlock();
	SpawnPushBlock();
	SpawnChessBoard();

	SHARED(Engine::CGameObject) pObj = nullptr;

	m_pMainCamera = Engine::ADD_CLONE(L"Camera", L"Camera", true)->GetComponent<Engine::CCameraComponent>();

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"Player", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3.5f, 7, -6));
	pObj->GetComponent<Engine::CTransformComponent>()->SetRotationY(180.f);
	m_pPlayer = pObj;

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"Player", L"WalkBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(4.f, 8.f, -1.f));
	pObj->GetComponent<Engine::CTransformComponent>()->SetScale(_float3(0.5f, 1, 0.5f));
	m_pSubPlayer = pObj;
	
	
}

_uint CEventScene::FixedUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::FixedUpdate())
		return event;

	if (m_pMainCamera->GetIsStarted() && !m_isCameraStart)
	{
		m_pMainCamera->GetTransform()->SetPosition(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition());
		m_pMainCamera->GetTransform()->SetRotationX(45.f);
		m_pMainCamera->GetTransform()->SetRotationY(D3DXToRadian(90.f));
		m_isCameraStart = true;

	}
	ChangeRedPos();
	return event;
}

_uint CEventScene::Update(void)
{
	_uint event = NO_EVENT;
	if (event = __super::Update())
		return event;
	
	if (m_isCameraStart)
	{
		m_pPlayer->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(3.5f, 7, -6));
		m_pMainCamera->GetTransform()->SetPositionX(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().x);
		m_pMainCamera->GetTransform()->SetPositionY(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().y);
	}

	if (m_pSubPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().y >= 1.f)
	{
		m_pSubPlayer->GetComponent<Engine::CTransformComponent>()->AddPositionY(-5.f * GET_DT);
	}	
	else if (m_pSubPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().y <= 1.f && m_shakeTime <= 1.f)
	{
		m_shakeTime += GET_DT;
		if (m_shakeTime <= 0.2f)
		{
			Engine::CSoundManager::GetInstance()->StartSound(L"Land.wav", Engine::CHANNELID::LAND);
			m_pMainCamera->GetTransform()->SetPositionX(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().x + rand() % 2 * 0.5f);
			m_pMainCamera->GetTransform()->SetPositionY(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().y + rand() % 2 * 0.5f);
			m_pMainCamera->GetTransform()->SetPositionZ(m_pPlayer->GetComponent<Engine::CTransformComponent>()->GetPosition().z + rand() % 2 * 0.5f);
		}
	}

	

	if (m_curPlaySoundTime >= 48.f)
	{
		m_eventTimer = 0.f;
		m_curPlaySoundTime = 0.f;
	}

	if (!m_isBGMStart && m_shakeTime >= 1.f)
	{
		Engine::CSoundManager::GetInstance()->StopSound(Engine::CHANNELID::LAND);

		if(m_startCount <= 2.5f)
			m_countDown += GET_DT;

		m_startCount += GET_DT;		

		if (m_countDown >= 1.f)
		{
			Engine::CSoundManager::GetInstance()->StartSound(L"Hat.wav", Engine::CHANNELID::HAT);
			m_countDown = 0.f;
		}
	}


	if (m_startCount >= 3.f)
	{
		Engine::CSoundManager::GetInstance()->StopSound(Engine::CHANNELID::HAT);
		Engine::CSoundManager::GetInstance()->PlayBGM(L"Rhythm.wav");
		m_startCount = 0.f;

		m_isBGMStart = true;
	}
	if (m_isBGMStart)
	{
		m_curPlaySoundTime += GET_DT;		
		m_bpm += GET_DT;
	}

	if (m_bpm >= 0.5f)
	{
		ChangePosition();
		m_pMainCamera->GetTransform()->AddPositionY(0.2f);
		m_bpm = 0;
	}

	return event;
}

_uint CEventScene::LateUpdate(void)
{
	_uint event = NO_EVENT;
	if (event = __super::LateUpdate())
		return event;


	return event;

}

void CEventScene::OnDestroy(void)
{
	__super::OnDestroy();
}

void CEventScene::OnEnable(void)
{
}

void CEventScene::OnDisable(void)
{
}

void CEventScene::InitLayers(void)
{
	AddLayer(L"Default");
	AddLayer(L"Player");
	AddLayer(L"Camera");
	AddLayer(L"EventBlock");
	AddLayer(L"NormalBlock");
}

void CEventScene::InitPrototypes(void)
{
}

// ���� ���� �� ��� �� ��ġ
void CEventScene::SpawnNormalBlock()
{
	SHARED(Engine::CGameObject) pObj = nullptr;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(i, 0, 8.f + j));

			pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
			pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(i , 0, -1.f - j));
		}
	}
}

// ���� ���� �� �о�� �� ��ġ
void CEventScene::SpawnPushBlock()
{
	SHARED(Engine::CGameObject) pObj = nullptr;

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(10, 1, 2));
	pObj->GetComponent<Engine::CTransformComponent>()->SetRotationZ(D3DXToRadian(90.f));
	m_vRedBlock.emplace_back(pObj);

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(10, 1, 6));
	pObj->GetComponent<Engine::CTransformComponent>()->SetRotationZ(D3DXToRadian(90.f));
	m_vRedBlock.emplace_back(pObj);

	pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RedBlock", true);
	pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(-3, 1, 4));
	pObj->GetComponent<Engine::CTransformComponent>()->SetRotationZ(D3DXToRadian(90.f));
	m_vRedBlock.emplace_back(pObj);
}

// ���� ���� �� �̺�Ʈ �� ��ġ
void CEventScene::SpawnChessBoard()
{
	SHARED(Engine::CGameObject) pObj = nullptr;

	for (int i = 0; i < 8; ++i)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (j % 2 == 0)
				{
					pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
					pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0, 1.f * j));
				}
				else
				{
					pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RhythmBlock", true);
					pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0.f, 1.f * j));
				}
				m_vBlock.emplace_back(pObj);
			}
		}
		else
		{
			for (int j = 0; j < 8; ++j)
			{
				if (j % 2 == 1)
				{
					pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"NormalBlock", L"WhiteBlock", true);
					pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0, 1.f * j));
				}
				else
				{
					pObj = Engine::CObjectFactory::GetInstance()->AddClone(L"EventBlock", L"RhythmBlock", true);
					pObj->GetComponent<Engine::CTransformComponent>()->SetPosition(_float3(1.f * i, 0.f, 1.f * j));
				}
				m_vBlock.emplace_back(pObj);
			}
		}

	}
}

void CEventScene::ChangePosition()
{
	for (_int i = 0; i < 8; ++i)
	{
		for (_int j = 0; j < 8; ++j)
		{
			if (m_vBlock[j * 8 + i]->GetComponent<Engine::CTransformComponent>()->GetPosition().x >= 7.f)
			{
				m_vBlock[j * 8 + i]->GetComponent<Engine::CTransformComponent>()->SetPositionX(0.f);
			}
			else
			{
				m_vBlock[j * 8 + i]->GetComponent<Engine::CTransformComponent>()->AddPositionX(1.f);
			}
		}
	}
}

void CEventScene::ChangeRedPos()
{
	// BGM�� ������ �̺�Ʈ ����
	if (m_isBGMStart && !m_isEventStart)
	{
		m_eventTimer += GET_DT;
		
		if (m_eventTimer >= 1.6f)
		{
			m_isEventStart = true;
			m_isEventEnd = false;
			m_eventTimer = 0.f;
		}
	}
	if (m_isEventStart && !m_isEventEnd)
	{
		// �̺�Ʈ�� ���۵Ǹ� �̺�Ʈ Ÿ�̸Ӱ� ���� ��.
		m_eventTimer += GET_DT;

		//�̺�Ʈ Ÿ�̸Ӱ� 2.3�ʰ� �� ������ ���� ���� �̵�
		if (m_eventTimer <= 2.3f)
		{
			switch (m_eventCount)
			{
			case 0:
				m_vRedBlock[0]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[0]->GetComponent<Engine::CTransformComponent>()->GetPosition().x - 6.f * GET_DT);
				m_vRedBlock[1]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[1]->GetComponent<Engine::CTransformComponent>()->GetPosition().x - 6.f * GET_DT);
				m_vRedBlock[2]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[2]->GetComponent<Engine::CTransformComponent>()->GetPosition().x + 6.f * GET_DT);
				break;
			case 1:
				m_vRedBlock[0]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[0]->GetComponent<Engine::CTransformComponent>()->GetPosition().x + 6.f * GET_DT);
				m_vRedBlock[1]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[1]->GetComponent<Engine::CTransformComponent>()->GetPosition().x + 6.f * GET_DT);
				m_vRedBlock[2]->GetComponent<Engine::CTransformComponent>()->SetPositionX(m_vRedBlock[2]->GetComponent<Engine::CTransformComponent>()->GetPosition().x - 6.f * GET_DT);
				break;
			default:
				break;
			}
		}
		else
		{
			// �̺�Ʈ Ÿ�̸Ӱ� n�ʰ� �Ǿ��� �� �̺�Ʈ ����
			m_eventCount++;
			if (m_eventCount > 1)
			{
				m_eventCount = 0;
			}
			m_isEventStart = false;
			m_isEventEnd = true;
			m_eventTimer = 0.f;
		}
	}
}

HRESULT CEventScene::SceneLoad()
{
	return E_NOTIMPL;
}
