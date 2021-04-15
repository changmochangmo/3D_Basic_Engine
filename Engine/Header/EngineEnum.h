#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Engine
{
#pragma region GraphicsEnum
	//������ ���÷��� ���
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
		Alpha			= 2,
		UI				= 3,
		WireFrame		= 4,
		NumOfRenderID	= 5
	};

	//Camera Mdoe
	enum class ECameraMode
	{
		Fixed			= 0,
		Edit			= 1,
		FPS				= 2,
		NumOfCameraMode	= 3
	};

	//MeshType
	enum class EMeshType
	{
		Static			= 0,
		Dynamic			= 1,
		NumOfMeshType	= 2
	};
#pragma endregion

#pragma region PhysicsEnum
	enum class EColliderType
	{
		Point,
		Ray,
		Sphere,
		AABB,
		OBB,
		NumOfCT
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
		Transform,
		Graphics,
		Mesh,
		Texture,
		Physics,
		UI,
		RigidBody,
		Collider,
		Camera,
		Bitmap,
		NumOfEngineComponentID
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
		Engine,
		Component,
		NumOfEngineDataID
	};
}
#endif // !ENGINEENUM_H
