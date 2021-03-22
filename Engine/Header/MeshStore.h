#ifndef MESHSTORE_H
#define MESHSTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class ENGINE_DLL CMeshStore final : public CResourceStore
{
	DECLARE_SINGLETON(CMeshStore)
public:
					void				Awake				(void) override;
					void				Start				(void) override;
					void				OnDestroy			(void) override;

					void				ClearCurResource	(void) override;

					SHARED(_MeshData)	GetMeshData			(std::wstring meshKey);
					void				InitMeshForScene	(std::wstring curScene);
private:
					void				InitResource		(std::wstring sourcePath) override;
					void				ParsingMesh			(std::wstring filePath, 
															 std::wstring fileName);

private:
	typedef std::unordered_map<std::wstring, SHARED(_MeshData)>	_MeshDataMap;
					_MeshDataMap		m_mCurSceneMeshData;
					_MeshDataMap		m_mStaticMeshData;
};
END
#endif // !MESHSTORE_H
