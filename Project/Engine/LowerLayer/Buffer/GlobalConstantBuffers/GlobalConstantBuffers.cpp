#include "PreCompileHeader.h"
#include "GlobalConstantBuffers.h"

//外部
#include "../../../../../Assets/Shared/ConstantBuffers.h"

namespace
{
	auto const fileName = "GlobalConstantBuffers.cpp";
}


BufferContext::GlobalConstantBuffers::GlobalConstantBuffers
(
	NexusFieldProof proof_
)
{

}

void BufferContext::GlobalConstantBuffers::PackRuntimeContainer(NexusFieldProof proof_, AgentKey agentKey_)
{
	//デバッグ用
	std::vector<uint8_t> forChecking{};
	

	//昇順は担保されてるはずだからそのまま詰めてく
	for (auto [key, value] : gpuVirtualAddressMap)
	{
		//念のため重複チェック
		ErrorMessageOutput::Assert::DetectError(!std::ranges::contains(forChecking, key), "定数バッファのスロット設定おかしくね？", fileName);
		forChecking.emplace_back(key);

		gpuVirtualAddressVector[0].emplace_back(value[0]);
		gpuVirtualAddressVector[1].emplace_back(value[1]);
	}

	auto const numActualCBuffers = forChecking.size();
	auto const numRequiredCBuffers = (size_t)ConstantBuffers::ConstantBufferBindSlots::kCount;

	ErrorMessageOutput::Assert::DetectError
	(
		numActualCBuffers == numRequiredCBuffers,
		"定数バッファの生成数が合わない実 " + std::to_string(numActualCBuffers) + " : 必 " + std::to_string(numRequiredCBuffers),
		fileName
	);

	Logger::Log("===== List of cBuffer slots =====",fileName);
	for (auto [key, value] : bufferNameMap)
	{
		Logger::Log("Slot[" + std::to_string(key) + "]: " + value);
	}

	gpuVirtualAddressMap.clear();
	bufferNameMap.clear();
}


void BufferContext::GlobalConstantBuffers::Import
(
	Local_ImportLicence licence_,
	std::string const bufferName_,
	const uint8_t bindSlot_,
	DoubleVirtualGPUAddress doubleVirtualGPUAddress_
) 
{
	ErrorMessageOutput::Assert::DetectError
	(
		gpuVirtualAddressMap.find(bindSlot_) == gpuVirtualAddressMap.end(),
		"この定数バッファのスロットは使われているよ",
		fileName
	);

	bufferNameMap[bindSlot_] = bufferName_;
	gpuVirtualAddressMap[bindSlot_] = doubleVirtualGPUAddress_;
}