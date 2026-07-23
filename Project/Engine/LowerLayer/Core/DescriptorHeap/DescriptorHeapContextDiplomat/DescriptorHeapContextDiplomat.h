#pragma once
#include "../DescriptorHeapContext.h"


//コマンドコンテキストの外交官クラス
class DescriptorHeapContextDiplomat
{
public:
	DescriptorHeapContextDiplomat
	(
		DescriptorHeapContext::NexusFieldProof proof_,
		std::unique_ptr<DescriptorHeapContext::ToolLender>&& toolLender_
	);

	template<typename ToolType>
	ToolType* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:
	//提供するツールのテーブル
	std::tuple<std::unique_ptr<DescriptorHeapContext::ToolLender>> tools;

};

