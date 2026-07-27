#pragma once
#include "../ModelSlotAllocator.h"

class ModelContext::ModelSlotAllocator::MeshDataIDLibrary
{
public:

	MeshDataIDLibrary(NexusFieldProof proof_);

	//メッシュファイル名に対してMeshDataID(複数)を紐づける
	void LinkModelFileNameToMeshDataID
	(
		std::string modelFileName_,
		const std::vector<MeshDataID>& idContainer_
	);

	//ライブラリーの中身をログファイルに出力
	void Log()const;

	//検索
	[[nodiscard]] const std::vector<MeshDataID>& Find(std::string fileName_)const;

private:

	///そのモデルファイル名が、
	///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
	std::unordered_map<std::string, std::vector<MeshDataID>> meshDataIDLib;

};

