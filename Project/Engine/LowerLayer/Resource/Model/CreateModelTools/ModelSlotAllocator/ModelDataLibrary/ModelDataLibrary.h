#pragma once
#include "../ModelSlotAllocator.h"
#include "../../../ModelStructure/ModelData/ModelData.h"



class ModelContext::ModelSlotAllocator::ModelDataLibrary
{
public:

	ModelDataLibrary(NexusFieldProof proof_);

	//モデルファイル名に対してデータを紐づける
	template<typename DataType>
	void Link
	(
		std::string const& modelFileName_,
		std::vector<DataType> const& src_
	)
	{
		if constexpr (std::is_same_v<DataType, MeshDataID>)
		{
			ErrorMessageOutput::Assert::DetectError(src_.size() > 0, "メッシュデータの中身すっからかんやん！", "ModelDataLibrary.h");
			modelData[modelFileName_].meshDataID = src_;

		}
		else if constexpr (std::is_same_v<DataType, StructuredBufferModelData::MaterialCPU>)
		{
			modelData[modelFileName_].materialCPU = src_;

		}
		else if constexpr (std::is_same_v<DataType, size_t>)
		{
			ErrorMessageOutput::Assert::DetectError(src_.size() > 0, "メッシュデータの中身すっからかんやん！", "ModelDataLibrary.h");
			modelData[modelFileName_].meshletSize = src_;

		}

		Logger::Log("Register: " + modelFileName_ + ModelData::DataTypeTraits<DataType>::kName, "ModelDataLibrary.h");
	}

	auto const& Find(std::string const& fileName_)const
	{
		ErrorMessageOutput::Assert::DetectError
		(
			modelData.find(fileName_) != modelData.end(),
			"そないなキーはありません",
			"ModelDataLibrary.h"
		);

		return modelData.at(fileName_);
	}

	//ライブラリーの中身をログファイルに出力
	void Log()const;


private:


	///モデルファイル名から、サブメッシュまで含んだ情報を索引する
	std::unordered_map<std::string, ModelData> modelData;


};

