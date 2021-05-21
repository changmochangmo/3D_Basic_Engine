#ifndef USERINTERFACE_H
#define USERINTERFACE_H 

#include "Object.h"
class CUserInterface : public Engine::CObject
{
	SMART_DELETER_REGISTER
protected:
	explicit							CUserInterface		(void);
									   ~CUserInterface		(void);

public:
	static		SP(CUserInterface)		Create				(std::wstring objectKey);

	virtual		SP(Engine::CObject)		MakeClone			(void) override;
	virtual		void					Awake				(void) override;
	virtual		void					Start				(void) override;

	virtual		void					FixedUpdate			(void) override;
	virtual		void					Update				(void) override;
	virtual		void					LateUpdate			(void) override;

	virtual		void					OnDestroy			(void) override;

	virtual		void					OnEnable			(void) override;
	virtual		void					OnDisable			(void) override;
	virtual		void					SetBasicName		(void) override;
protected:
	GETTOR			(SP(Engine::CGraphicsC),	m_spGraphics,	nullptr,	Graphics)
	GETTOR			(SP(Engine::CBitmapC),		m_spBitmap,		nullptr,	Bitmap)
	GETTOR			(SP(Engine::CTextureC),		m_spTexture,	nullptr,	Texture)

	GETTOR_SETTOR	(_float,			m_positionX,	0.f,	PositionX)
	GETTOR_SETTOR	(_float,			m_positionY,	0.f,	PositionY)
	GETTOR_SETTOR	(_float,			m_ScaleX,		0.f,	ScaleX)
	GETTOR_SETTOR	(_float,			m_ScaleY,		0.f,	ScaleY)

private:
	static		_uint					m_s_uniqueID;
};

#endif // !UIOBJECT_H__
