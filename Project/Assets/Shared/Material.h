#pragma once

#ifdef __cplusplus

#include "../../Engine/LowerLayer/Buffer/BufferDefinition/TextureComponent.h"
#include "StaticSampler.h"
#include "../../Engine/Math/Vector/Vector4.h"

namespace Material
{
    enum class Type
    {
        kStandard,
        kGridLine,
        
        
        
        
       
        kOffscreen,
        kNone,
        kCount

    };

    static constexpr UINT kNumParamExists = 2;

    template<Material::Type>
    struct MaterialTypeTraits;

    template<Material::Type type>
    inline void CheckIsMaterialTypeAttachable()
    {
        static_assert
        (
            ((UINT)type < (UINT)Type::kOffscreen),
            "Detected unattachable Material Type (Material.h)"
        );
    }

    struct MaterialIndexGroupCPUGPU
    {
        UINT standardIndex = kInvalid;
        UINT gridLineIndex = kInvalid;

    };
    static_assert
    (
        sizeof(MaterialIndexGroupCPUGPU) == sizeof(UINT) * kNumParamExists,
        "MaterialIndexGroupCPUGPU is incomplete"
    );

    struct MaterialArrBufferSrvIndexGroupCPUGPU
    {
        SRVHeapIndex standardSrv = kInvalid;
        SRVHeapIndex gridLineSrv = kInvalid;
    };

    static_assert
    (
        sizeof(MaterialArrBufferSrvIndexGroupCPUGPU) == sizeof(SRVHeapIndex) * kNumParamExists,
        "MaterialArrBufferSrvIndexGroupCPUGPU is incomplete"
    );

    struct StandardCPU
    {
        std::string albedoTexture = "";
        std::string normalTexture = "";
        std::string emissiveTexture = "";
        Vector4<float> baseColor = { float(kInvalid),float(kInvalid),float(kInvalid),float(kInvalid) };
        float roughness = float(kInvalid);
        float metallic = float(kInvalid);
        StaticSampler::SamplerState albedoTexSamplerState = StaticSampler::SamplerState::kLinearClamp;
    };

    struct StandardGPU
    {
        SRVHeapIndex albedoTexture = kInvalid;
        SRVHeapIndex normalTexture = kInvalid;
        SRVHeapIndex emissiveTexture = kInvalid;
        Vector4<float> baseColor = { float(kInvalid),float(kInvalid),float(kInvalid),float(kInvalid) };
        float roughness = float(kInvalid);
        float metallic = float(kInvalid);
        StaticSampler::SamplerState albedoTexSamplerState = StaticSampler::SamplerState::kLinearClamp;

        void ChangeRoughness(float dst_) { roughness = dst_; }
        void ChangeMetallic(float dst_) { metallic = dst_; }
        void ChangeColor(Vector4<float> const& dst_) { baseColor = dst_; }
        void ChangeAlbedoTexSamplerState(StaticSampler::SamplerState dst_) { albedoTexSamplerState = dst_; }
        template<TextureComponent::TextureType textureType>
        void ChangeTexture(SRVHeapIndex dst_)
        {
            static_assert
            (
                (UINT)textureType < (UINT)TextureComponent::TextureType::kSprite,
                "Detected Invalid TextureType Material.h"
            );

            if constexpr (textureType == TextureComponent::TextureType::kAlbedo) albedoTexture = dst_;
            else if constexpr (textureType == TextureComponent::TextureType::kEmissive) emissiveTexture = dst_;
            else if constexpr (textureType == TextureComponent::TextureType::kNormal) normalTexture = dst_;
        }

    };

    struct GridLineCPUGPU
    {
    private:

        Vector4<float> gridColor;
        Vector4<float> backgroundColor;
        float gridScale = 1.0f;
        float gridRatio = 1.0f;

    public:

        void ChangeGridColor(Vector4<float> const& dst_) { gridColor = dst_; }
        void ChangeBackgroundColor(Vector4<float> const& dst_) { backgroundColor = dst_; }
        void ChangeGridScale(float dst_) { gridScale = dst_; }
        void ChangeGridRatio(float dst_) { gridRatio = dst_; }

    };





}

template<>
struct Material::MaterialTypeTraits<Material::Type::kStandard>
{
    static constexpr UINT kReserveSize = 10;
    static inline const std::string kName = "Standard";
    using dataType = Material::StandardGPU;
};

template<>
struct Material::MaterialTypeTraits<Material::Type::kGridLine>
{
    static constexpr UINT kReserveSize = 10;
    static inline const std::string kName = "GridLine";
    using dataType = Material::GridLineCPUGPU;
};


#else

struct MaterialGridLine
{
    float4 gridColor;
    float4 backgroundColor;
    float gridScale;
    float gridRatio;
};

struct MaterialStandard
{
    uint albedoIndex;
    uint normalIndex;
    uint emissiveIndex;
    float4 baseColor;
    float roughness;
    float metallic;
    uint samplerState;
};


struct MaterialIndexGroup
{
    uint standardIndex;
    uint gridLineIndex;
};

struct MaterialArrBufferSrvIndexGroup
{
    uint standardSrv;
    uint gridLineSrv;
};


#endif
