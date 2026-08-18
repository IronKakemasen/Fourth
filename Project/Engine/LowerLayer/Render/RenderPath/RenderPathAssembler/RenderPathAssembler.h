#pragma once
#include "../../RenderContext.h"
#include "../AllRenderPath/AllPathFwd.h"
#include "../../RenderPass/AllRenderPass/RenderPassComponent.h"
#include "../AllRenderPath/RenderPathName.h"

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
		std::string const pathName = RenderPathName::PathTypeToName<PathType>::name;
		std::unique_ptr<PathType> path = InstantiatePath<PathType>(proof_);

		std::vector<PassAndName> passAndNames =  LoadPathSettings(pathName);

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
	std::unique_ptr<PathType> InstantiatePath(NexusFieldProof proof_);

};


template<>
std::unique_ptr<CreateSceneTexture> RenderContext::RenderPathAssembler::InstantiatePath(NexusFieldProof proof_);
