#include "PreCompileHeader.h"
#include "RenderPathBuilder.h"
#include "../../../../RenderPath/RenderPathAssembler/RenderPathAssembler.h"


namespace
{
	auto const fileName = "RenderPathBuilder.cpp";
}


[[nodiscard]] std::vector<RenderContext::PathBehavior*> RenderContext::StaticRenderGraph::PathBuilder::Build
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	std::vector<RenderContext::PathBehavior*> allPathPtr;

	allPathPtr.emplace_back(pathAssembler_.Assemble<CreateSceneTexture>(proof_, bufferContextDiplomat_));
	Logger::Log("Instantiate: CreateSceneTexture", fileName);

	//制御シーケンス通りに並び替える
	return SortInSequence(allPathPtr);
}


std::vector<RenderContext::PathBehavior*> RenderContext::StaticRenderGraph::PathBuilder::SortInSequence(std::vector<RenderContext::PathBehavior*>& allPathPtr_)
{
	std::vector<RenderContext::PathBehavior*> sortDst;

	//pathのシーケンス情報を取得
	auto* miyajison = Miyajison::Get();
	auto const pathSequence = miyajison->LoadData<std::vector<std::string>>(DataKey::kSrcJsonFile, { DataKey::kPathSequence });

	//path名と一致したpathのアドレス順に並べ替える
	for (auto const& srcPathName : pathSequence)
	{
		for (auto* pathPtr : allPathPtr_)
		{
			if (pathPtr->WatchName() == srcPathName)
			{
				sortDst.emplace_back(pathPtr);
			}
		}
	}

	//生成したパスの数と、シーケンス制御に記述された数の整合チェック
	ErrorMessageOutput::Assert::DetectError
	(
		sortDst.size() == pathSequence.size(),
		"生成したPathの数" + std::to_string(sortDst.size()) + "と、シーケンス制御の数" + std::to_string(pathSequence.size()) + "が合わない",
		fileName
	);

	return sortDst;
}
