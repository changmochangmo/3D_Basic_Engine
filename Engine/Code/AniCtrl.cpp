#include "EngineStdafx.h"
#include "AniCtrl.h"
#include "FRC.h"


USING(Engine)
CAniCtrl::CAniCtrl(LPD3DXANIMATIONCONTROLLER pAniCtrl)
	: m_pAniCtrl(pAniCtrl)
{
}


CAniCtrl::~CAniCtrl()
{
}

CAniCtrl * CAniCtrl::Create(LPD3DXANIMATIONCONTROLLER pAniCtrl)
{
	CAniCtrl* pInstance = new CAniCtrl(pAniCtrl);
	pInstance->Awake();
	
	return pInstance;
}

void CAniCtrl::Free(void)
{
	OnDestroy();
	delete this;
}

CAniCtrl* CAniCtrl::MakeClone(void)
{
	CAniCtrl* pClone = new CAniCtrl(nullptr);
	LPD3DXANIMATIONCONTROLLER pAniCtrlForClone = NULL;
	
	m_pAniCtrl->CloneAnimationController(m_pAniCtrl->GetMaxNumAnimationOutputs(),
										 m_pAniCtrl->GetMaxNumAnimationSets(),
										 m_pAniCtrl->GetMaxNumTracks(),
										 m_pAniCtrl->GetMaxNumEvents(),
										 &pClone->m_pAniCtrl);

	return pClone;
}

void CAniCtrl::Awake(void)
{
}

void CAniCtrl::OnDestroy(void)
{
	m_pAniCtrl->Release();
}

void CAniCtrl::OnEnable(void)
{
}

void CAniCtrl::OnDisable(void)
{
}

void CAniCtrl::ChangeAniSet(_uint index, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	if (index > m_pAniCtrl->GetMaxNumAnimationSets() - 1)
		index = 0;
	if (m_curIndex == index)
		return;

	if (m_fixTillEnd && !IsItEnd())
		return;

	_int newTrack = m_curTrack == 0 ? 1 : 0;
	
	LPD3DXANIMATIONSET pAS = NULL;

	m_pAniCtrl->GetAnimationSet(index, &pAS);
	m_period = pAS->GetPeriod();

	m_pAniCtrl->SetTrackAnimationSet(newTrack, pAS);
	m_pAniCtrl->UnkeyAllTrackEvents(m_curTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(newTrack);

	//현재 트랙을 끈다.
	m_pAniCtrl->KeyTrackEnable(m_curTrack, FALSE, m_timer + smoothTime);
	//꺼지는 동안 키 속도 세팅
	m_pAniCtrl->KeyTrackSpeed(m_curTrack, 1.f, m_timer, smoothTime, D3DXTRANSITION_LINEAR);
	//꺼지는 동안 가중치
	m_pAniCtrl->KeyTrackWeight(m_curTrack, 1 - changeWeight, m_timer, smoothTime, D3DXTRANSITION_LINEAR);

	//새 트랙 활성화
	m_pAniCtrl->SetTrackEnable(newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(newTrack, 1.f, m_timer, smoothTime, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(newTrack, changeWeight, m_timer, smoothTime, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();
	m_timer = 0.f;

	m_pAniCtrl->SetTrackPosition(newTrack, 0.0);
	m_curIndex = index;
	m_curTrack = newTrack;
	m_fixTillEnd = fixTillEnd;
}

void CAniCtrl::ChangeAniSet(std::string name, _bool fixTillEnd, _double smoothTime, _float changeWeight)
{
	_int newTrack = m_curTrack == 0 ? 1 : 0;
	LPD3DXANIMATIONSET pAS = NULL;
	m_pAniCtrl->GetAnimationSet(m_curIndex, &pAS);
	
	if (pAS->GetName() == name)
		return;

	//이거하던중
	m_pAniCtrl->GetAnimationSetByName(name.c_str(), &pAS);

	m_curIndex = FindIndexByName(name, pAS);
	m_period = pAS->GetPeriod();

	m_pAniCtrl->SetTrackAnimationSet(newTrack, pAS);
	m_pAniCtrl->UnkeyAllTrackEvents(m_curTrack);
	m_pAniCtrl->UnkeyAllTrackEvents(newTrack);

	//현재 트랙을 끈다.
	m_pAniCtrl->KeyTrackEnable(m_curTrack, FALSE, m_timer + 0.25);
	//꺼지는 동안 키 속도 세팅
	m_pAniCtrl->KeyTrackSpeed(m_curTrack, 1.f, m_timer, 0.25, D3DXTRANSITION_LINEAR);
	//꺼지는 동안 가중치
	m_pAniCtrl->KeyTrackWeight(m_curTrack, 0.01f, m_timer, 0.25, D3DXTRANSITION_LINEAR);

	//새 트랙 활성화
	m_pAniCtrl->SetTrackEnable(newTrack, TRUE);
	m_pAniCtrl->KeyTrackSpeed(newTrack, 1.f, m_timer, 0.25, D3DXTRANSITION_LINEAR);
	m_pAniCtrl->KeyTrackWeight(newTrack, 0.99f, m_timer, 0.25, D3DXTRANSITION_LINEAR);

	m_pAniCtrl->ResetTime();
	m_timer = 0.f;

	m_pAniCtrl->SetTrackPosition(newTrack, 0.0);

	m_curTrack = newTrack;
	m_fixTillEnd = fixTillEnd;
}

void CAniCtrl::Play(void)
{
	_float deltaTime = GET_DT;
	m_timer += deltaTime * m_speed;
	if (m_replay == false && m_timer > m_period)
	{
		m_timer = (_float)m_period;
		return;
	}

	m_pAniCtrl->AdvanceTime(deltaTime * m_speed, NULL);
}

_bool CAniCtrl::IsItEnd(void)
{
	D3DXTRACK_DESC	TrackInfo;
	ZeroMemory(&TrackInfo, sizeof(D3DXTRACK_DESC));

	m_pAniCtrl->GetTrackDesc(m_curTrack, &TrackInfo);


	if (TrackInfo.Position >= m_period - 0.25)
		return true;

	
	return false;
}

_uint CAniCtrl::FindIndexByName(std::string const & name, LPD3DXANIMATIONSET pAS)
{
	for (_uint i = 0; i < m_pAniCtrl->GetNumAnimationSets(); ++i)
	{
		LPD3DXANIMATIONSET compareAS;
		m_pAniCtrl->GetAnimationSet(i, &compareAS);
		if (compareAS == pAS)
			return i;
	}

	MSG_BOX(__FILE__, L"Failed to find animationSet by name in FindIndexByName");
	ABORT;
	return UNDEFINED;
}
