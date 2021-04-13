#ifndef MAINAPP_H
#define MAINAPP_H

class CMainApp final
{
	SMART_DELETER_REGISTER;
protected:
	explicit						CMainApp				(void);
								   ~CMainApp				(void);


public:

	static		SP(CMainApp)		Create					(void);

				void				Awake					(void);
				void				Start					(void);

				void				FixedUpdate				(void);
				void				Update					(void);
				void				LateUpdate				(void);

				void				PreRender				(void);
				void				Render					(void);
				void				PostRender				(void);
				
				void				OnDestroy				(void);

				void				OnEnable				(void);
				void				OnDisable				(void);

private:
				void				InitStaticPrototype		(void);
};

#endif