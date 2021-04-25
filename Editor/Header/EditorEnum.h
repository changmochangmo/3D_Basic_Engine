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
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Terrain				= 2 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Decoration			= 3 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 4 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	BasicObject		= 0,
	Player			= 1,
	Terrain			= 2,
	Decoration		= 3,
	NumOfLayerID
};
#endif // CLIENTENUM_H