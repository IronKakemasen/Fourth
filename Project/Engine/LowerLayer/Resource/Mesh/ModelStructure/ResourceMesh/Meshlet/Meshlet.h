#pragma once

struct Meshlet
{
	//頂点番号オフセット
	uint32_t vertexOffset;
	//頂点数
	uint32_t vertexCnt;
	//プリミティブ番号オフセット
	uint32_t primitiveOffset;
	//プリミティブオフセット
	uint32_t primitiveCnt;
};

struct PrimitiveIndex
{
	uint32_t index0 : 10;
	uint32_t index1 : 10;
	uint32_t index2 : 10;
	uint32_t reserved : 2;
};


