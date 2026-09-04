#include "DescriptorHeapCreator.h"
#include "../DescriptorHeapPoolContainer/DescriptorHeapPoolContainer.h"

//外部
#include "../../Device/DeviceContextDiplomat/DeviceContextDiplomat.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCmdLicences.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandProvider/DeviceContextCommandProvider.h"
#include "../../Device/DeviceContextDiplomat/DeviceContextCommandExecutor/DeviceContextCommandExecutor.h"

using namespace ProjectConfig::Core;

namespace
{
	auto const fileName = "DescriptorHeapCreator.cpp";
}

DescriptorHeapContext::DescriptorHeapCreator::DescriptorHeapCreator
(
	NexusFieldProof proof_,
	DescriptorHeapPoolContainer& container_,
	DeviceContextDiplomat& deviceContextDiplomat_
) {
	//deviceContextからディスクリプタヒープ生成コマンドを渡してもらう
	auto* deviceContextCmdProvider = deviceContextDiplomat_.Access<DeviceContext::CommandProvider>();
	DeviceContext::CommandProvider::LicenceType<DeviceContextCmds::CreateDescriptorHeap> licenceCreateDescriptorHeap;
	auto createDescriptorHeapCmd = deviceContextCmdProvider->Provide<DeviceContextCmds::CreateDescriptorHeap>(licenceCreateDescriptorHeap);

	//deviceContextのコマンド実行クラスから、各種descriptorHeapのインクリメントサイズを教えてもらう
	auto* cmdExecutor = deviceContextDiplomat_.Access<DeviceContext::CommandExecutor>();
	UINT rtvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	UINT srvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	UINT dsvDHIncrementSIze = cmdExecutor->CalcDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	container_.Import<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>
	(
		proof_,
		std::move(Create<D3D12_DESCRIPTOR_HEAP_TYPE_RTV>(createDescriptorHeapCmd,kNumDescriptorsRTVHeap, false, rtvDHIncrementSIze))
	);
	Logger::Log("Create: DescriptorHeapRTV", fileName);

	container_.Import<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>
	(
		proof_,
		std::move(Create<D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV>(createDescriptorHeapCmd,kNumDescriptorSRVHeap, false, srvDHIncrementSIze))
	);
	Logger::Log("Create: DescriptorHeapSRV", fileName);

	container_.Import<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>
	(
		proof_,
		std::move(Create<D3D12_DESCRIPTOR_HEAP_TYPE_DSV>(createDescriptorHeapCmd,kNumDescriptorsDSVHeap, false, dsvDHIncrementSIze))
	);
	Logger::Log("Create: DescriptorHeapDSV", fileName);

}
