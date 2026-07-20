#pragma once
#include "../BufferContext.h"


//コマンドコンテキストの外交官クラス
class BufferContextDiplomat
{
public:
	BufferContextDiplomat
	(
		BufferContext::InstanceKey key_,
		std::unique_ptr<BufferContext::ToolLender>&& toolLender_
	);

	template<typename ToolType>
	ToolType* Access()
	{
		return std::get<std::unique_ptr<ToolType>>(tools).get();
	}

private:
	//提供するツールのテーブル
	std::tuple<std::unique_ptr<BufferContext::ToolLender>> tools;

};

