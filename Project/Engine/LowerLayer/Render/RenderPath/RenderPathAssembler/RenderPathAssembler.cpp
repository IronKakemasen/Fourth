#include "PreCompileHeader.h"
#include "RenderPathAssembler.h"
#include "../../RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "../AllRenderPath/AllPathInclude.h"
#include "PathSettingsLoader/PathSettingsLoader.h"
#include "../../RenderPass/AllRenderPass/RenderPassTraits.h"

#include "../../../../../External/AI/PassCreationHelper/RenderPassFactoryTable.h"

using namespace RenderPassComponent;
using namespace RenderPassTraits;

RenderContext::RenderPathAssembler::RenderPathAssembler
(
	NexusFieldProof proof_,
	RenderPassCreator& passCreator_,
	RenderPathContainer& pathContainer_
)
	:passCreator(passCreator_), pathContainer(pathContainer_)
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
	auto const& factoryTable = RenderPassTraitsAI::PassFactoryTable();

	for (auto const& passType_string : passAndNames_)
	{
		auto* factory = factoryTable[(size_t)passType_string.first];

		ErrorMessageOutput::Assert::DetectError
		(
			factory != nullptr,
			"対応するPassFactoryが登録されていない: " + passType_string.second,
			"RenderPathAssembler.cpp"
		);

		if(factory) factory(passCreator, dstPath_, proof_, passType_string.second, bufferContextDiplomat_);
	}
}
