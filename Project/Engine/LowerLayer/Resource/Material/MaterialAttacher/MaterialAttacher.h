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
		BufferContextDiplomat& bufferContextDiplomat_
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
	//materialIndexGroups配列のバッファに一括バッチングする

private:

	//マテリアルIDの指す先の実データに該当マテリアルのインデックスを書き込む
	template<Material::Type type>
	void WriteMaterialIndex(UINT materialID_)
	{
		//ディスパッチャーが該当マテリアルのフリーリストからインデックスを割り当てる
		UINT materialArrIndex = materialIndexDispatcher.DispatchMaterialArrIndex<type>();

		//実データに書き込む
		auto* firstMemberPtr = &materialIndexGroups[materialID_].standardIndex;



		*(firstMemberPtr + UINT(type)) = materialArrIndex;

	}

	//マテリアル配列インデックス群のバッファに書き込むための実データ
	std::vector<Material::MaterialIndexGroupCPUGPU> materialIndexGroups;

	MaterialIndexDispatcher& materialIndexDispatcher;

	//呼び出し回数が多いのと、いろんな場所でマテリアルをアタッチするので所持します
	BufferContext::BufferDispatcher* bufferDispatcher;
};

