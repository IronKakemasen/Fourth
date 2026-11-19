#include "PreCompileHeader.h"
#include "MaterialDataBatcher.h"
#include "../MaterialBatchFormat.h"
#include "../../Materials/Materials.h"

//外部
#include "../../../../Buffer/BufferContextDiplomat/BufferContextDiplomat.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLender.h"
#include "../../../../Buffer/BufferContextDiplomat/BufferToolLender/BufferToolLenderLicence.h"
#include "../../../../Buffer/BufferRuntime/BufferDispatcher/BufferDispatcher.h"
#include "../../../../Buffer/BufferDefinition/GPUBuffer/UploadStructuredBuffer/UploadStructuredBuffer.h"

namespace
{
	auto const fileName = "MaterialDataBatcher.cpp";
}


MaterialContext::MaterialDataBatcher::MaterialDataBatcher
(
	NexusFieldProof proof_
) 
{
	materialIndexGroups.resize((UINT)ProjectConfig::Render::BufferSize::kMaterialIndexGroupArr);
}

void MaterialContext::MaterialDataBatcher::WriteInAllMaterialData
(
	AgentKey key_,
	std::vector<MaterialBatchFormat> const& src_,
	UINT frameIndex_,
	BufferContextDiplomat& bufferContextDiplomat_
) 
{
	//bufferDispatcherを借りる
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;
	auto& bufferDispatcher = *bufferContextDiplomat_.Access<BufferContext::ToolLender>()->
		Lend<BufferContext::BufferDispatcher>(licence);

	for (auto& dst : src_)
	{
#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			dst.materialsPtr,
			"materialsPtrがぬる(エンジンのせい)",
			fileName
		);

#endif // _DEBUG

		//該当タイプのマテリアルが存在しかつダーティならバッチングをする
		Material::Type callCheck = Material::Type::kStandard;

		WriteInMaterialData<Material::Type::kStandard>
		(
			dst,
			callCheck,
			frameIndex_,
			bufferDispatcher
		);

		WriteInMaterialData<Material::Type::kGridLine>
		(
			dst,
			callCheck,
			frameIndex_,
			bufferDispatcher
		);


#ifdef _DEBUG

		ErrorMessageOutput::Assert::DetectError
		(
			(UINT)callCheck == Material::kNumParamExists,
			"書き込んでいないマテリアルデータの種類がある(エンジンのせい)",
			fileName
		);

#endif // _DEBUG

	}
}

void MaterialContext::MaterialDataBatcher::ImportMaterialIndexGroupArrBufferID(BufferUniqueID id_)
{
	materialIndexGroupArrBufferID = id_;
	Logger::Log("Import MaterialIndexGroupArrBufferID: " + std::to_string(id_), fileName);
}


void MaterialContext::MaterialDataBatcher::WriteInMaterialIndexGroupsArrBuffer
(
	NexusFieldProof proof_, 
	AgentKey key_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//bufferDispatcherを借りる
	BufferContext::ToolLender::LicenceType<BufferContext::BufferDispatcher> licence;
	auto& bufferDispatcher = *bufferContextDiplomat_.Access<BufferContext::ToolLender>()->
	Lend<BufferContext::BufferDispatcher>(licence);

	//バッチ先バッファ
	auto* dstWriteInBuffer = static_cast<UploadStructuredBuffer*>(bufferDispatcher.Dispatch(materialIndexGroupArrBufferID));
	
	//両面にマテリアル配列インデックス群配列のデータを書き込む
	dstWriteInBuffer->WriteRangeInBoth< Material::MaterialIndexGroupCPUGPU >
	(
		{
			materialIndexGroups,
			materialIndexGroups
		}
	);
	Logger::Log("Write materialIndexGroups", fileName);
}

template<Material::Type type>
void MaterialContext::MaterialDataBatcher::WriteInMaterialData
(
	MaterialBatchFormat const& src_,
	Material::Type& callCheck_,
	UINT frameIndex_,
	BufferContext::BufferDispatcher& bufferDispatcher_
)
{
	Material::CheckIsMaterialTypeAttachable<type>();

	auto* material = src_.materialsPtr->GetMaterialPtrIfDirty<type>();
	callCheck_ = Material::Type((UINT)callCheck_ + 1);

	if (material)
	{
		//マテリアルIDからバッチング対象のマテリアル配列のインデックスを引き、入力する
		//マテリアルインデックス群の先頭メンバ変数(standardIndex)のアドレス
		auto* standardIndexPtr = reinterpret_cast<UINT*>(&materialIndexGroups[src_.materialID].standardIndex);

		UINT dstMaterialArrIndex = *(standardIndexPtr + (UINT)type );

		//所持していたマテリアル配列のバッファIDからバッファを取得
		auto* bufferBeWritten = bufferDispatcher_.Dispatch(materialArrBufferIdArr[(UINT)type]);
		auto* writeable = static_cast<UploadStructuredBuffer*>(bufferBeWritten);
		
		//実データを書き込む
		writeable->WriteElement<typename Material::MaterialTypeTraits<type>::dataType>
			(frameIndex_, *material, dstMaterialArrIndex);

		//バッファの片面に書き込んだのでダーティカウントを1へらす
		src_.materialsPtr->DecrementDirtyCnt<type>();
	}

}

template
void MaterialContext::MaterialDataBatcher::WriteInMaterialData<Material::Type::kStandard>
(
	MaterialBatchFormat const& src_,
	Material::Type& callCheck_,
	UINT frameIndex_,
	BufferContext::BufferDispatcher& bufferDispatcher_
);

template
void MaterialContext::MaterialDataBatcher::WriteInMaterialData<Material::Type::kGridLine>
(
	MaterialBatchFormat const& src_,
	Material::Type& callCheck_,
	UINT frameIndex_,
	BufferContext::BufferDispatcher& bufferDispatcher_
);


