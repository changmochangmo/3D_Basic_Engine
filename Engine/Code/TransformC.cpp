#include "EngineStdafx.h"
#include "GameObject.h"
#include "DataStore.h"
#include "FRC.h"

USING(Engine)
CTransformC::CTransformC(void)  
{
}

CTransformC::~CTransformC(void)
{
	OnDestroy();
}

SP(CComponent) CTransformC::MakeClone(CGameObject* pObject)
{
	SP(CTransformC) spClone(new CTransformC);
	__super::InitClone(spClone, pObject);

	spClone->SetPosition(m_position);
	spClone->SetRotation(m_rotation);
	spClone->SetSize(m_size);
	spClone->UpdateWorldMatrix();

	return spClone;
}

void CTransformC::Awake(void)
{
	__super::Awake();
	m_componentID = (_int)m_s_componentID;
}

void CTransformC::Start(SP(CComponent) spThis)
{
	__super::Start(spThis);
}

void CTransformC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTransformC::Update(SP(CComponent) spThis)
{
	
}

void CTransformC::LateUpdate(SP(CComponent) spThis)
{
	if (m_hasChanged)
		UpdateWorldMatrix();
}

void CTransformC::OnDestroy(void)
{
}

void CTransformC::OnEnable(void)
{
	__super::OnEnable();
}

void CTransformC::OnDisable(void)
{
}

#pragma region TransformSettors
void CTransformC::SetPosition(_float3 position)
{
	m_position = position;
	m_hasChanged = true;
}

void CTransformC::SetRotation(_float3 rotation)
{
	m_rotation = rotation;
	UpdateForward();
	m_hasChanged = true;
}

void CTransformC::SetSize(_float3 size)
{
	m_size = size;
	m_hasChanged = true;
}

void CTransformC::SetForward(_float3 lookAt)
{
	m_forward = lookAt;

	D3DXVec3Normalize(&m_forward, &m_forward);
	UpdateRotation();
	m_hasChanged = true;
}

void CTransformC::AddPosition(_float3 position)
{
	m_position += position;
	m_hasChanged = true;
}

void CTransformC::AddPositionX(_float adder)
{
	m_position.x += adder;
	m_hasChanged = true;
}

void CTransformC::AddPositionY(_float adder)
{
	m_position.y += adder;
	m_hasChanged = true;
}

void CTransformC::AddPositionZ(_float adder)
{
	m_position.z += adder;
	m_hasChanged = true;
}

void CTransformC::AddRotation(_float3 rotation)
{
	m_rotation += rotation;
	m_hasChanged = true;
	UpdateForward();
}

void CTransformC::AddRotationX(_float adder)
{
	m_rotation.x += adder;
	m_hasChanged = true;
	UpdateForward();
}

void CTransformC::AddRotationY(_float adder)
{
	m_rotation.y += adder;
	m_hasChanged = true;
	UpdateForward();
}

void CTransformC::AddRotationZ(_float adder)
{
	m_rotation.z += adder;
	m_hasChanged = true;
	UpdateForward();
}

void CTransformC::AddSize(_float3 size)
{
	m_size += size;
	m_hasChanged = true;
}

void CTransformC::AddSizeX(_float adder)
{
	m_size.x += adder;
	m_hasChanged = true;
}

void CTransformC::AddSizeY(_float adder)
{
	m_size.y += adder;
	m_hasChanged = true;
}

void CTransformC::AddSizeZ(_float adder)
{
	m_size.z += adder;
	m_hasChanged = true;
}
#pragma endregion

#pragma region Move
void CTransformC::MoveForward(_float magnitude)
{
	AddPosition(m_forward * magnitude);
}

void CTransformC::MoveBackward(_float magnitude)
{
	AddPosition(-m_forward * magnitude);
}

void CTransformC::MoveLeft(_float magnitude)
{
	AddPosition(-m_right * magnitude);
}

void CTransformC::MoveRight(_float magnitude)
{
	AddPosition(m_right * magnitude);
}

void CTransformC::MoveUp(_float magnitude)
{
	AddPosition(m_up * magnitude);
}

void CTransformC::MoveDown(_float magnitude)
{
	AddPosition(-m_up * magnitude);
}
#pragma endregion

void CTransformC::UpdateForward(void)
{
	_mat rot;
	_float yaw, pitch, roll;
	yaw		= m_rotation.y;
	pitch	= m_rotation.x;
	roll	= m_rotation.z;

	D3DXMatrixRotationYawPitchRoll(&rot, yaw, pitch, roll);
	D3DXVec3TransformNormal(&m_forward, &FORWARD_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_up, &UP_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_right, &RIGHT_VECTOR, &rot);

	D3DXVec3Normalize(&m_forward, &m_forward);
	D3DXVec3Normalize(&m_up, &m_up);
	D3DXVec3Normalize(&m_right, &m_right);
}

void CTransformC::UpdateRotation(void)
{
	D3DXVec3Cross(&m_right, &m_up, &m_forward);
	D3DXVec3Normalize(&m_right, &m_right);

	D3DXVec3Cross(&m_up, &m_forward, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	_mat rotMatrix(m_right.x,		m_right.y,		m_right.z,		0.f,
				   m_up.x,			m_up.y,			m_up.z,			0.f,
				   m_forward.x,		m_forward.y,	m_forward.z,	0.f,
				   0.f,				0.f,			0.f,			1.f);

	_quat rotQuat;
	D3DXQuaternionRotationMatrix(&rotQuat, &rotMatrix);
	D3DXQuaternionNormalize(&rotQuat, &rotQuat);


	m_rotation = GET_MATH->QuatToRad(rotQuat);
}

void CTransformC::UpdateWorldMatrix(void)
{
	_mat rotateX, rotateY, rotateZ, size, translation, result;

	D3DXMatrixRotationX(&rotateX, m_rotation.x);
	D3DXMatrixRotationY(&rotateY, m_rotation.y);
	D3DXMatrixRotationZ(&rotateZ, m_rotation.z);
    
    D3DXMatrixScaling(&size, m_size.x, 
                             m_size.y,
                             m_size.z);
    
    D3DXMatrixTranslation(&translation, m_position.x, 
                                        m_position.y,
                                        m_position.z);

	m_worldMat = size * rotateX * rotateY * rotateZ * translation;

	m_hasChanged = false;
}


