#pragma once
#include "../../RenderPass/RenderPassComponent.h"
#include "../../RenderStateComponent.h"

//外部
#include "../../../Resource/Shader/ShaderPathComponent/ShaderPathComponent.h"


struct GraphicsPSO_Key
{

    ///シーケンス
    enum Sequence
    {
        kPass,
        kMeshType,
        kMaterialType,
        kBlendMode,
        KFillMode,
        kCullMode
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
        else if constexpr (sequence == KFillMode)     return RenderStateComponent::FillMode{};
        else if constexpr (sequence == kCullMode)     return RenderStateComponent::CullMode{};
    }

public:

    template <Sequence sequence>
    using SequenceToType = decltype(sequenceToType<sequence>());

    GraphicsPSO_Key() = default;

    GraphicsPSO_Key
    (
        RenderPassComponent::Pass pass_,
        ShaderPathComponent::MeshType mesh_,
        ShaderPathComponent::MaterialType material_,
        RenderStateComponent::BlendMode blend_,
        RenderStateComponent::FillMode fill_,
        RenderStateComponent::CullMode cull_
    ) :pass(pass_), mesh(mesh_), material(material_), blend(blend_), fill(fill_), cull(cull_)
    {

    }

    RenderPassComponent::Pass pass = RenderPassComponent::Pass(kInvalid);
    ShaderPathComponent::MeshType mesh = ShaderPathComponent::MeshType(kInvalid);
    ShaderPathComponent::MaterialType material = ShaderPathComponent::MaterialType(kInvalid);
    ///超重要。このPSOキーにおけるblendModeはつまるところkDependsModelかそれ以外の２パターン存在する
    ///kDependsModelを選択した場合、モデルのblendModeがそのパスにある
    ///kDependsModelを選択しているカラーバッファに影響する
    ///それ以外のタグを選択している場合は、カラーバッファ[0]のblendModeが代表として設定される
    ///Pass X BlendMode　で使用するカラーバッファのblendModeは一意に決まるので恐らく心配する必要はない
    RenderStateComponent::BlendMode blend = RenderStateComponent::BlendMode(kInvalid);
    RenderStateComponent::CullMode cull = RenderStateComponent::CullMode(kInvalid);

    ///これもblendModeと同じような感じ。モデル描画パスではWireFrameは有効だが、
    ///そうでなければSolidのみ。キーがWireFrameだからと言って、そのパスの全てのバッファの
    ///fillModeがwireFrameにはならない。あくまでモデル描画するカラーバッファの影響する
    RenderStateComponent::FillMode fill = RenderStateComponent::FillMode(kInvalid);


     template<Sequence sequence>
     constexpr auto Get() const
     {
         if      constexpr (sequence == kPass)         return pass;
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