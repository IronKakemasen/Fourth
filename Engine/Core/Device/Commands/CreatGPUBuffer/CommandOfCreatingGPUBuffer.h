#pragma once

struct BufferDescriptionTypeA;
struct BufferDescriptionTypeB;


//各Typeのバッファを作る関数群
class CommandOfCreatingGPUBuffer
{
	//TypeAのバッファを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateResourceTypeA(ID3D12Device8* device_, 
		const BufferDescriptionTypeA& typeA_Desc_);
	//TypeBのバッファを作る
	[[nodiscard]] Microsoft::WRL::ComPtr<ID3D12Resource> CreateResourceTypeB(ID3D12Device8* device_, 
		const BufferDescriptionTypeB& typeB_Desc_);
};

