#include "PreCompileHeader.h"
#include "RenderPathBuilder.h"
#include "../../../../RenderPath/RenderPathAssembler/RenderPathAssembler.h"


namespace
{
	auto const fileName = "RenderPathBuilder.cpp";
}


[[nodiscard]] AllPathPtr RenderContext::RenderGraph::PathBuilder::InstantiateAllPath
(
	NexusFieldProof proof_,
	RenderPathAssembler& pathAssembler_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	AllPathPtr allPathPtr;

	std::get<CreateSceneTexture*>(allPathPtr) = pathAssembler_.Assemble<CreateSceneTexture>(proof_, bufferContextDiplomat_);
	Logger::Log("Create: CreateSceneTexture", fileName);


	return allPathPtr;
}
