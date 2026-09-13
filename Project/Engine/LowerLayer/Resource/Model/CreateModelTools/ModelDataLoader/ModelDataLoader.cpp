#include "PreCompileHeader.h"
#include "ModelDataLoader.h"

#include "MeshParser/MeshParser.h"
#include "MaterialParser/MaterialParser.h"
#include "ModelDataCache/ModelDataCache.h"
#include "../../ModelStructure/ModelData/ModelData.h"


//外部
#include "StringConverter/StringConverter.h"

#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"

namespace
{
    auto const fileName = "ModelDataLoader.cpp";
}

ModelContext::ModelDataLoader::ModelDataLoader(NexusFieldProof proof_)
{
    Logger::Entry("ModelDataLoader: Constructor");


	modelDataCache.reset(new ModelDataCache(proof_));
    Logger::Log("Instantiate: ModelDataCache",fileName);

    Logger::End("ModelDataLoader: Constructor");
}

ModelContext::ModelDataLoader::~ModelDataLoader()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelData* ModelContext::ModelDataLoader::Load(std::string fileName_ , std::string filePath_)
{
    std::unique_ptr<ModelData> modelData = std::make_unique<ModelData>();

	///同じモデルファイルを読み込んでいる場合は何かおかしいのでアサート
	modelDataCache->FindDuplication(ModelDataCache::AccessKey{},fileName_);

    // wchar_t から char型(UTF-8)に変換
    auto path = StringConverter::ToUTF8(StringConverter::ConvertString(filePath_));

    Assimp::Importer importer;
    unsigned int flag = 0;
    flag |= aiProcess_Triangulate;
    flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;
    flag |= aiProcess_FlipWindingOrder;
    flag |= aiProcess_MakeLeftHanded;
    flag |= aiProcess_FixInfacingNormals;

    // ファイルを読み込み.
    scene = importer.ReadFile(path, flag);
    ErrorMessageOutput::Abort::DetectError(scene, "シーンデータが無い", fileName);

    //メッシュのメモリを確保
    modelData->resourceMesh.clear();
    if(scene) modelData->resourceMesh.resize(scene->mNumMeshes);

    // メッシュデータを変換.
    for (size_t i = 0; i < modelData->resourceMesh.size(); ++i)
    {
        const auto pMesh = scene->mMeshes[i];
        MeshParser::ParseMesh(modelData->resourceMesh[i], pMesh);
    }

    //マテリアルのメモリを確保
    modelData->resourceMaterial.clear();
    if(scene)modelData->resourceMaterial.resize(scene->mNumMaterials);

    //マテリアルデータを変換
    for (size_t i = 0; i < modelData->resourceMaterial.size(); ++i)
    {
        const auto pMaterial = (scene) ? scene->mMaterials[i] : nullptr;
        MaterialParser::ParseMaterial(modelData->resourceMaterial[i], pMaterial);
    }

    //キャッシュデータに登録
    auto returnPtr = modelData.get();
    modelDataCache->StoreTemporarily(ModelContext::ModelDataLoader::ModelDataCache::AccessKey{}, fileName_, std::move(modelData));

    //不要になったのでクリア
    importer.FreeScene();
    scene  = nullptr;

    Logger::Log("Complete: Loading " + fileName_, fileName);

    return returnPtr;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
