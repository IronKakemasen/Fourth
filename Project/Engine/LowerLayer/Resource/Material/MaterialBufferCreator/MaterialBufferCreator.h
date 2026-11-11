#pragma once
#include "../MaterialContext.h"


//外部
#include "../../../../../Assets/Shared/Material.h"
#include "../../../../../Assets/Shared/ConstantBuffers.h"

class GPUBufferBehavior;

class MaterialContext::MaterialBufferCreator
{
public:

	MaterialBufferCreator
	(
		NexusFieldProof proof_,
		MaterialDataBatcher& materialDataBatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

private:


	//マテリアル配列バッファのキャッシュ
	std::vector<GPUBufferBehavior*> materialArrBufferCache;

	//デバッグ用。ちょいと雑だが、呼び出しシーケンスチェックのため
	Material::Type materialSequence = Material::Type(0);

	//マテリアル配列のバッファをサイズ分作成
	template<Material::Type type>
	void CreateMaterialArrBuffer
	(
		MaterialDataBatcher& materialDataBatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	//それらのsrvHeapIndex群のバッファも作成する
	GPUBufferBehavior* CreateMaterialArrSrvIndexGroupBuffer
	(
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//MaterialArrバッファの表裏２面分のsrvIndexを書き込む
	void WriteMaterialArrSrvIndices(GPUBufferBehavior* materialArrBufferSrvIndexGroupBuffer_);

	//Material配列インデックス群配列のバッファを作成する
	GPUBufferBehavior* CreateMaterialIndexGroupArrBuffer
	(
		MaterialDataBatcher& materialDataBatcher_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//バッファのSrvのグローバル定数バッファを作成する
	template<ConstantBuffers::ConstantBufferBindSlots dstSlot>
	void CreateItsSrvCBuffer
	(
		GPUBufferBehavior* uploadStructuredBuffer_,
		std::string const& cBUfferName_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
};

