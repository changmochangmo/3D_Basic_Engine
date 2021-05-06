#ifndef EDITORENUM_H
#define EDITORENUM_H


enum class ESceneID
{
	Changmo,
	NumOfSceneID
};

enum class EComponentID
{
	Default = 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID
};


enum class EColliderID
{
	BasicObject			= 0,
	Player				= 1,
	Terrain				= 2,
	NumOfColliderID		= 3
};

enum class EDataID
{
	Player				= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Scene				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Decoration			= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 3 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	Player			= 0 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Map				= 1 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	Decoration		= 2 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	EmptyObject		= 3 + (_int)Engine::ELayerID::NumOfEngineLayerID,
	NumOfLayerID
};
#endif // CLIENTENUM_H