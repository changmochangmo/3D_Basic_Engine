#ifndef ENGINESTRUCTURE_H
#define ENGINESTRUCTURE_H


namespace Engine
{
#pragma region GraphicsStructure
	typedef struct _tagIndex16
	{
		WORD _0, _1, _2;
	}INDEX16;

	typedef struct _CustomVertex
	{
		_float3	position;
		_float3 normal;
		_float2	uv;
	}CUSTOM_VERTEX;
	const _uint customFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_NORMAL;

	typedef struct _CustomVertex2D
	{
		_CustomVertex2D()
			:position(0.0f, 0.0f, 0.0f),
			texture(0.0f, 0.0f)
		{}

		_CustomVertex2D(float x, float y, float z, float u, float v)
			:position(x, y, z),
			texture(u, v)
		{}

		_CustomVertex2D(const D3DXVECTOR3& v, const D3DXVECTOR3& uv)
			:position(v),
			texture(uv)
		{}

		D3DXVECTOR3 position;   // Position Vector
		D3DXVECTOR2 texture;    // Texture  Coordinate
	}CUSTOM_VERTEX2D;
	const _uint customFVF2D = (D3DFVF_XYZ | D3DFVF_TEX1);

	typedef struct _TexData
	{
		LPDIRECT3DTEXTURE9 pTexture;
		D3DXIMAGE_INFO imageInfo;
	}TEXTURE_DATA;

	typedef struct _Face
	{
		_uint vertexIndex[3];
		_uint uvIndex[3];
		_uint normIndex[3];
	}FACE;

	typedef struct _DerivedD3DXFRAME : public D3DXFRAME
	{
		_mat		CombinedTransformMatrix;
	}D3DXFRAME_DERIVED;

	typedef struct _DerivedD3DXMESHCONTAINER : public D3DXMESHCONTAINER
	{
		LPD3DXMESH				pOriMesh;

		_ulong					numBones;

		_mat*					pFrameOffsetMatrix;
		_mat**					ppCombinedTransformMatrix;

		_mat*					pRenderingMatrix;	// 최종적으로 변환이 끝나서 그리기를 수행하기 위한 행렬 정보
													// pFrameOffsetMatrix * (*ppCombinedTransformMatrix)

		_int					texIndexStart;
	}D3DXMESHCONTAINER_DERIVED;
#pragma endregion

	class CCollider;
	struct _CollisionInfo
	{
		_CollisionInfo(const _CollisionInfo& ci)
			: pMyCollider(ci.pMyCollider), pOtherCollider(ci.pOtherCollider), hitPoint(ci.hitPoint), normal(ci.normal), penetLength(ci.penetLength)
		{
		}
		_CollisionInfo(CCollider* pMine, CCollider* pOthers, _float3 cHitPoint, _float3 cNormal, _float cPenet)
			: pMyCollider(pMine), pOtherCollider(pOthers), hitPoint(cHitPoint), normal(cNormal), penetLength(cPenet)
		{
		}

		CCollider*	pMyCollider		= nullptr;
		CCollider*	pOtherCollider	= nullptr;	
		_float3		hitPoint		= ZERO_VECTOR;
		_float3		normal			= ZERO_VECTOR;
		_float		penetLength		= 0.f;
	};

	//Text
	struct _Text
	{
		std::wstring	m_message;
		D3DXVECTOR3		m_position;
		D3DXCOLOR		m_color;
		_bool			m_isVisible;
	};
}
#endif // !ENGINESTRUCTURE_H            `

