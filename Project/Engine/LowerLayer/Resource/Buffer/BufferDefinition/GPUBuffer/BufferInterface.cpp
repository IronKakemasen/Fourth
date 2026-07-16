#include "BufferInterface.h"

D3D12_RESOURCE_STATES IColorBuffer::ResourceStateTable(Usage usage_)const
{
	static D3D12_RESOURCE_STATES resourceStatetable[2]
	{
		D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	};

	return resourceStatetable[(int)usage_];
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_STATES IDepthBuffer::ResourceStateTable(Usage usage_)const
{
	static D3D12_RESOURCE_STATES resourceStateTable[2]
	{
		D3D12_RESOURCE_STATE_DEPTH_READ | D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_DEPTH_WRITE
	};

	return resourceStateTable[(int)usage_];
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3D12_RESOURCE_STATES IRWStructuredBuffer::ResourceStateTable(Usage usage_)const
{
	static D3D12_RESOURCE_STATES resourceStateTable[2]
	{
		D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_UNORDERED_ACCESS
	};

	return resourceStateTable[(int)usage_];
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IRenderTargetBuffer::Swap()
{
	static IRenderTargetBuffer::Status nextTable[3]
	{
		kShaderResource_RenderTarget,
		kRenderTarget_ShaderResource,
		kSingle
	};

	status = nextTable[status];
}

int IRenderTargetBuffer::ProperBufferIndex(Usage usage_)const
{
	//シングルバッファは問答無用
	if (status == kSingle) return 0;

	int dstBufferIndex{};

	//使用目的が読み込みの場合
	if (usage_ == Usage::kRead)
	{
		//2番目がシェーダーリソース
		if (status == kRenderTarget_ShaderResource) dstBufferIndex = 1;
	}
	//使用目的が書き込みの場合
	else
	{
		//2番目がレンダーターゲット
		if (status == kShaderResource_RenderTarget) dstBufferIndex = 1;
	}

	return dstBufferIndex;
}

void IRenderTargetBuffer::SynchronizeStatus(ProjectConfig::Render::NumBuffer numBuffer_)
{
	(numBuffer_ == ProjectConfig::Render::NumBuffer::kSingleBuffer) ? status = kSingle : status = kRenderTarget_ShaderResource;
}
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IComputeBuffer::Swap()
{
	static IComputeBuffer::Status nextTable[3]
	{
		kShaderResource_ComputeResource,
		kComputeResource_ShaderResource,
		kSingle
	};

	status = nextTable[status];

}

int IComputeBuffer::ProperBufferIndex(Usage usage_)const
{
	//シングルバッファは問答無用
	if (status == kSingle) return 0;

	int dstBufferIndex{};

	//使用目的が読み込みの場合
	if (usage_ == Usage::kRead)
	{
		//2番目がシェーダーリソース
		if (status == kComputeResource_ShaderResource) dstBufferIndex = 1;
	}
	//使用目的が書き込みの場合
	else
	{
		//2番目が計算リソース
		if (status == kShaderResource_ComputeResource) dstBufferIndex = 1;
	}

	return dstBufferIndex;
}

void IComputeBuffer::SynchronizeStatus(ProjectConfig::Render::NumBuffer numBuffer_)
{
	(numBuffer_ == ProjectConfig::Render::NumBuffer::kSingleBuffer) ? status = kSingle : status = kComputeResource_ShaderResource;
}
