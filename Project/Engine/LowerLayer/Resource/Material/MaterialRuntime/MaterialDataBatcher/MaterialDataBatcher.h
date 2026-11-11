#pragma once
#include "../../MaterialContext.h"


//外部
#include "../../../../../../Assets/Shared/Material.h"

class MaterialContext::MaterialDataBatcher
{
public:

	MaterialDataBatcher
	(
		NexusFieldProof proof_
	);

	//materialIndexGroupsにアタッチしたマテリアル配列のインデックスを書き込む
	template<Material::Type type>
	void WriteInMaterialIndexGroups(UINT materialID_,UINT materialArrIndex_)
	{
		//実データに書き込む
		auto* firstMemberPtr = &materialIndexGroupsCache[materialID_].standardIndex;

		*(firstMemberPtr + UINT(type)) = materialArrIndex_;
	}

	//全ての描画対象のマテリアル付与が終わった後に
	//materialIndexGroups配列のバッファにバッチングする
	void WriteMaterialIndexGroups
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
		Logger::Log("Import " + Material::MaterialTypeTraits<type>::kName + "ArrBuf: " + std::to_string(id_), "MaterialIndexDispatcher.h");
	}

	//マテリアル配列インデックス群配列バッファIDを入れる
	void ImportMaterialIDGroupArrBufferID(BufferUniqueID id_);


	
private:


	//マテリアル配列インデックス群のバッファに書き込むための実データ
	std::vector<Material::MaterialIndexGroupCPUGPU> materialIndexGroupsCache;

	//書き込む必要があるので、マテリアル配列のバッファIDは所持する
	std::array<BufferUniqueID, (UINT)Material::kNumParamExists> materialArrBufferIdArr{ kInvalid };

	//各描画対象のマテリアル配列インデックス群配列のバッファID 
	//こちらも同様、書き込む必要があるため
	BufferUniqueID materialIDGroupArrBufferID = kInvalid;

};

