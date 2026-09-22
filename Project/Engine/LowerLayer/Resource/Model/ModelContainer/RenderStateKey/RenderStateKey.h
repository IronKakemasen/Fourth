#pragma once
#include "../ModelContainer.h"
#include "../../../../Render/RenderStateComponent.h"
#include "../../../../Resource/Shader/ShaderPathComponent/ShaderPathComponent.h"
#include "../../../../Render/RenderPass/RenderPassComponent.h"

struct ModelContext::ModelContainer::RenderStateKey
{
    ///シーケンス
    enum Sequence
    {
        kPass,
        kBlendMode,
        kCullMode,
        kMeshType,
        kMaterialType
    };

private:

    int const kInvalid = -1;

    template <Sequence sequence>
    static constexpr auto sequenceToType()
    {
        if      constexpr (sequence == kPass)         return RenderPassComponent::Pass{};
        else if constexpr (sequence == kMeshType)     return ShaderPathComponent::MeshType{};
        else if constexpr (sequence == kMaterialType) return ShaderPathComponent::MaterialType{};
        else if constexpr (sequence == kBlendMode)    return RenderStateComponent::BlendMode{};
        else if constexpr (sequence == kCullMode)     return RenderStateComponent::CullMode{};
    }

public:

    template <Sequence sequence>
    using SequenceToType = decltype(sequenceToType<sequence>());

    RenderStateKey() = default;

    RenderStateKey
    (
        RenderPassComponent::Pass pass_,
        RenderStateComponent::BlendMode blend_,
        RenderStateComponent::CullMode cull_,
        ShaderPathComponent::MeshType mesh_,
        ShaderPathComponent::MaterialType material_
    ) :pass(pass_), mesh(mesh_), material(material_), blend(blend_), cull(cull_)
    {

    }

    RenderPassComponent::Pass pass              = RenderPassComponent::Pass(kInvalid);
    RenderStateComponent::BlendMode blend       = RenderStateComponent::BlendMode(kInvalid);
    RenderStateComponent::CullMode cull         = RenderStateComponent::CullMode(kInvalid);
    ShaderPathComponent::MeshType mesh          = ShaderPathComponent::MeshType(kInvalid);
    ShaderPathComponent::MaterialType material  = ShaderPathComponent::MaterialType(kInvalid);


    template<Sequence sequence>
    constexpr auto Get() const
    {
        if      constexpr (sequence == kPass)         return pass;
        else if constexpr (sequence == kMeshType)     return mesh;
        else if constexpr (sequence == kMaterialType) return material;
        else if constexpr (sequence == kBlendMode)    return blend;
        else if constexpr (sequence == kCullMode)     return cull;
    }

    template<Sequence sequence>
    static constexpr UINT Count()
    {
        return (UINT)SequenceToType<sequence>::kCount;
    }
};
