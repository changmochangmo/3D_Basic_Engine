#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Engine
{
#pragma region GraphicsEnum
	//윈도우 디스플레이 모드
	enum class EDisplayMdoe
	{
		FullMode,
		WinMode
	};

	//GraphicsComponent RenderID
	enum class ERenderID
	{
		Base			= 0,
		NonAlpha		= 1,
		WireFrame		= 2,
		AlphaTest		= 3,
		AlphaBlend		= 4,
		UI				= 5,
		NumOfRenderID	= 6
	};

	//Camera Mdoe
	enum class ECameraMode
	{
		Fixed			= 0,
		Edit			= 1,
		FPS				= 2,
		Follower		= 3,
		NumOfCameraMode	= 4
	};

	//MeshType
	enum class EMeshType
	{
		Static			= 0,
		Dynamic			= 1,
		NumOfMeshType	= 2
	};

	enum class EDebugBV
	{
		Sphere			= 0,
		AABB			= 1,
		NumOfDebugBV	= 2
	};

	enum class EDebugMT
	{
		BV				= 0,
		ArrowR			= 1,
		ArrowU			= 2,
		ArrowF			= 3,
		Mesh			= 4,
		NumOfDebugMT	= 5
	};

	enum class EShaderType
	{
		Debug			= 0,
		Texture			= 1,
		NumOfShdaerType	= 2
	};
#pragma endregion

#pragma region PhysicsEnum
	enum class EColliderType
	{
		Point		= 0,
		Ray			= 1,
		Sphere		= 2,
		AABB		= 3,
		OBB			= 4,
		NumOfCT
	};

	enum class ERayType
	{
		LIMITED,
		POSITIVE_INF,
		NEGATIVE_INF,
		ALL_INF
	};

	enum class EConstraint
	{
		None				= 1 << 0,
		FreezePositionX		= 1 << 1,
		FreezePositionY		= 1 << 2,
		FreezePositionZ		= 1 << 3,
		FreezeRotationX		= 1 << 4,
		FreezeRotationY		= 1 << 5,
		FreezeRotationZ		= 1 << 6,
		FreezePosition		= 1 << 7,
		FreezeRotation		= 1 << 8,
		FreezeAll			= 1 << 9
	};
#pragma endregion

	enum class EComponentID
	{
		Transform				= 0,
		Mesh					= 1,
		Texture					= 2,
		Graphics				= 3,
		RigidBody				= 4,
		Collision				= 5,
		Camera					= 6,
		Debug					= 7,
		NumOfEngineComponentID	= 8
	};

	enum class EChannelID
	{
		BGM,
		PLAYER,
		DOOR,
		BOX,
		HAT,
		UI,
		LAND,
		NumOfChannelID
	};

	enum class EDataID
	{
		Engine				= 0,
		Component			= 1,
		DebugObject			= 2,
		Grid				= 3,
		NumOfEngineDataID
	};

	enum class ELayerID
	{
		Camera				= 0,
		BV					= 1,
		DebugArrow			= 2,
		DebugCollision		= 3,
		Grid				= 4,
		NumOfEngineLayerID	
	};
}
#endif // !ENGINEENUM_H
