#ifndef MESHSTORE_H
#define MESHSTORE_H

#include "ResourceStore.h"

BEGIN(Engine)
class CMesh;
class ENGINE_DLL CMeshStore final : public CResourceStore
{
	DECLARE_SINGLETON(CMeshStore)
public:
			void				Awake				(void) override;
			void				Start				(void) override;
			void				OnDestroy			(void) override;

			void				ClearCurResource	(void) override;

			CMesh*				GetMeshData			(std::wstring meshKey);
			void				InitMeshForScene	(std::wstring curScene);
private:
			void				InitResource		(std::wstring sourcePath) override;
			void				ParsingMesh			(std::wstring filePath, 
													 std::wstring fileName);

private:
	typedef std::unordered_map<std::wstring, CMesh*> _MeshMap;
					_MeshMap		m_mCurSceneMeshData;
					_MeshMap		m_mStaticMeshData;
};
END
#endif // !MESHSTORE_H
