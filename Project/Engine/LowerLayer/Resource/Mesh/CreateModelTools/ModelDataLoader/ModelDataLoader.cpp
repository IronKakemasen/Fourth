#include "PreCompileHeader.h"
#include "ModelDataLoader.h"

#include "MeshParser/MeshParser.h"
#include "MaterialParser/MaterialParser.h"
#include "ModelDataCache/ModelDataCache.h"

#include "StringConnverter/StringConverter.h"

#include ".././../../../External/assimp/include/assimp/Importer.hpp"
#include ".././../../../External/assimp/include/assimp/scene.h"
#include ".././../../../External/assimp/include/assimp/postprocess.h"

namespace
{
    auto const fileName = "ModelDataLoader.cpp";
}

MeshContext::ModelDataLoader::ModelDataLoader(MeshContext::InstanceKey key_)
{
    Logger::Entry("ModelDataLoader: Constructor");


	modelDataCache.reset(new ModelDataCache(key_));
    Logger::Log("Instantiate: ModelDataCache",fileName);

    Logger::End("ModelDataLoader: Constructor");
}

MeshContext::ModelDataLoader::~ModelDataLoader()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelDataAggregate* MeshContext::ModelDataLoader::Load(std::string fileName_ , std::string filePath_)
{
    std::unique_ptr<ModelDataAggregate> modelDataAggregate = std::make_unique<ModelDataAggregate>();

	///同じモデルファイルを読み込んでいる場合は何かおかしいのでアサート
	ModelDataAggregate* cachedModelData = modelDataCache->FindDuplication(ModelDataCache::AccessKey{},fileName_);
    ErrorMessageOutput::Assert::DetectError(!cachedModelData, "ファイルを重複読み込みしている", fileName);

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
    modelDataAggregate->resourceMesh.clear();
    if(scene) modelDataAggregate->resourceMesh.resize(scene->mNumMeshes);

    // メッシュデータを変換.
    for (size_t i = 0; i < modelDataAggregate->resourceMesh.size(); ++i)
    {
        const auto pMesh = scene->mMeshes[i];
        MeshParser::ParseMesh(modelDataAggregate->resourceMesh[i], pMesh);
    }

    //マテリアルのメモリを確保
    modelDataAggregate->resourceMaterial.clear();
    if(scene)modelDataAggregate->resourceMaterial.resize(scene->mNumMaterials);

    //マテリアルデータを変換
    for (size_t i = 0; i < modelDataAggregate->resourceMaterial.size(); ++i)
    {
        const auto pMaterial = scene->mMaterials[i];
        MaterialParser::ParseMaterial(modelDataAggregate->resourceMaterial[i], pMaterial);
    }

    //キャッシュデータに登録
    auto returnPtr = modelDataAggregate.get();
    modelDataCache->Register(MeshContext::ModelDataLoader::ModelDataCache::AccessKey{}, fileName_, std::move(modelDataAggregate));

    //不要になったのでクリア
    importer.FreeScene();
    scene  = nullptr;

    Logger::Log("Complete: Loading " + fileName_, fileName);

    return returnPtr;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
