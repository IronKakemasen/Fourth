#pragma once
#include "Vertex/StandardVertex.h"
#include "Meshlet/Meshlet.h"


struct ResourceMesh
{
	std::vector<StandardVertex> vertices;
	std::vector<uint32_t> indices;

    //メッシュレット
    std::vector<Meshlet> meshlets;
    //ユニーク頂点インデックス(threadGroupの総数でもある)
    std::vector<uint32_t> uniqueVertexIndices;
    //プリミティブインデックス
    std::vector<PrimitiveIndex> primitiveIndices;

};

