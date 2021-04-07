#ifndef LAYER_H
#define LAYER_H

BEGIN(Engine)

class CGameObject;
class CScene;
class ENGINE_DLL CLayer final  
{
protected:
	explicit					CLayer			(void);
							   ~CLayer			(void);

public:
	static		CLayer*			Create			(_int layerID, CScene* pOwner);
				void			Free			(void);

				void			Awake			(void);
				void			Start			(void);
				
				_uint			FixedUpdate		(void);
				_uint			Update			(void);
				_uint			LateUpdate		(void);
				
				void			OnDestroy		(void);

				void			OnEnable		(void);
				void			OnDisable		(void);

//Interface
public:
				void			AddGameObject	(SP(CGameObject) spGameObject);
protected:
	typedef std::vector<SP(CGameObject)> _GAMEOBJECTS;
	GETTOR			(_GAMEOBJECTS,	m_vGameObjects,		{},			GameObjects)

	GETTOR_SETTOR	(CScene*,		m_pOwner,			nullptr,	Owner)
	GETTOR_SETTOR	(_int,			m_layerID,			-1,			LayerID)
};
END


#endif // !LAYER_H