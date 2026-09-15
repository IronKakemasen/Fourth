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

using namespace StructuredBufferModelData;

void ModelContext::ModelDataLoader::MaterialParser::ParseMaterial(MaterialCPU& dstMaterial_, const aiMaterial* pSrcMaterial_)
{
    //ベースカラー
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);

        if (pSrcMaterial_->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        {
            dstMaterial_.baseColor.x = color.r;
            dstMaterial_.baseColor.y = color.g;
            dstMaterial_.baseColor.z = color.b;
        }
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


}


std::string ModelContext::ModelDataLoader::MaterialParser::Convert(const aiString& path_)
{
    wchar_t temp[256] = {};
    size_t  size;
    mbstowcs_s(&size, temp, path_.C_Str(), 256);

    return StringProcessing::RemoveFileExtension(std::string(path_.C_Str()));
}
