#pragma once
#include "../MaterialIndexDispatcher/MaterialIndexDispatcher.h"
#include "../MaterialRuntime/MaterialDataBatcher/MaterialDataBatcher.h"


class MaterialContext::MaterialAttacher
{
public:

	MaterialAttacher
	(
		NexusFieldProof proof_,
		MaterialIndexDispatcher& materialIndexDispatcher_,
		MaterialDataBatcher& materialDataBatcher_
	);

	//マテリアルIDを割り当てる
	UINT DispatchMaterialID();

	//対象のマテリアルID所持者に、マテリアルをアタッチする
	template<Material::Type type>
	auto Attach(UINT materialID_)
	{
		//危険は完全に防げていないが…
		Material::CheckIsMaterialTypeAttachable<type>();

		//マテリアルIDは描画対象のMaterialArrIndexGroupBufferの添え字でもあるので、
		//今回アタッチしたマテリアルのインデックスをバッファと実データである
		//materialIndexGroupsに書き込む
		WriteMaterialIndex<type>(materialID_);

		return std::make_unique<Material::MaterialTypeTraits<type>::dataType>();
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


	//マテリアルのインデックスを割り振るため
	MaterialIndexDispatcher& materialIndexDispatcher;
	//マテリアル配列インデックス群のバッファにバッチングするためにデータを記録する
	MaterialDataBatcher& materialDataBatcher;


};

