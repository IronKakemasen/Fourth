#include "PreCompileHeader.h"
#include "MaterialParser.h"
#include "../../../ModelStructure/ModelData/ResourceMaterial/ResourceMaterial.h"


#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"
#include ".././../../../External/assimp/include/assimp/cimport.h"

#include "StringConnverter/StringConverter.h"

namespace
{
    auto const fileName = "MaterialParser.cpp";
}



void MeshContext::ModelDataLoader::MaterialParser::ParseMaterial(ResourceMaterial& dstMaterial_, const aiMaterial* pSrcMaterial_)
{
    // 拡散反射成分
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);

        if (pSrcMaterial_->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.diffuse.data.x = color.r;
            dstMaterial_.standardMaterial.diffuse.data.y = color.g;
            dstMaterial_.standardMaterial.diffuse.data.z = color.b;
        }
    }

    // 鏡面反射成分
    {
        aiColor3D color(0.0f, 0.0f, 0.0f);

        if (pSrcMaterial_->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.specular = { color.r,color.g,color.b };
        }
    }

    // 鏡面反射強度
    {
        auto shininess = 0.0f;
        if (pSrcMaterial_->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.shininess = shininess;
        }
    }

    // colorマップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.colorMap = StringConverter::ConvertString(Convert(path));
        }
    }

    // スペキュラーマップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_SPECULAR(0), path) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.specularMap = StringConverter::ConvertString(Convert(path));
        }
    }

    // シャイネスマップ
    {
        aiString path;

        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_SHININESS(0), path) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.shininessMap = StringConverter::ConvertString(Convert(path));
        }
    }

    // 法線マップ
    {
        aiString path;
        if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_NORMALS(0), path) == AI_SUCCESS)
        {
            dstMaterial_.standardMaterial.normalMap = StringConverter::ConvertString(Convert(path));
        }
        else
        {
            if (pSrcMaterial_->Get(AI_MATKEY_TEXTURE_HEIGHT(0), path) == AI_SUCCESS)
            {
                dstMaterial_.standardMaterial.normalMap = StringConverter::ConvertString(Convert(path));
            }
            else
            {
                dstMaterial_.standardMaterial.normalMap.clear();
            }
        }
    }
}


std::wstring MeshContext::ModelDataLoader::MaterialParser::Convert(const aiString& path_)
{
    wchar_t temp[256] = {};
    size_t  size;
    mbstowcs_s(&size, temp, path_.C_Str(), 256);
    return StringConverter::ConvertString(std::string(path_.C_Str()));
}
