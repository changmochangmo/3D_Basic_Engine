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
	Boss				= 3,
	Player				= 4,
	NumOfColliderID		= 5
};

enum class EDataID
{
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene				= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Camera				= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Boss				= 4 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 5 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Enemy			= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Camera			= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID	= 4 + (_int)Engine::ELayerID::NumOfEngineLayerID
};
#endif // CLIENTENUM_H