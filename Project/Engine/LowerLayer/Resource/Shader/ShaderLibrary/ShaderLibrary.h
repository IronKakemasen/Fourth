#pragma once
#include "../ShaderContext.h"


class ShaderContext::ShaderLibrary
{
public:
	ShaderLibrary(NexusFieldProof proof_);

	///シェーダーバイナリオブジェのポインタを輸出
	IDxcBlob* Export(std::string fileName_);
	//輸入
	void Import(NexusFieldProof proof_, const std::string& fileName_, Microsoft::WRL::ComPtr<IDxcBlob>&& data_);

private:
	///本元データ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<IDxcBlob>> data;



};

