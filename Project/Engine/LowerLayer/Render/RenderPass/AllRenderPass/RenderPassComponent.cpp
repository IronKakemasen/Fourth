#include "RenderPassComponent.h"
#include "RenderPassName.h"



RenderPassComponent::Pass RenderPassComponent::PassNameToPassType(std::string const passName_)
{
    RenderPassComponent::Pass pass = RenderPassComponent::Pass::kEnd;

    if (passName_ == RenderPassName::PassTypeToName<SceneTextureCreator>::name)
    {
        pass = RenderPassComponent::Pass::kSceneTextureCreator;
    }
    else
    {
        ErrorMessageOutput::Assert::OutputError("そんなパスネームは存在しない", "RenderPassComponent.cpp");
    }

    return pass;
}
