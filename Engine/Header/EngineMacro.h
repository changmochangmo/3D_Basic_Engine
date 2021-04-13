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
#ifdef _DEBUG_MSG
#define MSG_BOX(file, message) MessageBox(0, message, Engine::GetCurFileName(file).c_str(), MB_OK)
#define ABORT abort()
#else
#define MSG_BOX(caption, message) 0
#define ABORT 0
#endif




//namespace setting
#define BEGIN(Name) namespace Name {
#define END }
#define USING(Name) using namespace Name;


//SmartPointers
#define SP(typeName) std::shared_ptr<typeName>
#define UNIQUE(typeName) std::unique_ptr<typeName>
#define WEAK(typeName) std::weak_ptr<typeName>

#define SMART_DELETER_REGISTER														\
template<typename T> friend void Engine::SmartDeleter(T* something);


//Gettor, Settor
#define GETTOR_SETTOR(varType, varName, varInitValue, funcName)						\
protected:																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType const& Get##funcName(void) const { return varName; }			\
	virtual inline void Set##funcName(varType var){ varName = var; }    

#define GETTOR(varType, varName, varInitValue, funcName)							\
protected: 																			\
	varType varName = varInitValue; 												\
public: 																			\
	virtual inline varType const& Get##funcName(void) const { return varName; }





//Singleton Macro
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


//InputManager Macro
#define IMKEY_DOWN(key) CInputManager::GetInstance()->KeyDown(key)
#define IMKEY_PRESS(key) CInputManager::GetInstance()->KeyPress(key)
#define IMKEY_UP(key) CInputManager::GetInstance()->KeyUp(key)
#define IMMOUSE_POS() CInputManager::GetInstance()->GetMousePos()


//SceneMangager Macro
#define GET_CUR_SCENE CSceneManager::GetInstance()->GetCurScene()

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
#define GET_VALUE(isStatic, dataID, objectKey, varKey, result)						\
CDataStore::GetInstance()->GetValue(isStatic, dataID, objectKey, varKey, result)


//ObjectFactory Macro
#define ADD_CLONE1(objectKey)														\
CObjectFactory::GetInstance()->AddClone(objectKey)

#define ADD_CLONE2(objectKey, isStatic)												\
CObjectFactory::GetInstance()->AddClone(objectKey, isStatic)

#define ADD_CLONE3(objectKey, isStatic, name)										\
CObjectFactory::GetInstance()->AddClone(objectKey, isStatic, name)

#define GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) arg4

#define ADD_CLONE_MACRO_CHOOSER(...)												\
GET_4TH_ARG(__VA_ARGS__, ADD_CLONE3, ADD_CLONE2, ADD_CLONE1, )

#define ADD_CLONE(...) ADD_CLONE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)



#define ADD_PROTOTYPE(spPrototype)													\
CObjectFactory::GetInstance()->AddPrototype(spPrototype)

//FontManager Macro
#define ADD_TEXT(key, text, position, color)										\
CTextManager::GetInstance()->AddText(key, text, position, color)

#define REWRITE_TEXT(key, text) CTextManager::GetInstance()->RewriteText(key, text)
#define DELETE_TEXT(key) CTextManager::GetInstance()->DeleteText(key)

//CameraManager Macro
#define GET_MAIN_CAM CCameraManager::GetInstance()->GetMainCamera()

//MathHelper Macro
#define GET_MATH CMath::CMathHelper::GetInstance()
#endif // ! MACRO_H	





   















