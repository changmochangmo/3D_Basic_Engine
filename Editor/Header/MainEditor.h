#pragma once
class CMainEditor final
{
	SMART_DELETER_REGISTER;
protected:
	explicit					CMainEditor				(void);
							   ~CMainEditor				(void);


public:

	static		SP(CMainEditor)	Create					(void);

				void			Awake					(void);
				void			Start					(void);

				void			FixedUpdate				(void);
				void			Update					(void);
				void			LateUpdate				(void);

				void			PreRender				(void);
				void			Render					(void);
				void			PostRender				(void);

				void			OnDestroy				(void);

				void			OnEnable				(void);
				void			OnDisable				(void);

private:
				void			InitStaticPrototype		(void);

};

