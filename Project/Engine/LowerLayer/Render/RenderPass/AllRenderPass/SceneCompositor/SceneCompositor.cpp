#include "PreCompileHeader.h"
#include "SceneCompositor.h"
#include "../../PassDesc/PassDesc.h"
#include "../../RuntimePassInfo/RuntimePassInfo.h"


//外部
#include "../../../../Resource/Model/ModelStructure/Model.h"
#include "../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

SceneCompositor::SceneCompositor(RenderContext::NexusFieldProof proof_, std::unique_ptr<RenderContext::PassDesc>&& desc_)
	:RenderContext::PassBehavior(proof_, std::move(desc_))
{

}


void SceneCompositor::Update
(
	[[maybe_unused]] std::unordered_map<uint32_t, std::pair<RenderStateKey, std::vector<Model*>>> const& modelContainer_,
	RuntimeWrapper& cmdWrapper_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{

}
