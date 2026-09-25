#include "PreCompileHeader.h"
#include "SceneOpaque.h"
#include "../../PassDesc/PassDesc.h"
#include "../../RuntimePassInfo/RuntimePassInfo.h"

//外部
#include "../../../../Resource/Model/ModelStructure/Model.h"
#include "../../../../Core/Command/RuntimeWrapper/RuntimeWrapper.h"

SceneOpaque::SceneOpaque(RenderContext::NexusFieldProof proof_ , std::unique_ptr<RenderContext::PassDesc>&& desc_)
	:RenderContext::PassBehavior(proof_, std::move(desc_))
{

}

void SceneOpaque::Update
(
	[[maybe_unused]] std::pair<RenderStateKey, std::vector<Model*>> const& modelContainer_,
	RuntimeWrapper& cmdWrapper_,
	BufferContext::BufferDispatcher& bufDispatcher_
)
{

}
