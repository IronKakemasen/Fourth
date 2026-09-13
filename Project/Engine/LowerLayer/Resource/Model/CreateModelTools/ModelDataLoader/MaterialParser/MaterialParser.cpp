#include "PreCompileHeader.h"
#include "MaterialParser.h"


#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"
#include ".././../../../External/assimp/include/assimp/cimport.h"

#include "StringConverter/StringConverter.h"

namespace
{
    auto const fileName = "MaterialParser.cpp";
}

using namespace StructuredBufferModelData;

void ModelContext::ModelDataLoader::MaterialParser::ParseMaterial(MaterialCPU& dstMaterial_, const aiMaterial* pSrcMaterial_)
{
    // 拡散反射成分
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
            dstMaterial_.albedoTexture = StringConverter::ConvertString(Convert(path));
        }
    }

    //法線マップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_NORMALS(0), path) == AI_SUCCESS)
        {
            dstMaterial_.normalTexture = StringConverter::ConvertString(Convert(path));
        }
        else
        {
            if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_HEIGHT(0), path) == AI_SUCCESS)
            {
                dstMaterial_.normalTexture = StringConverter::ConvertString(Convert(path));
            }
            else
            {
                dstMaterial_.normalTexture.clear();
            }
        }
    }

    //colorマップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_EMISSIVE(0), path) == AI_SUCCESS)
        {
            dstMaterial_.emissiveTexture = StringConverter::ConvertString(Convert(path));
        }
    }


}


std::wstring ModelContext::ModelDataLoader::MaterialParser::Convert(const aiString& path_)
{
    wchar_t temp[256] = {};
    size_t  size;
    mbstowcs_s(&size, temp, path_.C_Str(), 256);
    return StringConverter::ConvertString(std::string(path_.C_Str()));
}
