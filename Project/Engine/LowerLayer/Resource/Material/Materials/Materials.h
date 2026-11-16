#pragma once


//外部
#include "../../../../../Assets/Shared/Material.h"

class MaterialContext;
class ModelContext;

struct Materials
{
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

    //インターフェースを絞るため
    friend class MaterialContext;
    friend class ModelContext;

    //IDはMaterialIndexDispatcherが割り当てる
    Materials(UINT materialID_);

    //マテリアルダーティチェック
    template<Material::Type type>
    bool IsMaterialDirty() { return dirtyArr[(UINT)type]; }

    //ダーティカウントを一つ減らす
    template<Material::Type type>
    void DecrementDirtyCnt()
    {
#ifdef _DEBUG

        auto& dst = dirtyArr[(UINT)type];

        ErrorMessageOutput::Assert::DetectError
        (
            dst > 0 && dst <= (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer,
            "マテリアルのダーティのインデックスがおかしい",
            "Materials.h"
        );

        dst--;

#else
        dirtyArr[(UINT)type]--;

#endif // _DEBUG
    }

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

