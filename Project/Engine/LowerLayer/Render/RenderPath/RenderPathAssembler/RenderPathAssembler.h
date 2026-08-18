#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPath/AllPathInclude.h"
#include "../AllRenderPath/RenderPathName.h"
#include "../../RenderPass/AllRenderPass/RenderPassComponent.h"

class RenderContext::RenderPathAssembler
{
	class PathSettingsLoader;
	using PassAndName = std::pair<RenderPassComponent::Pass, std::string>;

public:

	RenderPathAssembler
	(
		NexusFieldProof proof_, 
		RenderPassCreator* passCreator_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	template<typename PathType>
	std::unique_ptr<PathType> Assemble
	(
		NexusFieldProof proof_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{
		//Pathの名前
		std::string const pathName = RenderPathName::PathTypeToName<PathType>::name;
		//実体
		std::unique_ptr<PathType> path = InstantiatePath<PathType>(proof_);
		//そのPathが使用するPassのコンテナ
		std::vector<PassAndName> passAndNames =  LoadPathSettings(pathName);
		//それら情報をもとに、passCreatorでPassを作り追加する
		AddPass(proof_, passAndNames, *path.get(), bufferContextDiplomat_);

		return path;
	}


private:

	RenderPassCreator* passCreator;

	std::vector<PassAndName> LoadPathSettings(std::string const pathName_);

	void AddPass
	(
		NexusFieldProof proof_,
		std::vector<PassAndName> const& passAndNames_,
		PathBehavior& dstPath_,
		BufferContextDiplomat& bufferContextDiplomat_
	);

	template<typename PathType>
	std::unique_ptr<PathType> InstantiatePath(NexusFieldProof proof_)
	{
		return std::make_unique<CreateSceneTexture>(proof_);
	}

};

