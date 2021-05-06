#ifndef GAMEDATA_H
#define GAMEDATA_H

class CPlayer;

class CGameData
{
	DECLARE_SINGLETON(CGameData)
public:
					void			Awake			(void);
					void			Start			(void);

					void			OnDestroy		(void);

					void			OnEnable		(void);
					void			OnDisable		(void);


private:
	GETTOR_SETTOR	(SP(CPlayer),	m_pPlayer,		nullptr,	Player)

};

#endif