#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::PassSetUpper
{
	friend class StaticRenderGraph;


	static [[nodiscard]] BuildOutput::PassSetUpper Setup
	(
		NexusFieldProof proof_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//以下ヘルパー
private:

	//パスの参照バッファ、書き込みシェアバッファをPassDescから詰めていく
	//そして、PassDescをもとにRuntimePassInfoを作成する
	static void CreateAllPassInfo
	(
		NexusFieldProof proof_,
		BuildOutput::PassSetUpper& output_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//各パスの参照バッファをバッファ名から埋めていき、
	//Outputの全パスの参照バッファ格納先にIDを登録する
	struct AddRefBufferFuncReturn
	{
		//そのパスがバッファ配列の何番目を参照するか、であるPassConstantsCPUGPUのoffset
		UINT refOffset;
		//そのPassの参照先バッファID格納用
		std::vector<BufferUniqueID> refColorBuffersID;
		std::vector<BufferUniqueID> refDepthStencilBuffersID;
	};
	static AddRefBufferFuncReturn AddRefBuffer
	(
		NexusFieldProof proof_,
		PassBehavior& pass_,
		BuildOutput::PassSetUpper& output_,
		RenderPassCreator& renderPassCreator_,
		[[maybe_unused]] std::vector<std::string >& debug_allRefBufferNames_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//RuntimePassInfoを作成する
	static void CreateRuntimePassInfo
	(
		NexusFieldProof proof_,
		PassBehavior& pass_,
		AddRefBufferFuncReturn addRefBufferFuncReturn_
	);

	//各パスの書き込み共有バッファをバッファ名から埋めていく
	static void AddWriteSharingBuffer
	(
		NexusFieldProof proof_,
		PassBehavior& pass_,
		RenderPassCreator& renderPassCreator_
	);

	//スワップチェーンのフロントバッファが参照する最終カラーバッファを詰める
	static void SetFinalColorBuffer
	(
		NexusFieldProof proof_,
		BuildOutput::PassSetUpper& output_,
		RenderPassCreator& renderPassCreator_
	);

	///各パスが参照するバッファのsrvHeapIndexを配列したもののバッファ、そしてそのsrvHeapIndexの定数バッファを作成
	//ReferenceBufferSrvArrayバッファのバッファインデックスを返す
	static void CreateReferenceBufferSrvArray
	(
		NexusFieldProof proof_,
		BuildOutput::PassSetUpper& output_,
		BufferContextDiplomat& bufferContextDiplomat_
	);


	struct DataKey
	{
		static inline auto const kRenderGraphSettings = "RenderGraphSettings";
		static inline auto const kFinalColorBuffer	  = "FinalColorBuffer";
	};
};

