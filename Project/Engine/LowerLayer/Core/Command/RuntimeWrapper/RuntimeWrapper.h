#pragma once
#include "../CommandContext.h"


class CommandContext::RuntimeWrapper
{

	ID3D12GraphicsCommandList6* cmdList;

public:

	RuntimeWrapper(ID3D12GraphicsCommandList6* cmdList_);


	__forceinline void SetGraphicsRootSignature(ID3D12RootSignature* rootSinganature_)
	{
		cmdList->SetGraphicsRootSignature(rootSinganature_);
	}

	__forceinline void SetPipelineState(ID3D12PipelineState* pipelineState_)
	{
		cmdList->SetPipelineState(pipelineState_);
	}

	__forceinline void DispatchMesh(UINT x_, UINT y_, UINT z_)
	{
		cmdList->DispatchMesh(x_, y_, z_);
	}

	__forceinline void OMSetRenderTargets
	(
		_In_ UINT numRTV_,
		_In_opt_ const D3D12_CPU_DESCRIPTOR_HANDLE* rtvCPUHandles_,
		_In_ BOOL RTsSingleHandleToDescriptorRange_,
		_In_opt_ const D3D12_CPU_DESCRIPTOR_HANDLE* dsvCPUHandle_
	)
	{
		cmdList->OMSetRenderTargets(numRTV_, rtvCPUHandles_, RTsSingleHandleToDescriptorRange_, dsvCPUHandle_);
	}

	__forceinline void ClearDepthStencilView
	(
		_In_ D3D12_CPU_DESCRIPTOR_HANDLE dsvCPUHandle_,
		_In_ D3D12_CLEAR_FLAGS clearFlags_,
		_In_ FLOAT clearColor_,
		_In_ UINT8 stencil_,
		_In_ UINT numRects_,
		_In_reads_(numRects_)  const D3D12_RECT* pRects_
	)
	{
		cmdList->ClearDepthStencilView(dsvCPUHandle_, clearFlags_, clearColor_, stencil_, numRects_, pRects_);
	}

	__forceinline void ClearRenderTargetView
	(
		_In_  D3D12_CPU_DESCRIPTOR_HANDLE rtvCPUHandle_,
		_In_  const FLOAT clearColor_[4],
		_In_  UINT numRects_,
		_In_reads_(numRects_)  const D3D12_RECT* pRects_
	) 
	{
		cmdList->ClearRenderTargetView(rtvCPUHandle_, clearColor_, numRects_, pRects_);
	}

	__forceinline void SetDescriptorHeaps(_In_ UINT numDescriptorHeaps_, _In_reads_(numDescriptorHeaps_) ID3D12DescriptorHeap* const* ppDescriptorHeaps_)
	{
		cmdList->SetDescriptorHeaps(numDescriptorHeaps_, ppDescriptorHeaps_);
	}

	__forceinline void RSSetViewports
	(
		_In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT numViewports_,
		_In_reads_(numViewports_)  const D3D12_VIEWPORT* pViewports_
	)
	{
		cmdList->RSSetViewports(numViewports_, pViewports_);
	}

	__forceinline void RSSetScissorRects
	(
		_In_range_(0, D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE)  UINT numRects_,
		_In_reads_(numRects_)  const D3D12_RECT* pRects_
	)
	{
		cmdList->RSSetScissorRects(numRects_, pRects_);
	}

	__forceinline void SetGraphicsRoot32BitConstants
	(
		_In_ UINT rootParameterIndex_,
		_In_ UINT num32BitValuesToSet_,
		_In_reads_(num32BitValuesToSet_) const void* pSrcData_,
		_In_ UINT destOffsetIn32BitValues_
	)
	{
		cmdList->SetGraphicsRoot32BitConstants(rootParameterIndex_, num32BitValuesToSet_, pSrcData_, destOffsetIn32BitValues_);
	}

	__forceinline void SetGraphicsRoot32BitConstant
	(
		_In_ UINT rootParameterIndex_,
		_In_ UINT srcData_,
		_In_ UINT destOffsetIn32BitValues_
	)
	{
		cmdList->SetGraphicsRoot32BitConstant(rootParameterIndex_, srcData_, destOffsetIn32BitValues_);
	}

	__forceinline void IASetPrimitiveTopology(_In_ D3D12_PRIMITIVE_TOPOLOGY primitiveTopology_)
	{
		cmdList->IASetPrimitiveTopology(primitiveTopology_);
	}

	__forceinline void ResourceBarrier
	(
		_In_ UINT numBarriers_,
		_In_reads_(numBarriers_) const D3D12_RESOURCE_BARRIER* pBarriers_
	)
	{
		if (numBarriers_ > 0)
		{
			cmdList->ResourceBarrier(numBarriers_, pBarriers_);
		}
	}

	__forceinline void SetComputeRootSignature(ID3D12RootSignature* rootSignature_)
	{
		cmdList->SetComputeRootSignature(rootSignature_);
	}

	__forceinline void SetComputeRootDescriptorTable(UINT rootParameterIndex_, D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor_)
	{
		cmdList->SetComputeRootDescriptorTable(rootParameterIndex_, baseDescriptor_);
	}

	__forceinline void SetComputeRootConstantBufferView(UINT rootParameterIndex_, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation_)
	{
		cmdList->SetComputeRootConstantBufferView(rootParameterIndex_, bufferLocation_);
	}

	__forceinline void Dispatch(UINT threadGroupCountX_, UINT threadGroupCountY_, UINT threadGroupCountZ_)
	{
		cmdList->Dispatch(threadGroupCountX_, threadGroupCountY_, threadGroupCountZ_);
	}

	__forceinline void SetGraphicsRootDescriptorTable
	(
		_In_ UINT rootParameterIndex_,
		_In_ D3D12_GPU_DESCRIPTOR_HANDLE baseDescriptor_
	)
	{
		cmdList->SetGraphicsRootDescriptorTable(rootParameterIndex_, baseDescriptor_);
	}
};


