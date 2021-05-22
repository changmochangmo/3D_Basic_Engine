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

private:
	static		_uint					m_s_uniqueID;
};

#endif // !UIOBJECT_H__
