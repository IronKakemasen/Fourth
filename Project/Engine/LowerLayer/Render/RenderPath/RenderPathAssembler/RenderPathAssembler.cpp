#include "PreCompileHeader.h"
#include "RenderPathAssembler.h"
#include "../../RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "../AllRenderPath/AllPathInclude.h"
#include "PathSettingsLoader/PathSettingsLoader.h"

using namespace RenderPassComponent;

RenderContext::RenderPathAssembler::RenderPathAssembler
(
	NexusFieldProof proof_,
	std::unique_ptr <RenderPassCreator>&& passCreator_,
	RenderPathContainer* pathContainer_,
	BufferContextDiplomat& bufferContextDiplomat_
)
	:passCreator(std::move(passCreator_)), pathContainer(pathContainer_)
{

}

std::vector<RenderContext::RenderPathAssembler::PassAndName> RenderContext::RenderPathAssembler::LoadPathSettings(std::string const pathName_)
{
	//使用するPassを読み込む
	return PathSettingsLoader::ParseWhichPassUses(pathName_);
}

void RenderContext::RenderPathAssembler::AddPass
(
	NexusFieldProof proof_,
	std::vector<PassAndName> const& passAndNames_,
	PathBehavior& dstPath_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{

	//静的変数に書き直す。これどうにしたい
	for (auto const passType_string : passAndNames_)
	{
		RenderPassComponent::Pass pass = passType_string.first;

		switch (pass)
		{
		case RenderPassComponent::Pass::kSceneTextureCreator:

			dstPath_.AddPass
			(
				proof_,
				passCreator->Create<PassTypeToPassClass<RenderPassComponent::Pass::kSceneTextureCreator>::PassClass>
				(
					proof_,
					passType_string.second,
					bufferContextDiplomat_
				)
			);

			break;

		default:

			ErrorMessageOutput::Assert::OutputError("ここに到達するのはおかしい", "RenderPathAssembler.cpp");

			break;
		}
	}
}

