#pragma once
#include "../../PSO/PSO_Context.h"

class ShaderContext;


class ShaderLibrary
{
public:

	enum class MS
	{
		kStatic_Basic			//特別な頂点処理なし、用途:基本



		,kCount
	};

	enum class PS
	{
		kStandard_kBasic		//特別なピクセル処理なし。用途：基本

		, kCount
	};

	struct ImportKey;
	struct GetDataKey;

	ShaderLibrary(ImportKey importKey_);

	//生成したシェーダーのバイナリオブジェを輸入
	template<typename ShaderType>
	void Import
	(
		ImportKey key_,
		Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
		ShaderType type_
	);

	//シェーダーバイナリオブジェのポインタを輸出
	template<typename ShaderType>
	IDxcBlob* Export
	(
		GetDataKey key_,
		ShaderType meshType_
	);


private:
	Microsoft::WRL::ComPtr<IDxcBlob> meshShaderData[(int)MS::kCount];
	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderData[(int)PS::kCount];

};


struct ShaderLibrary::ImportKey
{
private:

	friend class ShaderContext;
	explicit ImportKey() = default;
};

struct ShaderLibrary::GetDataKey
{
private:
	//friend class PSO_Context::Assembler;
	explicit GetDataKey() = default;
};


template<>
void ShaderLibrary::Import
(
	ImportKey key_,
	Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
	MS type_
);

template<>
void ShaderLibrary::Import
(
	ImportKey key_,
	Microsoft::WRL::ComPtr<IDxcBlob>&& data_,
	PS type_
);

template<>
IDxcBlob* ShaderLibrary::Export
(
	GetDataKey key_,
	MS meshType_
);

template<>
IDxcBlob* ShaderLibrary::Export
(
	GetDataKey key_,
	PS meshType_
);
