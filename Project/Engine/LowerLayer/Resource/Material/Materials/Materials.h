#pragma once


//外部
#include "../../../../../Assets/Shared/Material.h"

class MaterialContext;

struct Materials
{
private:
    //インターフェースを絞るため
    friend class MaterialContext;

    struct InstantiateLicence { explicit InstantiateLicence() = default; };

public:

    //IDはMaterialIndexDispatcherが割り当てる
    Materials(InstantiateLicence licence_ ,UINT materialID_);

    //これを呼び出したらマテリアルのダーティーをオンにします
    template<Material::Type type>
    auto& Ref()
    {
        //データ型チェック  
        Material::CheckIsMaterialTypeAttachable<type>();

        //ダーティカウントリセット
        dirtyArr[UINT(type)] = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;

        auto* paramPtr =
            std::get<std::unique_ptr<typename Material::MaterialTypeTraits<type>::dataType>>(params).get();

#ifdef _DEBUG

        ErrorMessageOutput::Assert::DetectError
        (
            paramPtr,
            "アタッチしていないマテリアルの参照を取得すな: " + Material::MaterialTypeTraits<type>::kName,
            "Materials.h"
        );

#endif // _DEBUG

        return *paramPtr;
    }

    template<Material::Type type>
    auto const& Watch()const
    {
        //データ型チェック  
        Material::CheckIsMaterialTypeAttachable<type>();

        auto* paramPtr =
            std::get<std::unique_ptr<typename Material::MaterialTypeTraits<type>::dataType>>(params).get();

#ifdef _DEBUG

        ErrorMessageOutput::Assert::DetectError
        (
            paramPtr,
            "アタッチしていないマテリアルの参照を取得すな: " + Material::MaterialTypeTraits<type>::kName,
            "Materials.h"
        );

#endif // _DEBUG

        return *paramPtr;
    }

private:

    //マテリアル配列インデックス群配列のID
    UINT materialID = kInvalid;

    //パラメーター群
    std::tuple
    <
        std::unique_ptr<Material::StandardGPU>,
        std::unique_ptr<Material::GridLineCPUGPU>
    > params;

    //バッファ書き込みダーティ判定用
    std::array<UINT, Material::kNumParamExists> dirtyArr;
};

