#pragma once
#include "GPUBufferBehavior.h"

//ピンポンバッファ専用
struct IRWBuffer
{
	virtual ~IRWBuffer() = default;

	//各バッファが自身のバリアを適切に張るためのバリアを生成仮想関数
	virtual std::array<D3D12_RESOURCE_BARRIER, ProjectConfig::Render::kRequiredGPUBufferSum>
		CreateNextStepBarriers(GPUBufferBehavior::ExtractMaterialKey key_) = 0;
	//内部の役割をスワップさせる
	virtual void Swap() = 0;
};

//読み込みバッファのインターフェース
struct IShaderBuffer
{
	virtual ~IShaderBuffer() = default;

	//ダブルバッファのうち適切な方のバッファからインデックスを出す
	virtual uint32_t OutProperSRV_UAVHeapIndex()const = 0;
	//適切な方のバッファからFormat出す(テクスチャとして利用する場合)
	virtual DXGI_FORMAT OutProperSRVFormat()const = 0;

};

//カラーバッファやディプスバッファなどのテクスチャに対して書き込みを行うもの
struct IRenderTargetBuffer
{
	virtual ~IRenderTargetBuffer() = default;
	//ダブルバッファのうち適切な方のバッファからCPUインデックスを出す
	virtual D3D12_CPU_DESCRIPTOR_HANDLE OutProperCPUHandle()const = 0;
	//適切な方のバッファからFormat出す
	virtual DXGI_FORMAT OutProperRenderTargetFormat()const = 0;
	//適切な方のバッファからClearColor出す
	virtual std::array<float, 4> OutProperClearColor()const = 0;
};


//ほぼカラーバッファ専用インターフェース
struct IColorBuffer
{
	virtual ~IColorBuffer() = default;
	//描画パイプラインに必要な行列を出す
	std::pair<D3D12_VIEWPORT, D3D12_RECT> OutMatrix()const;
	//行列を組み立てる
	void AssembleMatrix(UINT width_, UINT height_);

protected:

	//ビューポート行列
	D3D12_VIEWPORT viewport;
	//シザーレクト行列
	D3D12_RECT scissorRect;

};
