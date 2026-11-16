#pragma once
#include "../../MaterialContext.h"


//外部
#include "../../../../../../Assets/Shared/Material.h"

//パフォーマンスのため
#include "../../../../Buffer/BufferContext.h"


struct MaterialBatchFormat;

class MaterialContext::MaterialDataBatcher
{
public:

	MaterialDataBatcher
	(
		NexusFieldProof proof_
	);

	//マテリアルデータをマテリアル配列にバッチングする
	//代理人がシーンのBatchingPlaceで呼ぶ
	void WriteInAllMaterialData
	(
		AgentKey key_,
		std::vector<MaterialBatchFormat>& src_,
		UINT frameIndex_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//materialIndexGroupsにアタッチしたマテリアル配列のインデックスを書き込む
	template<Material::Type type>
	void WriteInMaterialIndexGroups(UINT materialID_,UINT materialArrIndex_)
	{
		//実データに書き込む
		auto* firstMemberPtr = &materialIndexGroups[materialID_].standardIndex;

		*(firstMemberPtr + UINT(type)) = materialArrIndex_;
	}

	//全ての描画対象のマテリアル付与が終わった後に
	//materialIndexGroups配列のバッファにバッチングする
	void WriteInMaterialIndexGroupsArrBuffer
	(
		NexusFieldProof proof_,
		AgentKey key_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//マテリアル配列バッファIDを入れる
	template<Material::Type type>
	void ImportMaterialArrBufferIndex(BufferUniqueID id_)
	{
		materialArrBufferIdArr[(UINT)type] = id_;
		Logger::Log("Import " + Material::MaterialTypeTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "MaterialDataBatcher.h");
	}

	//マテリアル配列インデックス群配列バッファIDを入れる
	void ImportMaterialIndexGroupArrBufferID(BufferUniqueID id_);


	
private:

	//マテリアル配列バッファに実データを書き込む
	template<Material::Type type>
	void WriteInMaterialData
	(
		MaterialBatchFormat& src_,
		Material::Type& callCheck_,
		UINT frameIndex_,
		BufferContext::BufferDispatcher& bufferDispatcher_
	);

	//マテリアル配列インデックス群のバッファに書き込むための実データ
	std::vector<Material::MaterialIndexGroupCPUGPU> materialIndexGroups;

	//書き込む必要があるので、マテリアル配列のバッファIDは所持する
	std::array<BufferUniqueID, (UINT)Material::kNumParamExists> materialArrBufferIdArr;

	//各描画対象のマテリアル配列インデックス群配列のバッファID 
	//こちらも同様、書き込む必要があるため
	BufferUniqueID materialIndexGroupArrBufferID = kInvalid;

};
