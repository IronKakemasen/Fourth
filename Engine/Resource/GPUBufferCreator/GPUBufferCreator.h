#pragma once
#include "../BufferDescriptions/BufferDescriptionBehavior.h"

class WinApp;

//Description
struct ColorBufferDescription;
struct ConstantBufferDescription;
struct SRV_UAVBufferDescription;

//Buffer
class ConstantBuffer;
class ColorBuffer;
class SRV_UAVBuffer;

class GPUBufferCreator
{
private:

	using CreateColorBufferCommand = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ColorBufferDescription&)>;
	using CreateConstantBufferCommand = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const ConstantBufferDescription&)>;
	using CreateSRV_UAVBufferCommand = std::function<Microsoft::WRL::ComPtr<ID3D12Resource>(const SRV_UAVBufferDescription&)>;

public:

	//自身のインスタンス化キー
	struct InstanceKey;

	GPUBufferCreator(InstanceKey instanceKey_);
	~GPUBufferCreator();

	//外部クラスが作ったコマンドをセットする
	void SetCommands
	(
		const CreateColorBufferCommand& createColorBufferCommand_,
		const CreateConstantBufferCommand& createConstantBufferCommand_,
		const CreateSRV_UAVBufferCommand& createSRV_UAVBufferCommand_
	);

	//一括窓口
	template<typename BufferType,typename DescType>
	[[nodiscard]] std::unique_ptr<BufferType> CreateBuffer(std::unique_ptr<BufferDescriptionBehavior>&& desc_, const std::string& name_)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> resource1, resource2;

		//descriptionの中身が書き込まれているかチェック
		CheckDescription(*desc_.get());

		//名前を分かりやすい形に変換
		std::string convName = NameConverter<BufferType>(name_);
		Log(convName);

		//生成
		return std::move(CreateSpecificBuffer<BufferType, DescType>(std::move(desc_), convName, std::move(resource1), std::move(resource2)));
	}


private:

	//コマンド群
	CreateConstantBufferCommand createConstantBufferCommand;
	CreateColorBufferCommand createColorBufferCommand;
	CreateSRV_UAVBufferCommand createSRV_UAVBufferCommand;

	//引数のDescriptionに不備がないかチェックしてエラーを吐く
	void CheckDescription(const BufferDescriptionBehavior& srcDesc_);

	//ヘルパー関数
	template <typename BufferType, typename DescType>
	std::unique_ptr<BufferType> CreateSpecificBuffer(std::unique_ptr<DescType>&& desc_, const std::string& name_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource1_, Microsoft::WRL::ComPtr<ID3D12Resource>&& resource2_);

	template <typename BufferType>
	std::string NameConverter(const std::string& name_) = delete;

	void Log(std::string convName_);

};

template <>
std::string GPUBufferCreator::NameConverter<ConstantBuffer>(const std::string& name_);

template <>
std::string GPUBufferCreator::NameConverter<ColorBuffer>(const std::string& name_);

template <>
std::string GPUBufferCreator::NameConverter<SRV_UAVBuffer>(const std::string& name_);


struct GPUBufferCreator::InstanceKey
{

private:

	friend class WinApp;
	explicit InstanceKey() = default;
};
