#ifndef ENGINEENUM_H
#define ENGINEENUM_H

namespace Engine
{
	enum class EDisplayMdoe
	{
		FullMode,
		WinMode
	};

	enum class ERenderID
	{
		Base,
		NonAlpha,
		Alpha,
		UI,
		WireFrame,
		NumOfRenderID
	};

	enum class EColliderType
	{
		Point,
		Ray,
		Sphere,
		AABB,
		OBB,
		NumOfCT
	};

	enum class EComponentID
	{
		Undefined,
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
