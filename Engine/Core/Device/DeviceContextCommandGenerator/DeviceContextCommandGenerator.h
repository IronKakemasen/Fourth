#pragma once
#include "../DeviceContext.h"


//Deviceを使用するコマンド群を生成するクラス
class DeviceContext::CommandGenerator
{
public:

	struct GenerateKey;

	CommandGenerator(DeviceContext::InstanceKey instanceKey_);
	~CommandGenerator();

private:

	//GPUバッファを生成するコマンド群
	class CreatingGPUBuffer;
	std::unique_ptr<CreatingGPUBuffer> creatingGPUBuffer;

};

//DeviceContext::CommandGeneratorのみ生成できる
struct DeviceContext::CommandGenerator::GenerateKey
{
private:
	friend class DeviceContext::CommandGenerator;

	explicit GenerateKey() = default;
};
