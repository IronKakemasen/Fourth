#pragma once
#include "../RootSignatureContext.h"


class RootSignatureLibrary
{
public:
	enum class Usage
	{
		kGraphics,
		kCompute
		,kCount
	};


	struct InstanceKey;
	//データアドレスのアクセス権
	struct DataPtrAccesskey;

	RootSignatureLibrary(InstanceKey key_, RootSignatureContext::Assembler* assembler_);
	~RootSignatureLibrary();


	///シェーダーバイナリオブジェのポインタを渡す
	ID3D12RootSignature* Export(DataPtrAccesskey key_, Usage usage_);

private:
	///本元データ
	std::array<Microsoft::WRL::ComPtr<ID3D12RootSignature>, (int)Usage::kCount> data;

	///ルートシグネチャを生成する
	void CreateAllRootSignatures(RootSignatureContext::Assembler* assembler_);

};


struct RootSignatureLibrary::InstanceKey
{
private:

	friend class RootSignatureContext;
	explicit InstanceKey() = default;
};

struct RootSignatureLibrary::DataPtrAccesskey
{
private:

	explicit DataPtrAccesskey() = default;
};
