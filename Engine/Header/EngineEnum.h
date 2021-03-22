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
		Last,
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

	enum CHANNELID
	{
		BGM,
		PLAYER,
		DOOR,
		BOX,
		HAT,
		UI,
		MAXCHANNEL,
		LAND
	};
}
#endif // !ENGINEENUM_H
