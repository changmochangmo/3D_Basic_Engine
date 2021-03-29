#ifndef SCENE_H
#define SCENE_H

BEGIN(Engine)
class CLayer;
class CGameObject;
class ENGINE_DLL CScene abstract  
{
protected:
	explicit							CScene				(void);
	virtual							   ~CScene				(void);

public:
	virtual		void					Free				(void) PURE;
	virtual		void					Awake				(_int numOfLayers) PURE;
	virtual		void					Start				(void) PURE;
																   
	virtual		_uint					FixedUpdate			(void) PURE;
	virtual		_uint					Update				(void) PURE;
	virtual		_uint					LateUpdate			(void) PURE;	
																   
	virtual		void					OnDestroy			(void) PURE;
																   
	virtual		void					OnEnable			(void) PURE;
	virtual		void					OnDisable			(void) PURE;
				
				SHARED(CGameObject)		FindObjectByName	(std::wstring name);
				SHARED(CGameObject)		FindObjectWithKey	(std::wstring objectKey);
				_uint					FindObjectsWithKey	(std::wstring objectKey, 
															 std::vector<SHARED(CGameObject)>& gameObjects);


protected:												   
				void					InitLayers			(_int numOfLayers);
	virtual		void					InitPrototypes		(void) PURE;

	
protected:
	typedef std::vector<CLayer*> _LAYERS;
	GETTOR			(_LAYERS,					m_vLayers,			{},				Layers)

	GETTOR			(_int,						m_sceneID,			-1,				SceneID)

	GETTOR			(_bool,						m_isAwaked,			false,			IsAwaked)
	GETTOR			(_bool,						m_isStarted,		false,			IsStarted)
	GETTOR_SETTOR	(_bool,						m_enable,			true,			Enable)
	GETTOR_SETTOR	(_bool,						m_SceneEvent,		false,			SceneEvent)

};
END

#endif