#ifndef MACRO_H
#define MACRO_H

//라이브러리를 Engine에선 export하고 Client에선 Import하게 한다.
#ifdef EXPORTS_ENGINE
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif


//안전하게 포인터를 지우세요
#define SAFE_DELETE(something)														\
if((something) != nullptr)															\
	delete (something);																\
(something) = nullptr;

//MessageBox 간편화
//#ifdef _DEBUG
#define MSG_BOX(file, message) MessageBox(0, message, Engine::GetCurFileName(file).c_str(), MB_OK)
//#else
//#define MSG_BOX(caption, message) 0
//#endif



/**************************Namespace Setting************************/
#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;
/*******************************************************************/

/**************************Smart Pointer****************************/
#define SHARED(typeName) std::shared_ptr<typeName>
#define UNIQUE(typeName) std::unique_ptr<typeName>
#define WEAK(typeName) std::weak_ptr<typeName>

#define SMART_DELETER_REGISTER														\
template<typename T> friend void Engine::SmartDeleter(T* something);
/*******************************************************************/

/**************************Gettor / Settor**************************/
#define GETTOR_SETTOR(varType, varName, varInitValue, funcName)						\
protected:																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType& Get##funcName(void) { return varName; }					\
	virtual inline void Set##funcName(varType var){ varName = var; }    

#define GETTOR(varType, varName, varInitValue, funcName)							\
protected: 																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType& Get##funcName(void) { return varName; }
/*******************************************************************/




/**************************Singleton Macro**************************/
//카피 생성자를 막아용
#define NO_COPY(ClassName)															\
private:																			\
	ClassName(const ClassName&)	= delete;		

//Assign operator도 막아용
#define NO_ASSIGN_OPERATOR(ClassName)												\
private:																			\
	ClassName& operator=(const ClassName&) = delete;					
							

//Default Destructor 매크로
#define DEFAULT_DESTRUCTOR(ClassName)												\
	virtual ~ClassName(void) DEFAULT;									

//Default Constructor 매크로
#define DEFAULT_CONSTRUCTOR(ClassName)												\
	explicit ClassName(void) NONE;										

#define DEFAULT_COPY_CONSTRUCTOR(ClassName)											\
	explicit ClassName(const ClassName& other) NONE;

//싱글턴 선언 매크로
#define DECLARE_SINGLETON(ClassName)												\
		NO_COPY(ClassName)															\
		NO_ASSIGN_OPERATOR(ClassName)												\
protected:																			\
	DEFAULT_CONSTRUCTOR(ClassName)													\
	DEFAULT_DESTRUCTOR(ClassName)													\
public:																				\
	static ClassName*	GetInstance		(void);										\
	static void			DestroyInstance	(void);										\
private:																			\
	static ClassName*	m_s_pInstance;


//싱글턴 정의 매크로
#define IMPLEMENT_SINGLETON(ClassName)												\
ClassName* ClassName::m_s_pInstance = nullptr;										\
ClassName* ClassName::GetInstance(void)												\
{																					\
	if (nullptr == m_s_pInstance)													\
		m_s_pInstance = new ClassName;												\
	return m_s_pInstance;															\
}																					\
																					\
void ClassName::DestroyInstance(void)												\
{																					\
	if(m_s_pInstance != nullptr)													\
	{																				\
		m_s_pInstance->OnDestroy();													\
		delete m_s_pInstance;														\
		m_s_pInstance = nullptr;													\
	}																				\
}
/*******************************************************************/

//InputManager Macro
#define IMKEY_DOWN(key) CInputManager::GetInstance()->KeyDown(key)
#define IMKEY_PRESS(key) CInputManager::GetInstance()->KeyPress(key)
#define IMKEY_UP(key) CInputManager::GetInstance()->KeyUp(key)
#define IMMOUSE_POS() CInputManager::GetInstance()->GetMousePos()


//SceneMangager Macro
#define GET_CUR_SCENE CSceneManager::GetInstance()->GetCurScene()
#define GET_MAIN_CAM CSceneManager::GetInstance()->GetCurScene()->GetMainCamera()

//WndApp Macro
#define GET_HANDLE CWndApp::GetInstance()->GetHWnd()
#define GET_WND_WIDTH CWndApp::GetInstance()->GetWndWidth()
#define GET_WND_HEIGHT CWndApp::GetInstance()->GetWndHeight()

//GraphicsManager Macro
#define GET_DEVICE CDeviceManager::GetInstance()->GetDevice()

//FRC Macro
#ifdef EXPORTS_ENGINE
#define GET_DT CFRC::GetInstance()->GetDeltaTime()
#else
#define GET_DT Engine::CFRC::GetInstance()->GetDeltaTime()
#endif
#define TIME_MEASURE_START CFRC::GetInstance()->TimerStart()
#define GET_ELAPSED_TIME CFRC::GetInstance()->GetElapsedTime()

//DataStore Macro
#define GET_VALUE(isStatic, sectionKey, objectKey, varKey, result)					\
CDataStore::GetInstance()->GetValue(isStatic, sectionKey, objectKey, varKey, result)


//ObjectFactory Macro
#define ADD_CLONE(layerKey, objectKey, isStatic)									\
CObjectFactory::GetInstance()->AddClone(layerKey, objectKey, isStatic)

//FontManager Macro
#define ADD_TEXT(key, text, position, color) CFontManager::GetInstance()->AddText(key, text, position, color)
#define REWRITE_TEXT(key, text) CFontManager::GetInstance()->RewriteText(key, text)
#define DELETE_TEXT(key) CFontManager::GetInstance()->DeleteText(key)

//ObjectFactory Macro
//#define ADD_CLONE_2_ARGS(layerKey, objectKey)			CObjectFactory::GetInstance()->AddClone(layerKey, objectKey, false)
//#define Add_CLONE_3_ARGS(layerKey, objectKey, isStatic) CObjectFactory::GetInstance()->AddClone(layerKey, objectKey, isStatic)
//#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4
//#define PRINT_STRING_MACRO_CHOOSER(...) \
//    GET_4TH_ARG(__VA_ARGS__, PRINT_STRING_3_ARGS, \
//                PRINT_STRING_2_ARGS, PRINT_STRING_1_ARGS, )
//
//#define PRINT_STRING(...) PRINT_STRING_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#endif // ! MACRO_H	





















