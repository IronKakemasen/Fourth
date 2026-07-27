#pragma once
#include "../../../../../../../Assets/Shared/StructuredBuffer.h"
#include "StandardVertex.h"


struct ResourceMesh
{
    //頂点情報の原本
	std::vector<StandardVertex> vertices;
    ///元の頂点番号への対応表
    std::vector<StructuredBufferDataDefinition::UniqueVertexIndexCPUGPU> uniqueVertexIndices;
    //1スレッドグループが処理する頂点・三角形の範囲情報
    std::vector<StructuredBufferDataDefinition::MeshletCPUGPU> meshlets;
    ///3つのローカル頂点番号を保持する三角形インデックス。パッキングされている
    std::vector<StructuredBufferDataDefinition::PrimitiveIndexCPUGPU> primitiveIndices;

};

