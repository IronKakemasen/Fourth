#pragma once
#include "GPUBufferBehavior.h"


//使用目的
enum class Usage
{
	kRead,
	kWrite
};


//ピンポンバッファインターフェース
struct IPingPongBuffer
{
	virtual ~IPingPongBuffer() = default;

	//内部の役割をスワップさせる
	virtual void Swap() = 0;
	//ステートを同期させる
	virtual void SynchronizeStatus(ProjectConfig::Render::NumBuffer numBuffer_) = 0;
	//バリアを生成仮想関数
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) = 0;

protected:

	//使用法に応じて、適切にバッファのインデックスを出す
	virtual int ProperBufferIndex(Usage usage_)const = 0;
};

struct IDualRole
{
	virtual D3D12_RESOURCE_STATES ResourceStateTable(Usage usage_)const = 0;
};

//シェーダーバッファのインターフェース
struct IShaderBuffer
{
	virtual uint32_t OutProperSRVHeapIndex(int frameIndex_ = 0)const = 0;
};

//CSバッファのインターフェース
struct IRWStructuredBuffer:IDualRole
{
	virtual uint32_t OutProperUAVHeapIndex()const = 0;

protected:
	virtual D3D12_RESOURCE_STATES ResourceStateTable(Usage usage_)const override;
};


//ディプスバッファのインターフェース
struct IDepthBuffer:IDualRole
{
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperDSVHeapHandle()const = 0;
protected:
	virtual D3D12_RESOURCE_STATES ResourceStateTable(Usage usage_)const override;

};

//カラーバッファインターフェース
struct IColorBuffer:IDualRole
{
	virtual ~IColorBuffer() = default;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperRTVHeapHandle()const = 0;
protected:
	virtual D3D12_RESOURCE_STATES ResourceStateTable(Usage usage_)const override;
};



///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///コンピュートバッファ専用のインターフェース
struct IComputeBuffer:IPingPongBuffer
{
private:

	//内部ステータス
	enum Status
	{
		kComputeResource_ShaderResource,
		kShaderResource_ComputeResource,
		kSingle
	}status = kComputeResource_ShaderResource;

public:

	virtual ~IComputeBuffer() = default;
	virtual void Swap()override;
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) = 0;

protected:

	virtual int ProperBufferIndex(Usage usage_)const override;
	virtual void SynchronizeStatus(ProjectConfig::Render::NumBuffer numBuffer_)override;

};
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////
///カラーバッファやディプスバッファなどのテクスチャに対して書き込みを行うもの
struct IRenderTargetBuffer:IPingPongBuffer
{
private:

	//内部ステータス
	enum Status
	{
		kRenderTarget_ShaderResource,
		kShaderResource_RenderTarget,
		kSingle
	}status = kSingle;

public:

	virtual ~IRenderTargetBuffer() = default;

	//適切なClearColor出す
	virtual D3D12_RESOURCE_BARRIER CreateBarrier(Usage usage_) = 0;
	virtual void Swap()override;

protected:

	virtual int ProperBufferIndex(Usage usage_)const override;
	virtual void SynchronizeStatus(ProjectConfig::Render::NumBuffer numBuffer_)override;
};


