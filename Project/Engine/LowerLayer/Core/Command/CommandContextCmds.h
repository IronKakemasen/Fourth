#pragma once

namespace CommandContextCmds
{
	//テクスチャバッファ以外のアップロードコマンド
	using UploadBufferCommand = std::function<void
	(
		ID3D12Resource* dstResource_,
		ID3D12Resource* intermediateResource_,
		const D3D12_SUBRESOURCE_DATA* subeResource_,
		UINT subResourceCount_
	)>;

	//バリアを張るコマンド
	using PitchBarrierCommand = std::function<void(D3D12_RESOURCE_BARRIER*, UINT)>;
}

