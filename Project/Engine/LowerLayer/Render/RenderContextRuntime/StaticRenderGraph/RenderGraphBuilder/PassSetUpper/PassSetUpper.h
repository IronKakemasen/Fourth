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

	//全パスの所持するPassDesc -> PassInfoに移し替える
	static void CreateAllPassInfo
	(
		NexusFieldProof proof_,
		BuildOutput::PassSetUpper& output_,
		RenderPassCreator& renderPassCreator_,
		RenderPassContainer& passContainer_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	///各パスが参照するバッファのsrvHeapIndexを配列したもののバッファ、そしてそのsrvHeapIndexの定数バッファを作成
	//ReferenceBufferSrvArrayバッファのバッファインデックスを返す
	static void CreateReferenceBufferSrvArray
	(
		NexusFieldProof proof_,
		BuildOutput::PassSetUpper& output_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//Passのルートコンスタンツのバッファを作る
	static void CreatePassRootConstantsBuffer
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//フロントバッファが参照するカラーバッファのIDからSrvHeapIndexを取得し
	//それを入れるためのルートコンスタンツ用定数バッファを作成
	//この参照するカラーバッファはシングルだと思うのでランタイムの更新はいらないはず
	static void CreateFinalRefSrvConstantBuffer
	(
		NexusFieldProof proof_,
		BufferUniqueID const finalBufferID_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	struct DataKey
	{
		static inline auto const kRenderGraphSettings = "RenderGraphSettings";
		static inline auto const kFinalColorBuffer	  = "FinalColorBuffer";
	};
};

