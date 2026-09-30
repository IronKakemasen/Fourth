#include "StaticRenderGraph.h"


//外部
#include "../../../Core/DescriptorHeap/DescriptorHeapContextDiplomats.h"

#include "../../../Core/Command/CommandContextDiplomats.h"



void RenderContext::StaticRenderGraph::Run
(
	PSO_PoolDispatcher& psoDispatcher_,
	UINT const frameIndex_,
	DescriptorHeapContextDiplomat& descriptorHeapContextDiplomat_,
	CommandContextDiplomat& commandContextDiplomat_,
	BufferContextDiplomat& bufferContextDiplomat_
)
{
	//srvDescriptorHeapにアクセス
	auto dToolLender = descriptorHeapContextDiplomat_.Access<DescriptorHeapContext::ToolLender>();
	DescriptorHeapContext::ToolLender::LicenceType<ID3D12DescriptorHeap> dLicence;
	auto* srvUavDescriptorHeap = dToolLender->Lend<ID3D12DescriptorHeap>(dLicence);

	//runtimeCmdWrapperにアクセス
	auto cToolLender = commandContextDiplomat_.Access<CommandContext::ToolLender>();
	CommandContext::ToolLender::LicenceType<RuntimeWrapper> cLicence;
	auto& runtimeCmdWrapper = *cToolLender->Lend<RuntimeWrapper>(cLicence);


}

