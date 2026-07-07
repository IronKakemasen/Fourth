#include "PreCompileHeader.h"
#include "GraphicsPSO_KeyPackager.h"

using namespace RenderPathComponent;
using namespace RenderStateComponent;
using namespace ShaderPathComponent;


RenderContext::PSO_PoolDispatcher::GraphicsPSO_KeyPackager::GraphicsPSO_KeyPackager()
{
    renderPassBL.Init((uint32_t)Pass::kCount, 0);
    depthEnableBL.Init((uint32_t)DepthEnable::kCount, renderPassBL.EndLocation());
    depthTestBL.Init((uint32_t)DepthTest::kCount, depthEnableBL.EndLocation());
    meshTypeBL.Init((uint32_t)MeshType::kCount, depthTestBL.EndLocation());
    materialTypeBL.Init((uint32_t)MaterialType::kCount, meshTypeBL.EndLocation());
    blendModeBL.Init((uint32_t)BlendMode::kCount, materialTypeBL.EndLocation());
    fillModeBL.Init((uint32_t)FillMode::kCount, blendModeBL.EndLocation());
    cullModeBL.Init((uint32_t)CullMode::kCount, fillModeBL.EndLocation());
}