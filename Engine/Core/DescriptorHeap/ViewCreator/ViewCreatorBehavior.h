#pragma once



class ViewCreatorBehavior
{

protected:
	//ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap = nullptr;
	//最大領域分割数
	uint16_t maxDescriptorNum{};
	//viewの生成数
	uint32_t currentCreateNum{};
	//ディスクリプターサイズ
	uint32_t sizeOfDescriptor{};


};

