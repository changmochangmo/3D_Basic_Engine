#ifndef LAYER_H
#define LAYER_H

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CLayer final  
{
	SMART_DELETER_REGISTER;

protected:
	explicit					CLayer			(void);
							   ~CLayer			(void);

public:
	static		SHARED(CLayer)	Create			(std::wstring name);

				void			Awake			(void);
				void			Start			(void);
				
				_uint			FixedUpdate		(void);
				_uint			Update			(void);
				_uint			LateUpdate		(void);
				
				void			OnDestroy		(void);

				void			OnEnable		(void);
				void			OnDisable		(void);

protected:
	typedef std::vector<SHARED(CGameObject)> _GAMEOBJECTS;
	GETTOR			(_GAMEOBJECTS,		m_vGameObjects, {},			GameObjects)

	GETTOR_SETTOR	(std::wstring,		m_name,			L"",		Name)
};
END


#endif // !LAYER_H