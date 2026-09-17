#pragma once
#include "../ModelSlotAllocator.h"


//外部
#include "../../../../../../../Assets/Shared/StructuredBufferModelData.h"


class ModelContext::ModelSlotAllocator::ModelDataLibrary
{
	template<typename DataType>
	struct DataTypeTraits;


public:

	ModelDataLibrary(NexusFieldProof proof_);

	//モデルファイル名に対してデータを紐づける
	template<typename DataType>
	void Link
	(
		std::string modelFileName_,
		std::vector<DataType> const& data_
	)
	{
		auto& lib = std::get<std::unordered_map<std::string, std::vector<DataType>>>(libTuple);

		if constexpr (std::is_same_v<DataType, MeshDataID>)
		{
			ErrorMessageOutput::Assert::DetectError(data_.size() > 0, "中身すっからかんやん！", "ModelDataLibrary.h");
		}

		lib[modelFileName_] = data_;

		Logger::Log("Register: " + modelFileName_ + DataTypeTraits<DataType>::kName, "ModelDataLibrary.h");
	}

	//検索
	template<typename DataType>
	[[nodiscard]] std::vector<DataType> const& Find(std::string fileName_)const
	{
		auto const& lib = std::get<std::unordered_map<std::string, std::vector<DataType>>>(libTuple);

		ErrorMessageOutput::Assert::DetectError
		(
			lib.find(fileName_) != lib.end(),
			"そないなキーはありません",
			"ModelDataLibrary.h"
		);

		return lib.at(fileName_);
	}

	//ライブラリーの中身をログファイルに出力
	void Log()const;


private:


	///モデルファイル名から、サブメッシュまで含んだ情報を索引する
	std::tuple
	<
		///「メッシュデータバッファのsrvHeapIndexが詰まったもの」の配列の何番目に該当するのかを索引するため
		std::unordered_map<std::string, std::vector<MeshDataID>>,
		//モデルファイルから仕入れたマテリアル情報
		std::unordered_map<std::string, std::vector<StructuredBufferModelData::MaterialCPU>>
	>libTuple;


};

template<>
struct ModelContext::ModelSlotAllocator::ModelDataLibrary::DataTypeTraits<MeshDataID>
{
	static inline const std::string kName = "MeshDataID";
};

template<>
struct ModelContext::ModelSlotAllocator::ModelDataLibrary::DataTypeTraits<StructuredBufferModelData::MaterialCPU>
{
	static inline const std::string kName = "MaterialCPU";
};


