#include "PreCompileHeader.h"
#include "MaterialParser.h"


//外部
#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"
#include ".././../../../External/assimp/include/assimp/cimport.h"

#include "StringProcessing/StringProcessing.h"

namespace
{
    auto const fileName = "MaterialParser.cpp";
}

void ModelContext::ModelDataLoader::MaterialParser::ParseMaterial(Material::StandardCPU& dstMaterial_, const aiMaterial* pSrcMaterial_)
{
    //ベースカラー
    {
        //カラーの定義が無いのに勝手に書き込むので、1.0で書き込んじゃいます
        dstMaterial_.baseColor.x = 1.0f;
        dstMaterial_.baseColor.y = 1.0f;
        dstMaterial_.baseColor.z = 1.0f;
        dstMaterial_.baseColor.w = 1.0f;
    }

    //colorマップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
        {
            dstMaterial_.albedoTexture = Convert(path);
        }
    }

    //法線マップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_NORMALS(0), path) == AI_SUCCESS)
        {
            dstMaterial_.normalTexture = Convert(path);
        }
        else
        {
            if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_HEIGHT(0), path) == AI_SUCCESS)
            {
                dstMaterial_.normalTexture = Convert(path);
            }
        }
    }

    //エミッシブマップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_EMISSIVE(0), path) == AI_SUCCESS)
        {
            dstMaterial_.emissiveTexture = Convert(path);
        }
    }

    //ラフネス
    {
        float roughness{};
        if (pSrcMaterial_->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness) == AI_SUCCESS)
        {
            dstMaterial_.roughness = roughness;
        }
    }

    //メタリック
    {
        float metallic{};
        if (pSrcMaterial_->Get(AI_MATKEY_METALLIC_FACTOR, metallic) == AI_SUCCESS)
        {
            dstMaterial_.metallic = metallic;
        }
    }
}


std::string ModelContext::ModelDataLoader::MaterialParser::Convert(const aiString& path_)
{
    return StringProcessing::RemoveFileExtension(std::string(path_.C_Str()));
}
