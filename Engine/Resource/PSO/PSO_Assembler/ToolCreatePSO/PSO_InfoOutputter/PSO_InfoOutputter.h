#pragma once
#include "../../PipelineStateDesc.h"

class PSO_InfoOutputter
{
public:

	//デバッグ文字出力
	void OutputGraphicsPSOInfo
	(
		PipelineStateDesc::Graphics& srcDesc_, 
		std::string debugName_
	);

private:

	std::string debugName;
	std::string debugText;

	//デバッグ用テキストのテーブル
	std::string const DebugTextTable(DXGI_FORMAT format_)const;
	std::string const DebugTextTable(RenderStateComponent::BlendMode mode_) const;
	std::string const DebugTextTable(RenderStateComponent::FillMode mode_) const;
	std::string const DebugTextTable(RenderStateComponent::CullMode mode_) const;
	std::string const DebugTextTable(RenderStateComponent::DepthWrite write_) const;
	std::string const DebugTextTable(RenderStateComponent::DepthTest test_) const;

};

