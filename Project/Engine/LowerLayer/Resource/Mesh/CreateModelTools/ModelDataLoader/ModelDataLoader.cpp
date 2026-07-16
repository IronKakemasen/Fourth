#include "PreCompileHeader.h"
#include "ModelDataLoader.h"

#include "ModelDataCache/ModelDataCache.h"
#include "../../../../../../External/MeshOptimizer/meshoptimizer.h"
#include "../../../../../Utility/StringConnverter/StringConverter.h"


namespace
{
    auto const fileName = "ModelDataLoader.cpp";
}

MeshContext::ModelCreator::ModelDataLoader::ModelDataLoader(MeshContext::InstanceKey key_)
{
    Logger::Entry("ModelDataLoader: Constructor");


	modelDataCache.reset(new ModelDataCache(key_));
    Logger::Log("Instantiate: ModelDataCache",fileName);

    Logger::End("ModelDataLoader: Constructor");
}

MeshContext::ModelCreator::ModelDataLoader::~ModelDataLoader()
{

}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelDataAggregate* MeshContext::ModelCreator::ModelDataLoader::Load(std::string fileName_ , std::string filePath_)
{
    std::unique_ptr<ModelDataAggregate> modelDataAggregate = std::make_unique<ModelDataAggregate>();

	///キャッシュにあるか確認
	ModelDataAggregate* cachedModelData = modelDataCache->FindDuplication(ModelDataCache::AccessKey{},fileName_);
    if (cachedModelData)
    {
        Logger::Log("Cache Hit: " + fileName_, fileName);
        return cachedModelData;
    }
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
        ParseMesh(modelDataAggregate->resourceMesh[i], pMesh);
    }

    //マテリアルのメモリを確保
    modelDataAggregate->resourceMaterial.clear();
    if(scene)modelDataAggregate->resourceMaterial.resize(scene->mNumMaterials);

    //マテリアルデータを変換
    for (size_t i = 0; i < modelDataAggregate->resourceMaterial.size(); ++i)
    {
        const auto pMaterial = scene->mMaterials[i];
        ParseMaterial(modelDataAggregate->resourceMaterial[i], pMaterial);
    }

    //キャッシュデータに登録
    auto returnPtr = modelDataAggregate.get();
    modelDataCache->Register(MeshContext::ModelCreator::ModelDataLoader::ModelDataCache::AccessKey{}, fileName_, std::move(modelDataAggregate));

    //不要になったのでクリア
    importer.FreeScene();
    scene  = nullptr;

    Logger::Log("Complete: Loading " + fileName_, fileName);

    return returnPtr;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshContext::ModelCreator::ModelDataLoader::ParseMesh(ResourceMesh& dstMesh_, const aiMesh* pSrcMesh_)
{
    //マテリアル番号を設定
    //dstMesh.materialId = pSrcMesh->mMaterialIndex;

    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    std::vector<uint32_t> originalIndices;

    //頂点データのメモリを確保
    dstMesh_.vertices.resize(pSrcMesh_->mNumVertices);

    for (auto i = 0u; i < pSrcMesh_->mNumVertices; ++i)
    {
        auto pPosition = &(pSrcMesh_->mVertices[i]);
        auto pNormal = &(pSrcMesh_->mNormals[i]);
        auto pTexCoord = (pSrcMesh_->HasTextureCoords(0)) ? &(pSrcMesh_->mTextureCoords[0][i]) : &zero3D;
        auto pTangent = (pSrcMesh_->HasTangentsAndBitangents()) ? &(pSrcMesh_->mTangents[i]) : &zero3D;

        dstMesh_.vertices[i] = StandardVertex
        (
            Vector3(pPosition->x, pPosition->y, pPosition->z),
            Vector3(pNormal->x, pNormal->y, pNormal->z),
            Vector3(pTangent->x, pTangent->y, pTangent->z),
            Vector2(pTexCoord->x, 1.0f - pTexCoord->y)

        );
    }


    //頂点インデックスのメモリを確保
    originalIndices.resize(pSrcMesh_->mNumFaces * 3);

    for (auto i = 0u; i < pSrcMesh_->mNumFaces; ++i)
    {
        const auto& face = pSrcMesh_->mFaces[i];
        ErrorMessageOutput::Assert::DetectError(face.mNumIndices == 3, "頂点が3じゃない", fileName);

        originalIndices[i * 3 + 0] = face.mIndices[0];
        originalIndices[i * 3 + 1] = face.mIndices[1];
        originalIndices[i * 3 + 2] = face.mIndices[2];
    }

    //最適化
    {
        std::vector<uint32_t> remapIndices(originalIndices.size());

        //重複データを再マップするための再マッピング用インデックスを生成
        auto vertexCnt = meshopt_generateVertexRemap
        (
            remapIndices.data(),
            originalIndices.data(),
            originalIndices.size(),
            dstMesh_.vertices.data(),
            dstMesh_.vertices.size(),
            sizeof(StandardVertex)
        );

        std::vector<StandardVertex> vertices(vertexCnt);
        std::vector<uint32_t> indicesBuf(originalIndices.size());


        //頂点インデックスを再マッピング
        meshopt_remapIndexBuffer(
            indicesBuf.data(),
            originalIndices.data(),
            originalIndices.size(),
            remapIndices.data()
        );

        //頂点データを再マッピング
        meshopt_remapVertexBuffer(
            vertices.data(),
            dstMesh_.vertices.data(),
            dstMesh_.vertices.size(),
            sizeof(StandardVertex),
            remapIndices.data());


        //最適化したサイズにメモリ量を減らす
        dstMesh_.vertices.resize(vertices.size());
        originalIndices = std::move(indicesBuf);

        //頂点キャッシュ最適化
        meshopt_optimizeVertexCache
        (
            originalIndices.data(),
            originalIndices.data(),
            originalIndices.size(),
            vertexCnt
        );

        //頂点フェッチ最適化
        size_t optimizedVertexCount = meshopt_optimizeVertexFetch
(
            dstMesh_.vertices.data(),
            originalIndices.data(),
            originalIndices.size(),
            vertices.data(),
            vertices.size(),
            sizeof(StandardVertex)
        );

        //頂点フェッチ最適化後の実際の頂点数へ縮小
        dstMesh_.vertices.resize(optimizedVertexCount);
    }

    //メッシュレット生成
    //メッシュレットの自動分割と10bitパッキング
    {
        //ハードウェア（Mesh Shader）の制約条件。
        //一般的な現代のGPUアーキテクチャに最適化するため、
        ///1つのメッシュレットに含まれる最大頂点数を「64」、最大三角形数を「124〜126」に設定
        const size_t kMaxVertices = 64;
        const size_t kMaxPrimitives = 126;
        const float  kConeWeight = 0.0f; //カリング用のコーン計算の重み（今回は不使用なので0）

        //分割後に生成されるメッシュレットの「理論上の最大上限数」をあらかじめ計算
        size_t max_meshlets = meshopt_buildMeshletsBound(originalIndices.size(), kMaxVertices, kMaxPrimitives);

        //テンポラリ出力バッファ
        std::vector<meshopt_Meshlet> temp_meshlets(max_meshlets);
        std::vector<unsigned int>    temp_meshlet_vertices(max_meshlets * kMaxVertices);
        std::vector<unsigned char>   temp_meshlet_triangles(max_meshlets * kMaxPrimitives * 3);

        //メッシュレット分割
        //最適化済みの頂点バッファverticesから、座標データの先頭ポインタとバイトサイズを渡すことで、
        //空間的な局所性を考慮したクラスター分割アルゴリズムが実行される
        size_t meshletCount = meshopt_buildMeshlets
        (
            temp_meshlets.data(),
            temp_meshlet_vertices.data(),
            temp_meshlet_triangles.data(),
            originalIndices.data(),
            originalIndices.size(),
            &dstMesh_.vertices[0].localPos.data.x, //頂点データの座標ポインタの先頭
            dstMesh_.vertices.size(),
            sizeof(StandardVertex),                //頂点構造体1つあたりのバイトサイズ
            kMaxVertices,
            kMaxPrimitives,
            kConeWeight
        );

        ErrorMessageOutput::Assert::DetectError(meshletCount > 0, "meshletCountがおかしいです", fileName);

        //実際に生成された確定数に合わせてメタデータ配列をリサイズ
        temp_meshlets.resize(meshletCount);

        //最後のメッシュレットのオフセットを参照することで実際に使われた正確な要素数が割り出せる
        const meshopt_Meshlet& last_meshlet = temp_meshlets.back();
        size_t total_unique_vertices = last_meshlet.vertex_offset + last_meshlet.vertex_count;
        size_t total_primitive_triangles = last_meshlet.triangle_offset + last_meshlet.triangle_count;

        dstMesh_.meshlets.resize(meshletCount);
        dstMesh_.uniqueVertexIndices.reserve(total_unique_vertices);
        dstMesh_.primitiveIndices.reserve(total_primitive_triangles);


        //ResourceMeshに詰める
        for (size_t i = 0; i < meshletCount; ++i)
        {
            const meshopt_Meshlet& src = temp_meshlets[i];
            StructuredBufferDataDefinition::MeshletCPUGPU& dstMeshlet = dstMesh_.meshlets[i];

            //各スレッドグループが担当する箇所を算出
            dstMeshlet.vertexOffset = static_cast<uint32_t>(dstMesh_.uniqueVertexIndices.size());
            dstMeshlet.vertexCnt = src.vertex_count;
            dstMeshlet.primitiveOffset = static_cast<uint32_t>(dstMesh_.primitiveIndices.size());
            dstMeshlet.primitiveCnt = src.triangle_count;

            //インデックスを0～に対応付ける
            for (unsigned int v = 0; v < src.vertex_count; ++v)
            {
                uint32_t global_vertex_idx = temp_meshlet_vertices[src.vertex_offset + v];
                dstMesh_.uniqueVertexIndices.emplace_back(StructuredBufferDataDefinition::UniqueVertexIndexCPUGPU(global_vertex_idx));
            }

            //ポリゴン頂点情報をパッキング
            for (unsigned int t = 0; t < src.triangle_count; ++t)
            {
                size_t prim_base_idx = src.triangle_offset + t * 3;

                StructuredBufferDataDefinition::PrimitiveIndexCPUGPU tris = {};

                tris.index2 = temp_meshlet_triangles[prim_base_idx + 0];
                tris.index0 = temp_meshlet_triangles[prim_base_idx + 1];
                tris.index1 = temp_meshlet_triangles[prim_base_idx + 2];
                tris.reserved = 0;

                dstMesh_.primitiveIndices.push_back(tris);
            }
        }

        //最終メモリの最適化
        dstMesh_.uniqueVertexIndices.shrink_to_fit();
        dstMesh_.primitiveIndices.shrink_to_fit();
        dstMesh_.meshlets.shrink_to_fit();

    }
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshContext::ModelCreator::ModelDataLoader::ParseMaterial(ResourceMaterial& dstMaterial_, const aiMaterial* pSrcMaterial_)
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

///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::wstring MeshContext::ModelCreator::ModelDataLoader::Convert(const aiString& path)
{
    wchar_t temp[256] = {};
    size_t  size;
    mbstowcs_s(&size, temp, path.C_Str(), 256);
    return std::wstring(temp);
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
