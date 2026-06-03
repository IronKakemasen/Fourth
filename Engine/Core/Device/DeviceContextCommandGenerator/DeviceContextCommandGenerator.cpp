#include "PreCompileHedder.h"
#include "DeviceContextCommandGenerator.h"

#include "../Commands/CreatGPUBuffer/CommandOfCreatingGPUBuffer.h"


DeviceContext::CommandGenerator::CommandGenerator(DeviceContext::InstanceKey instanceKey_)
{

}

DeviceContext::CommandGenerator::~CommandGenerator()
{
	//GPU生成クラスのインスタンス化
	creatingGPUBuffer.reset(new CommandGenerator::CreatingGPUBuffer(CommandGenerator::GenerateKey{}));

}


