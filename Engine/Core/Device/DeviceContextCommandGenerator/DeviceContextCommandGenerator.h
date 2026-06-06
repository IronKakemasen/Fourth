#pragma once
#include "../DeviceContext.h"


//Deviceを使用するコマンド群を生成するクラス
class DeviceContext::CommandGenerator
{
public:
	//コマンド群を生成するのに必要。
	struct GenerateKey;

	CommandGenerator(DeviceContext::InstanceKey instanceKey_);
	~CommandGenerator();

	//コマンドを生成する
	template<typename CommandClass>
	[[nodiscard]] std::unique_ptr<DeviceContextCommandBehavior> CreateCommand(DeviceContext::InstanceKey instanceKey_)
	{
		auto generateKey = CommandGenerator::GenerateKey{};
		std::unique_ptr<DeviceContextCommandBehavior> retCommand = std::make_unique<CommandClass>(generateKey);

		return retCommand;
	}

};

//DeviceContext::CommandGeneratorのみ生成できる
struct DeviceContext::CommandGenerator::GenerateKey
{
private:
	friend class DeviceContext::CommandGenerator;

	explicit GenerateKey() = default;
};
