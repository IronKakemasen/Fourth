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
	//PassDescをもとにRuntimePassInfoを作成する（名前的に違和感あるが…）
	static void AddRefBuffer
	(
		NexusFieldProof proof_,
		PassBehavior& pass_,
		BuildOutput::PassSetUpper& output_,
		RenderPassCreator& renderPassCreator_,
		std::vector<std::string >& debug_allRefBufferNames_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//各パスの書き込み共有バッファをバッファ名から埋めていく
	static void AddWriteShareingBuffer
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

