#pragma once
#include "../BufferDescriptionBehavior.h"


//読み書き
struct UploadStructuredBufferDescription final :public BufferDescriptionBehavior, IAssembleShaderResource
{
private:
	struct Param
	{
		UINT structureByte{};
		UINT numElements{};
		UINT firstElement = -1;

	}param;

public:

	UploadStructuredBufferDescription
	(
		UINT structureByte_,
		UINT numElements_,
		UINT firstElement_
	);

	//パラーメーターチェック
	virtual void CheckRequirementsFilled() const override;
	//リソースディスクの生成
	virtual D3D12_RESOURCE_DESC CreateResourceDesc()const override;
	//ヒーププロパティの生成
	virtual D3D12_HEAP_PROPERTIES CreateHeapProperties()const override;
	//SRVDesc生成
	virtual D3D12_SHADER_RESOURCE_VIEW_DESC CreateSRV_Desc()const override;

};



