#ifndef ENGINESTRUCTURE_H
#define ENGINESTRUCTURE_H


namespace Engine
{
#pragma region GraphicsStructure
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

	typedef struct _MeshData
	{
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer = nullptr;
		_uint vertexCount;
		_uint vertexSize;
		_uint faceCount; //== PolygonCount == triangleCount
		DWORD FVF;
		_uint vertexNumInFace;

		_float3 minVertex;
		_float3 maxVertex;

		LPDIRECT3DINDEXBUFFER9 indexBuffer;
		D3DFORMAT indexFormat;
		_uint indexSize;
	}MESH_DATA;

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

	typedef struct _FRUSTUM
	{
		D3DXPLANE plane[6];
	}FRUSTUM;
#pragma endregion

	class CCollider;
	struct _CollisionInfo
	{
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

