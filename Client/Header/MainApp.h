#ifndef MAINAPP_H
#define MAINAPP_H

class CMainApp final
{
	SMART_DELETER_REGISTER;
protected:
	explicit						CMainApp				(void);
								   ~CMainApp				(void);


public:

	static		SHARED(CMainApp)	Create					(void);

				void				Awake					(void);
				void				Start					(void);

				_uint				FixedUpdate				(void);
				_uint				Update					(void);
				_uint				LateUpdate				(void);

				_uint				PreRender				(void);
				_uint				Render					(void);
				_uint				PostRender				(void);
				
				void				OnDestroy				(void);

				void				OnEnable				(void);
				void				OnDisable				(void);

private:
				void				InitStaticPrototype		(void);
};

#endif