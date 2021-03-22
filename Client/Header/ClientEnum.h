#ifndef CLIENTENUM_H
#define CLIENTENUM_H


enum class ESceneID
{
	Static,
	Logo, 
	Loading, 
	MainMenu,
	Stage1,
	Stage2,
	Stage3,
	NumOfSceneID
};

enum class EComponentID
{
	Player = 0 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	WhiteBlock = 1 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	BlueBlock = 2 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	RedBlock = 3 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	YellowBlock = 4 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	GreenBlock = 5 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	GenerateBlock = 6 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	RhythmBlock   = 7 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	NumOfComponentID = 8 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Door = 9 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Elevator = 10 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Stairs = 11 + (_uint)Engine::EComponentID::NumOfEngineComponentID,
	Enemy = 12 + (_uint)Engine::EComponentID::NumOfEngineComponentID
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
#endif // CLIENTENUM_H