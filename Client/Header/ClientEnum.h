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
	None				= 0,
	Player				= 1,
	NormalBlock			= 2,
	EventBlock			= 3,
	Ball				= 4,
	WayPoint		    = 5,
	CheckingPlayer		= 6,
	NumOfColliderID		= 7
};

enum class EDataID
{
	BasicObject			= 0 + (_uint)Engine::EDataID::NumOfEngineDataID,
	Player				= 1 + (_uint)Engine::EDataID::NumOfEngineDataID,
	NumOfDataID			= 2 + (_uint)Engine::EDataID::NumOfEngineDataID
};


enum class ELayerID
{
	BasicObject,
	Player,
	NumOfLayerID
};
#endif // CLIENTENUM_H