#pragma once


//外部
#include "../../../../../Assets/Shared/Material.h"

class MaterialContext;
class ModelContext;

class Materials
{
public:
    //これを呼び出したらマテリアルのダーティーをオンにします
    template<Material::Type type>
    auto& Ref()
    {
        //データ型チェック  
        Material::CheckIsMaterialTypeAttachable<type>();

        //ダーティカウントリセット
        dirtyArr[UINT(type)] = (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer;

        auto* paramPtr = GetMaterialPtr<type>();

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

    //マテリアルタイプからマテリアルの実データを取り出す
    //ヌルの可能性はある
    template<Material::Type type>
    auto* GetMaterialPtr()
    {
        return
        std::get<std::unique_ptr<typename Material::MaterialTypeTraits<type>::dataType>>(params).get();
    }

    template<Material::Type type>
    auto* GetMaterialConstPtr()const
    {
        return
            std::get<std::unique_ptr<typename Material::MaterialTypeTraits<type>::dataType>>(params).get();
    }

    //マテリアルダーティチェックして、ダーティーだったらそのマテリアルのポインタを返す
    //ほぼバッチング専用
    template<Material::Type type>
    auto* GetMaterialPtrIfDirty()const 
    {
        auto* dstMaterial = GetMaterialConstPtr<type>();
        
        if (dirtyArr[(UINT)type] == 0)
        {
            dstMaterial = nullptr;
        }

        return dstMaterial;
    }

    //ダーティカウントを一つ減らす
    template<Material::Type type>
    void DecrementDirtyCnt()
    {
#ifdef _DEBUG

        auto& dst = dirtyArr[(UINT)type];

        ErrorMessageOutput::Assert::DetectError
        (
            dst <= (UINT)ProjectConfig::Render::NumBuffer::kDoubleBuffer,
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

