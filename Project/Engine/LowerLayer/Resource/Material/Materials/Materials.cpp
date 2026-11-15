#include "PreCompileHeader.h"
#include "Materials.h"

Materials::Materials(InstantiateLicence licence_, UINT materialID_)
:materialID(materialID_)
{
	//全パラメーターのマテリアルのダーティカウントをダブルバッファ分にしておく(オン)にする
	for (UINT i = 0;i < Material::kNumParamExists;++i)
	{
		dirtyArr[i] = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;
	}
		

}