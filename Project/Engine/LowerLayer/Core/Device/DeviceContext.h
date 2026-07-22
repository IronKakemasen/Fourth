#pragma once

class Nexus;
class DeviceContextCommandBehavior;
class DeviceContextDiplomat;

//struct ModelStructure
//{
//	Transform trans;
//
//private:
//
//	//割り当てられたTransformMatrixBufferArrayのインデックス
//	DispatchedTransformMatrixID transID;
//	//必要かわからないが、自身のtransIDが指すバッファのユニークID。バッチング時に検索を省くために使用？
//	TransformBufferUniqueID transIDCache;
//	//色やカラーマップなどの情報
//	Material material;
//	//メッシュシェーダーの決定要因
//	MeshType meshType;
//	//BlendMode、CullModeなど。昔定義したやつ
//	RenderState renderState;
//
//};
//
//struct Model
//{
//	//MeshFile名で決定.サブメッシュも含む
//	std::vector<MeshDataID> id;
//
//	//メインとサブ分のデータ群
//	std::vector<ModelStructure> modelStructures;
//};



class DeviceContext
{
	//コアパーツを生成する
	class Setupper;

protected:

	//コアパーツにアクセスするのを許可するキー
	struct AccessKey;

public:

	//自身の生成キー。Nexusしか許さない
	struct InstanceKey;
	//コマンド生成キー
	struct GenerateKey;

	//他クラスにコアパーツを流用させないようにコマンドを生成して渡す
	class CommandProvider;
	//他クラスにコアパーツを流用させないようにコマンドを自ら実行する
	class CommandExecutor;

	std::unique_ptr<DeviceContextDiplomat> diplomat;

	DeviceContext(InstanceKey instanceKey);
	~DeviceContext();

private:

	Microsoft::WRL::ComPtr<ID3D12Device8> device = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter = nullptr;

	//Setupperからコアパーツを生成し、引き継ぐ
	void TakeOverCoreParts(DeviceContext::InstanceKey instanceKey_);
	//CommandProviderの生成
	std::unique_ptr<CommandProvider> InstantiateCommandProvider(DeviceContext::InstanceKey instanceKey_);
	//CommandExecutorの生成
	std::unique_ptr<CommandExecutor> InstantiateCommandExecutor(DeviceContext::InstanceKey instanceKey_);
};


//生成できるのはNexusのみ
struct DeviceContext::InstanceKey
{
private:

	friend class Nexus;
	explicit InstanceKey() = default;
};


//アクセスさせるがポインタは渡さん
struct DeviceContext::AccessKey
{
private:

	friend class CommandProvider;
	friend class CommandExecutor;

	explicit AccessKey() = default;
};

struct DeviceContext::GenerateKey
{
private:

	friend class DeviceContext::CommandProvider;
	friend class DeviceContext::CommandExecutor;

	explicit GenerateKey() = default;
};



