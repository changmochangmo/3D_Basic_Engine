#include "EngineStdafx.h"
#include "ShaderManager.h"
#include "TextureShader.h"
#include "DebugShader.h"

USING(Engine)
IMPLEMENT_SINGLETON(CShaderManager)
void CShaderManager::Awake()
{
	__super::Awake();
}


void CShaderManager::Start()
{
	AddShader(CTextureShader::Create());
	AddShader(CDebugShader::Create());
}

void CShaderManager::OnDestroy()
{
	for (auto& shader : m_mShaders)
		delete shader.second;

	m_mShaders.clear();
}

void CShaderManager::OnEnable()
{
}

void CShaderManager::OnDisable()
{
}

HRESULT CShaderManager::AddShader(CShader* pShader)
{
	_int shaderType = pShader->GetShaderType();
	if (m_mShaders.find(shaderType) == m_mShaders.end())
		m_mShaders[shaderType] = pShader;
	else
	{
		MSG_BOX(__FILE__, L"Shader already exist in AddShader");
		ABORT;
	}

	return S_OK;
}

CShader* CShaderManager::GetShader(_int shaderKey)
{
	return m_mShaders[shaderKey];
}
