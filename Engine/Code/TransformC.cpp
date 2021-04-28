#include "EngineStdafx.h"
#include "Object.h"
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

SP(CComponent) CTransformC::MakeClone(CObject* pObject)
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

	if (m_pParent == nullptr && m_vChildren.size() != 0)
		UpdateFinalWorldMatrix();
}

void CTransformC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTransformC::Update(SP(CComponent) spThis)
{
	if(m_pParent != nullptr)
		m_parentChanged = m_pParent->GetHasChanged();
}

void CTransformC::LateUpdate(SP(CComponent) spThis)
{
	if (m_hasChanged)
		UpdateWorldMatrix();
	
	if (m_parentChanged)
		UpdateFinalWorldMatrix();
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
	__super::OnDisable();
}

#pragma region TransformSettors
void CTransformC::SetPosition(_float3 position)
{
	m_position = position;
	m_hasChanged = true;
}

void CTransformC::SetPositionX(_float posX)
{
	m_position.x = posX;
}

void CTransformC::SetPositionY(_float posY)
{
	m_position.y = posY;
}

void CTransformC::SetPositionZ(_float posZ)
{
	m_position.z = posZ;
}

void CTransformC::SetRotation(_float3 rotation)
{
	m_rotation = rotation;
	UpdateForward();
	m_hasChanged = true;
}

void CTransformC::SetRotationX(_float rotationX)
{
	m_rotation.x = rotationX;
}

void CTransformC::SetRotationY(_float rotationY)
{
	m_rotation.y = rotationY;
}

void CTransformC::SetRotationZ(_float rotationZ)
{
	m_rotation.z = rotationZ;
}

void CTransformC::SetSize(_float3 size)
{
	m_size = size;
	m_hasChanged = true;
}

void CTransformC::SetSizeX(_float sizeX)
{
	m_size.x = sizeX;
}

void CTransformC::SetSizeY(_float sizeY)
{
	m_size.y = sizeY;
}

void CTransformC::SetSizeZ(_float sizeZ)
{
	m_size.z = sizeZ;
}

void CTransformC::SetForward(_float3 lookAt)
{
	m_forward = lookAt;

	D3DXVec3Normalize(&m_forward, &m_forward);
	UpdateRotation();
	m_hasChanged = true;
}

void CTransformC::AddChild(SP(CTransformC) spChild)
{
	m_vChildren.emplace_back(spChild);
	spChild->SetParent(this);
}

void CTransformC::DeleteChild(CTransformC * pChild)
{
	for (auto& it = m_vChildren.begin(); it != m_vChildren.end(); )
	{
		if ((*it).get() == pChild)
		{
			(*it).reset();
			it = m_vChildren.erase(it);
			continue;
		}

		++it;
	}
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

void CTransformC::CopyTransform(CTransformC const & transform)
{
	*this = transform;
}

void CTransformC::operator=(CTransformC const & rhs)
{
	m_position	= rhs.m_position;
	m_rotation	= rhs.m_rotation;
	m_size		= rhs.m_size;

	m_forward	= rhs.m_forward;
	m_up		= rhs.m_up;
	m_right		= rhs.m_right;

	m_worldMat	= rhs.m_worldMat;
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

	m_worldMat			= size * rotateX * rotateY * rotateZ * translation;
	m_worldMatNoScale	= rotateX * rotateY * rotateZ * translation;
}

void CTransformC::UpdateFinalWorldMatrix(void)
{
	if (m_hasChanged)
		UpdateWorldMatrix();

	if (m_pParent == nullptr)
	{
		m_finalWorldMat			= m_worldMat;
		m_finalWorldMatNoScale	= m_worldMatNoScale;
	}
	else if (m_parentChanged == true)
	{
		D3DXMatrixMultiply(&m_finalWorldMat, &m_worldMat, &m_pParent->GetFinalWorldMatNoScale());
		D3DXMatrixMultiply(&m_finalWorldMatNoScale, &m_worldMatNoScale, &m_pParent->GetFinalWorldMatNoScale());
	}
		

	if (m_hasChanged || m_parentChanged)
	{
		UpdateFinalPosition();
		UpdateFinalRotation();
		UpdateFinalAxis();

		m_parentChanged = false;
		m_hasChanged	= false;
	}


	for (auto& it = m_vChildren.begin(); it != m_vChildren.end(); )
	{
		if ((*it)->GetOwner() == nullptr)
		{
			(*it).reset();
			it = m_vChildren.erase(it);
			continue;
		}

		if ((*it)->GetIsEnabled())
			(*it)->UpdateFinalWorldMatrix();

		++it;
	}
}

void CTransformC::UpdateFinalPosition(void)
{
	m_finalPos = _float3(m_finalWorldMat._41, m_finalWorldMat._42, m_finalWorldMat._43);
}

void CTransformC::UpdateFinalRotation(void)
{
	D3DXQUATERNION localQuat;
	D3DXQuaternionRotationYawPitchRoll(&localQuat, m_rotation.y, m_rotation.x, m_rotation.z);

	if (m_pParent != nullptr)
	{
		_float3 parentRot = m_pParent->GetFinalRot();
		D3DXQUATERNION parentQuat;
		D3DXQuaternionRotationYawPitchRoll(&parentQuat, parentRot.y, parentRot.x, parentRot.z);


		localQuat = localQuat * parentQuat;
	}

	m_finalRot = GET_MATH->QuatToRad(localQuat);
}

void CTransformC::UpdateFinalAxis(void)
{
	_mat rot;
	_float yaw, pitch, roll;
	yaw		= m_finalRot.y;
	pitch	= m_finalRot.x;
	roll	= m_finalRot.z;

	D3DXMatrixRotationYawPitchRoll(&rot, yaw, pitch, roll);
	D3DXVec3TransformNormal(&m_finalForward, &FORWARD_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_finalUp, &UP_VECTOR, &rot);
	D3DXVec3TransformNormal(&m_finalRight, &RIGHT_VECTOR, &rot);

	D3DXVec3Normalize(&m_finalForward, &m_finalForward);
	D3DXVec3Normalize(&m_finalUp, &m_finalUp);
	D3DXVec3Normalize(&m_finalRight, &m_finalRight);
}

