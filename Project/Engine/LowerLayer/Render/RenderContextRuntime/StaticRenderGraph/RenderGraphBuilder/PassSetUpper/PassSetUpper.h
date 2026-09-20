#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::PassSetUpper
{
	friend class StaticRenderGraph;

	static [[nodiscard]] BufferUniqueID Setup
	(
		NexusFieldProof proof_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//以下ヘルパー
private:

	//全パスの所持するPassDesc -> PassInfoに移し替える
	static std::vector<BufferUniqueID> CreateAllPassInfo
	(
		NexusFieldProof proof_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_
	);

	///各パスが参照するバッファのsrvHeapIndexを配列したもののバッファ、そしてそのsrvHeapIndexの定数バッファを作成
	//ReferenceBufferSrvArrayバッファのバッファインデックスを返す
	static SRVHeapIndex CreateReferenceBufferSrvArray
	(
		NexusFieldProof proof_,
		std::vector<BufferUniqueID> const& data_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//Passのルートコンスタンツのバッファを作る
	static void CreatePassRootConstantsBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
};

