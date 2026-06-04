#pragma once
#include "../../Resource/BufferDescriptions/BufferDescriptionBehavior.h"

class WinApp;
struct ColorBufferDescription;
struct ConstantBufferDescription;
class ConstantBuffer;
class ColorBuffer;

class GPUBufferCreator
{
public:

	struct InstanceKey;

	GPUBufferCreator(InstanceKey instanceKey_);
	~GPUBufferCreator();

	//一括窓口
	template<typename BufferType,typename DescType>
	[[nodiscard]] std::unique_ptr<BufferType> CreateBuffer(const DescType& desc_, const std::string& name_)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1, resource2;

		//descriptionの中身が書き込まれているかチェック
		CheckDescription(desc_);

		//名前を分かりやすい形に変換
		std::string convName = NameConverter<BufferType>(name_);

		//生成
		return std::move(CallSpecificCreator<BufferType , DescType>(desc_, convName, std::move(resource1), std::move(resource2)));
	}


private:

	//引数のDescriptionに不備がないかチェックしてエラーを吐く
	void CheckDescription(const BufferDescriptionBehavior& srcDesc_);

	////コンスタントバッファ生成
	//[[nodiscard]] std::unique_ptr<ConstantBuffer> CreateConstantBuffer(const ConstantBufferDescription& desc_, const std::string& name_);
	////カラーバッファ生成
	//[[nodiscard]] std::unique_ptr<ColorBuffer> CreateColorBuffer(const ColorBufferDescription& desc_, const std::string& name_);

	//コマンド群
	std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)> createColorBuffer;
	std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)> createConstantBuffer;


	//ヘルパー関数
	template <typename BufferType, typename DescType>
	std::unique_ptr<BufferType> CallSpecificCreator(const DescType& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource> resource1_ , Microsoft::WRL::ComPtr<ID3D12Resource> resource2_);

	template <typename BufferType>
	std::string NameConverter(const std::string& name_) = delete;


};

template <>
std::string GPUBufferCreator::NameConverter<ConstantBuffer>(const std::string& name_);

template <>
std::string GPUBufferCreator::NameConverter<ColorBuffer>(const std::string& name_);

struct GPUBufferCreator::InstanceKey
{

private:

	friend class WinApp;
	explicit InstanceKey() = default;
};
