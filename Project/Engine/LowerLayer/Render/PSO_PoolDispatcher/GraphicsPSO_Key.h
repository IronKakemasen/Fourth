#pragma once
#include "../RenderPathStructure/RenderStateComponent.h"
#include "../RenderPathStructure/ShaderPathComponent.h"
#include "../RenderPathStructure/RenderPassComponent.h"

struct GraphicsPSO_Key
{
    ///シーケンス
    enum Sequence
    {
        kPass,
        kDepthEnable,
        kDepthTest,
        kMeshType,
        kMaterialType,
        kBlendMode,
        KFillMode,
        kCullMode
    };

private:

    int const kInvalid = -1;

    RenderPassComponent::Pass pass =                RenderPassComponent::Pass(kInvalid);
    RenderPassComponent::DepthEnable depthEnable =  RenderPassComponent::DepthEnable(kInvalid);
    RenderPassComponent::DepthTest depthTest =      RenderPassComponent::DepthTest(kInvalid);
    ShaderPathComponent::MeshType mesh =            ShaderPathComponent::MeshType(kInvalid);
    ShaderPathComponent::MaterialType material =    ShaderPathComponent::MaterialType(kInvalid);
    RenderStateComponent::BlendMode blend =         RenderStateComponent::BlendMode(kInvalid);
    RenderStateComponent::FillMode fill =           RenderStateComponent::FillMode(kInvalid);
    RenderStateComponent::CullMode cull =           RenderStateComponent::CullMode(kInvalid);

    template <Sequence sequence>
    static constexpr auto sequenceToType()
    {
        if      constexpr (sequence == kPass)         return RenderPassComponent::Pass{};
        else if constexpr (sequence == kDepthEnable)  return RenderPassComponent::DepthEnable{};
        else if constexpr (sequence == kDepthTest)    return RenderPassComponent::DepthTest{};
        else if constexpr (sequence == kMeshType)     return ShaderPathComponent::MeshType{};
        else if constexpr (sequence == kMaterialType) return ShaderPathComponent::MaterialType{};
        else if constexpr (sequence == kBlendMode)    return RenderStateComponent::BlendMode{};
        else if constexpr (sequence == KFillMode)     return RenderStateComponent::FillMode{};
        else if constexpr (sequence == kCullMode)     return RenderStateComponent::CullMode{};
    }

public:

    template <Sequence sequence>
    using SequenceToType = decltype(sequenceToType<sequence>());


    GraphicsPSO_Key
    (
        RenderPassComponent::Pass pass_,
        RenderPassComponent::DepthEnable depthEnable_,
        RenderPassComponent::DepthTest depthTest_,
        ShaderPathComponent::MeshType mesh_,
        ShaderPathComponent::MaterialType material_,
        RenderStateComponent::BlendMode blend_,
        RenderStateComponent::FillMode fill_,
        RenderStateComponent::CullMode cull_
    ) :pass(pass_), depthEnable(depthEnable_), depthTest(depthTest_), mesh(mesh_), material(material_), blend(blend_), fill(fill_), cull(cull_)
    {

    }

     template<Sequence sequence>
     constexpr auto Get() const
     {
         if      constexpr (sequence == kPass)         return pass;
         else if constexpr (sequence == kDepthEnable)  return depthEnable;
         else if constexpr (sequence == kDepthTest)    return depthTest;
         else if constexpr (sequence == kMeshType)     return mesh;
         else if constexpr (sequence == kMaterialType) return material;
         else if constexpr (sequence == kBlendMode)    return blend;
         else if constexpr (sequence == KFillMode)     return fill;
         else if constexpr (sequence == kCullMode)     return cull;
     }

     template<Sequence sequence>
     static constexpr UINT Count() 
     {
         return (UINT)SequenceToType<sequence>::kCount;
     }



};