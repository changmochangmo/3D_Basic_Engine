#ifndef LAYER_H
#define LAYER_H

BEGIN(Engine)

class CObject;
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
				
				void			FixedUpdate		(void);
				void			Update			(void);
				void			LateUpdate		(void);
				
				void			OnDestroy		(void);

				void			OnEnable		(void);
				void			OnDisable		(void);

//Interface
public:
				void			AddGameObject	(SP(CObject) spGameObject);
protected:
	typedef std::vector<SP(CObject)> _GAMEOBJECTS;
	GETTOR			(_GAMEOBJECTS,	m_vGameObjects,		{},			GameObjects)

	GETTOR_SETTOR	(CScene*,		m_pOwner,			nullptr,		Owner)
	GETTOR_SETTOR	(_int,			m_layerID,			UNDEFINED,	LayerID)
	GETTOR_SETTOR	(_bool,			m_enable,			true,			Enable)
};
END


#endif // !LAYER_H