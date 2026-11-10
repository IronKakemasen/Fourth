#pragma once
#include "../MaterialIndexDispatcher/MaterialIndexDispatcher.h"



//外部
#include "../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"

class MaterialContext::MaterialAttacher
{
public:

	MaterialAttacher
	(
		NexusFieldProof proof_,
		MaterialIndexDispatcher& materialIndexDispatcher_,
		BufferContextDiplomat& nufferContextDiplomat_
	);

	//マテリアルIDを割り当てる
	UINT DispatchMaterialID();

	//対象のマテリアルID所持者に、マテリアルをアタッチする
	template<Material::Type type,typename MaterialClass>
	std::unique_ptr<MaterialClass> Attach(UINT materialID_)
	{


		return std::make_unique<Material::MaterialTypeTraits<type>::dataType>();
	}

private:

	MaterialIndexDispatcher& materialIndexDispatcher;

	//呼び出し回数が多いのと、いろんな場所でマテリアルをアタッチするので所持します
	BufferContext::BufferDispatcher* bufferDispatcher;
};

