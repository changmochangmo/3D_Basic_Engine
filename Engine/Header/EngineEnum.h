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
		Alpha			= 2,
		UI				= 3,
		WireFrame		= 4,
		NumOfRenderID	
	};

	//Camera Mdoe
	enum class ECameraMode
	{
		Fixed,
		Edit,
		FPS,
		NumOfCameraMode
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
