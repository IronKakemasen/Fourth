#pragma once
#include "../MaterialIndexDispatcher/MaterialIndexDispatcher.h"
#include "../MaterialRuntime/MaterialDataBatcher/MaterialDataBatcher.h"
#include "../Materials/Materials.h"

class MaterialContext::MaterialAttacher
{
public:

	MaterialAttacher
	(
		NexusFieldProof proof_,
		MaterialIndexDispatcher& materialIndexDispatcher_,
		MaterialDataBatcher& materialDataBatcher_
	);

	//Materialsの実体を作成
	std::unique_ptr<Materials> CreateMaterials();

	//対象のマテリアルID所持者に、マテリアルをアタッチする
	template<Material::Type type>
	auto& Attach(Materials& dst_)
	{
		//危険は完全に防げていないが…
		Material::CheckIsMaterialTypeAttachable<type>();

		auto& materialUniqueRef = std::get<std::unique_ptr<typename Material::MaterialTypeTraits<type>::dataType>>(dst_.params);

#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			!materialUniqueRef,
			"マテリアルアタッチの重複: " + Material::MaterialTypeTraits<type>::kName,
			"MaterialAttacher.h"
		);

#endif // _DEBUG
			
		//マテリアルIDは描画対象のMaterialArrIndexGroupBufferの添え字でもあるので、
		//今回アタッチしたマテリアルのインデックスをバッファと実データである
		//materialIndexGroupsに書き込む
		WriteMaterialIndex<type>(dst_.materialID);

		materialUniqueRef = std::make_unique<typename Material::MaterialTypeTraits<type>::dataType>();

		return *materialUniqueRef;
	}


private:

	//マテリアルIDの指す先の実データに該当マテリアルのインデックスを書き込む
	template<Material::Type type>
	void WriteMaterialIndex(UINT materialID_)
	{
		//ディスパッチャーが該当マテリアルのフリーリストからインデックスを割り当てる
		UINT materialArrIndex = materialIndexDispatcher.DispatchMaterialArrIndex<type>();

		//実データに書き込む
		materialDataBatcher.WriteInMaterialIndexGroups<type>(materialID_, materialArrIndex);
	}

	//マテリアルIDを割り当てる
	UINT DispatchMaterialID();

	//マテリアルのインデックスを割り振るため
	MaterialIndexDispatcher& materialIndexDispatcher;
	//マテリアル配列インデックス群のバッファにバッチングするためにデータを記録する
	MaterialDataBatcher& materialDataBatcher;


};

