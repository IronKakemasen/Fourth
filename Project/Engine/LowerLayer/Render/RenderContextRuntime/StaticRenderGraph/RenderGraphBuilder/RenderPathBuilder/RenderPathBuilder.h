#pragma once
#include "../../StaticRenderGraph.h"

class RenderContext::StaticRenderGraph::PathBuilder
{
	friend class StaticRenderGraph;



	//以下ヘルパー
private:

	//全てのPathを生成
	static std::vector<RenderContext::PathBehavior*> Build
	(
		NexusFieldProof proof_,
		RenderPathAssembler& pathAssembler_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	//Jsonファイルに記録されているシーケンス通りに、AllPathPtrを一列に並び替えて返す
	static std::vector<RenderContext::PathBehavior*> SortInSequence(std::vector<RenderContext::PathBehavior*>& allPathPtr_);

	struct DataKey
	{
		static inline const std::string kSrcJsonFile = "RenderGraphSettings";
		static inline const std::string kPathSequence = "PathSequence";

	};
};

