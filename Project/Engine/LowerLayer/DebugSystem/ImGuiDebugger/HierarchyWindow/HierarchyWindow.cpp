#include "PreCompileHeader.h"
#include "HierarchyWindow.h"

#include "ImGuiInterface.h"

using namespace ProjectConfig;

namespace
{
	auto const fileName = "HierarchyWindow.cpp";
}

DebugContext::ImGuiDebugger::HierarchyWindow::HierarchyWindow()
{
#ifndef NDEBUG

	Reserve<Tag::kGameObject>();

	ErrorMessageOutput::Assert::DetectError
	(
		callChecker == Tag::kCount,
		"なにかがリザーブされてない(エンジン)",
		fileName
	);

#endif
}

void DebugContext::ImGuiDebugger::HierarchyWindow::ShowHierarchyWindow()
{
#ifndef NDEBUG

	//ウィンドウのサイズと位置を指定
	ImGuiInterface::SetNextWindowSize(Debug::ImGuiLayout::kHierarchyWindowRateX, Debug::ImGuiLayout::kHierarchyWindowRateY);
	ImGuiInterface::SetNextWindowPos(0.0f, 0.0f);

	ImGuiInterface::Window window
	(
		kHierarchyWindowName,
		ImGuiInterface::WindowAttach::kNoMove	  |
		ImGuiInterface::WindowAttach::kNoCollapse |
		ImGuiInterface::WindowAttach::kNoResize
	);

	//ゲームオブジェクト一覧表示
	ShowChildWindow<Tag::kGameObject>();




	//リストのクリア
	Clear<Tag::kGameObject>();

	ErrorMessageOutput::Assert::DetectError
	(
		callChecker == Tag::kCount,
		"なにかがリザーブされてない(エンジン)",
		fileName
	);

#endif // !NDEBUG

}

template<DebugContext::ImGuiDebugger::HierarchyWindow::Tag tag>
void DebugContext::ImGuiDebugger::HierarchyWindow::ShowChildWindow()
{

	if (ImGuiInterface::TreeNodeBool(TagTraits<tag>::kName))
	{
		ImGuiInterface::Text(kActiveListWindowName);
		ImGuiInterface::BeginChild(kActiveListWindowName, 0.0f, 215.0f);

		auto const& dstActiveList = activeListArr.at((UINT)tag);

		for (auto const* name_ : dstActiveList)
		{
			ImGuiInterface::Text(name_->c_str());
		}

		ImGuiInterface::EndChild();

		//アクティブ・非アクティブリスト子ウィンドウ間のスペース
		ImGuiInterface::Separator();
		ImGuiInterface::Separator();

		ImGuiInterface::Text(kInActiveListWindowName);
		ImGuiInterface::BeginChild(kInActiveListWindowName, 0.0f, 215.0f);

		auto const& dstInActiveList = inActiveListArr.at((UINT)tag);

		for (auto const* name_ : dstInActiveList)
		{
			ImGuiInterface::Text(name_->c_str());
		}

		ImGuiInterface::EndChild();


		ImGuiInterface::TreePop();
	}

}


template
void DebugContext::ImGuiDebugger::HierarchyWindow::ShowChildWindow < DebugContext::ImGuiDebugger::HierarchyWindow::Tag::kGameObject> ();

