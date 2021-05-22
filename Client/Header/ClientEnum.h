#ifndef CLIENTENUM_H
#define CLIENTENUM_H


enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default				= 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class EColliderID
{
	PlayerRay			= 0,
	Map					= 1,
	CameraRay			= 2,
	Enemy				= 3,
	Player				= 4,
	NumOfColliderID		= 5
};

enum class EDataID
{
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene				= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Camera				= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Enemy				= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	UI					= 5 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 6 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy			= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Camera			= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	UI				= 4 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 5 + (_int)Engine::ELayerID::NumOfEngineLayerID
};

enum class ELoadingID
{
	StaticResource,
	BossSceneResource
};
#endif // CLIENTENUM_H