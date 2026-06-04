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

	//引数のコマンドを生成する
	[[nodiscard]] std::unique_ptr<DeviceContextCommandBehavior> CreateCommand(DeviceContext::InstanceKey instanceKey_ , DeviceContext::CommandType type_);


};

//DeviceContext::CommandGeneratorのみ生成できる
struct DeviceContext::CommandGenerator::GenerateKey
{
private:
	friend class DeviceContext::CommandGenerator;

	explicit GenerateKey() = default;
};
