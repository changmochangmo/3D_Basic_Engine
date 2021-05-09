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

	
}

void CTransformC::FixedUpdate(SP(CComponent) spThis)
{
}

void CTransformC::Update(SP(CComponent) spThis)
{
	SlerpXZ();
}

void CTransformC::LateUpdate(SP(CComponent) spThis)
{
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
	__super::OnDisable();
}

#pragma region TransformSettors
void CTransformC::SetPosition(_float3 position)
{
	m_position = position;
}

void CTransformC::SetPosition(_float posX, _float posY, _float posZ)
{
	m_position.x = posX;
	m_position.y = posY;
	m_position.z = posZ;
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
}

void CTransformC::SetRotation(_float rotX, _float rotY, _float rotZ)
{
	m_rotation.x = rotX;
	m_rotation.y = rotY;
	m_rotation.z = rotZ;
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
}

void CTransformC::SetSize(_float sizeX, _float sizeY, _float sizeZ)
{
	m_size.x = sizeX;
	m_size.y = sizeY;
	m_size.z = sizeZ;
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
}

void CTransformC::AddPosition(_float3 position)
{
	m_position += position;
}

void CTransformC::AddPositionX(_float adder)
{
	m_position.x += adder;
}

void CTransformC::AddPositionY(_float adder)
{
	m_position.y += adder;
}

void CTransformC::AddPositionZ(_float adder)
{
	m_position.z += adder;
}

void CTransformC::AddRotation(_float3 rotation)
{
	m_rotation += rotation;
	UpdateForward();
}

void CTransformC::AddRotationX(_float adder)
{
	m_rotation.x += adder;
	UpdateForward();
}

void CTransformC::AddRotationY(_float adder)
{
	m_rotation.y += adder;
	UpdateForward();
}

void CTransformC::AddRotationZ(_float adder)
{
	m_rotation.z += adder;
	UpdateForward();
}

void CTransformC::AddSize(_float3 size)
{
	m_size += size;
}

void CTransformC::AddSizeX(_float adder)
{
	m_size.x += adder;
}

void CTransformC::AddSizeY(_float adder)
{
	m_size.y += adder;
}

void CTransformC::AddSizeZ(_float adder)
{
	m_size.z += adder;
}
#pragma endregion

#pragma region Move
void CTransformC::SlerpXZ(void)
{
	if (D3DXVec3LengthSq(&m_goalForward) > EPSILON)
	{
		_float dotTwoForward = D3DXVec3Dot(&m_goalForward, &m_forward);
		GET_MATH->RoundOffRange(dotTwoForward, 1);

		_float includedAngle = acos(dotTwoForward);
		if (dotTwoForward > 1.f || dotTwoForward < -1)
			int a = 5;
		if (abs(includedAngle) < m_slerpSpeed * GET_DT)
		{
			SetForward(m_goalForward);
			m_goalForward = ZERO_VECTOR;
			return;
		}

		_float3 determinant;
		D3DXVec3Cross(&determinant, &m_forward, &m_goalForward);
		
		if (determinant.y < 0)
			AddRotationY(-m_slerpSpeed * GET_DT);
		else
			AddRotationY(m_slerpSpeed * GET_DT);
	}
}

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
