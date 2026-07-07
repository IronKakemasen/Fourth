#pragma once
#include "../RenderPathStructure/RenderStateComponent.h"
#include "../RenderPathStructure/ShaderPathComponent.h"
#include "../RenderPathStructure/RenderPathComponent.h"

struct GraphicsPSO_Key
{
private:
    int const kInvalid = -1;

public:

    ///意味あるか分からんが、いちおうシーケンスを明示しとく
    enum Sequence
    {
        kPass,
        kDepthEnable,
        kDepthtest,
        kMeshType,
        kMaterialType,
        kBlendMode,
        KFillMode,
        kCullMode
    };

    GraphicsPSO_Key
    (
        RenderPathComponent::Pass pass_,
        RenderPathComponent::DepthEnable depthEnable_,
        RenderPathComponent::DepthTest depthTest_,
        ShaderPathComponent::MeshType mesh_,
        ShaderPathComponent::MaterialType material_,
        RenderStateComponent::BlendMode blend_,
        RenderStateComponent::FillMode fill_,
        RenderStateComponent::CullMode cull_
    ) :pass(pass_), depthEnable(depthEnable_), depthTest(depthTest_), mesh(mesh_), material(material_), blend(blend_), fill(fill_), cull(cull_)
    {

    }

     RenderPathComponent::Pass pass = RenderPathComponent::Pass(kInvalid);
     RenderPathComponent::DepthEnable depthEnable = RenderPathComponent::DepthEnable(kInvalid);
     RenderPathComponent::DepthTest depthTest = RenderPathComponent::DepthTest(kInvalid);
     ShaderPathComponent::MeshType mesh = ShaderPathComponent::MeshType(kInvalid);
     ShaderPathComponent::MaterialType material = ShaderPathComponent::MaterialType(kInvalid);
     RenderStateComponent::BlendMode blend = RenderStateComponent::BlendMode(kInvalid);
     RenderStateComponent::FillMode fill = RenderStateComponent::FillMode(kInvalid);
     RenderStateComponent::CullMode cull = RenderStateComponent::CullMode(kInvalid);
};