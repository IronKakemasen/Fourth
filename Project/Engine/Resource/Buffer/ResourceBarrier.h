#pragma once

namespace ResourceBarrier
{
	inline D3D12_RESOURCE_BARRIER Create
	(
		ID3D12Resource* dst_resource_,
		D3D12_RESOURCE_BARRIER_TYPE Type,
		D3D12_RESOURCE_BARRIER_FLAGS Flags,
		D3D12_RESOURCE_STATES before_,
		D3D12_RESOURCE_STATES after_,
		UINT transitionSubResource_
	)
	{
		D3D12_RESOURCE_BARRIER barrier{};

		//バリアの設定
		barrier.Type = Type;
		barrier.Flags = Flags;


		//バリアを張る対象のリソース。
		barrier.Transition.pResource = dst_resource_;
		barrier.Transition.Subresource = transitionSubResource_;

		//バリアステートを遷移
		barrier.Transition.StateBefore = before_;
		barrier.Transition.StateAfter = after_;

		return barrier;
	}

}