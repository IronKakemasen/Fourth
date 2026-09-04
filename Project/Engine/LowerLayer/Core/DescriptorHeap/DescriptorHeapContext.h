#pragma once

class Nexus;
class DescriptorHeapPool;
class DeviceContextDiplomat;
class DescriptorHeapContextDiplomat;

class DescriptorHeapContext
{

	//ディスクリプタヒープコンテナ
	class DescriptorHeapPoolContainer;

public:

	//DescriptorHeap生成クラス
	class DescriptorHeapCreator;
	//view生成
	class ViewCreator;

	//Nexusフィールドである証
	struct NexusFieldProof;
	//ツール貸し出しクラス
	class ToolLender;

	DescriptorHeapContext
	(
		NexusFieldProof proof_,
		DeviceContextDiplomat& deviceContextDiplomat_
	);

	~DescriptorHeapContext();

	std::unique_ptr<DescriptorHeapContextDiplomat> diplomat;

private:

	//DescriptorHeapPoolのコンテナ
	std::unique_ptr<DescriptorHeapPoolContainer> descriptorHeapPoolContainer;
	//ビュー生成機関
	std::unique_ptr<ViewCreator> viewCreator;

};



//生成できるのはNexusのみ
struct DescriptorHeapContext::NexusFieldProof
{
private:

	friend class Nexus;
	explicit NexusFieldProof() = default;
};

