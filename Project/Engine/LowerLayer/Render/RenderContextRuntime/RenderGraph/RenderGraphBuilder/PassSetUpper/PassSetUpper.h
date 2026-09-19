#pragma once
#include "../../RenderGraph.h"

class RenderContext::RenderGraph::PassSetUpper
{
	friend class RenderGraph;

	static void Setup
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

	//各パスが参照するバッファのsrvHeapIndexを配列したもののバッファを作成
	//static void CreateReferenceBufferSrvArray
	//(
	//	NexusFieldProof proof_,

	//)

	//Passのルートコンスタンツのバッファを作る
	static void CreatePassRootConstantsBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);
};

