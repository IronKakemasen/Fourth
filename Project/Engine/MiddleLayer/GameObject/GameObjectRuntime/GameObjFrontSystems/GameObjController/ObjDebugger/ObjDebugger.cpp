#include "PreCompileHeader.h"
#include "ObjDebugger.h"
#include "ImGuiInterface.h"

using namespace ProjectConfig;

GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger::ObjDebugger(size_t sumGameObject_)
{
	activeList.reserve(sumGameObject_);
	inActiveList.reserve(sumGameObject_);
}

void GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger::ShowHierarchyWindow()
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

	ImGuiInterface::Text(kActiveListWindoName);
	ImGuiInterface::BeginChild(kActiveListWindoName, 0.0f, 215.0f);
	
	for (auto const* name_ : activeList)
	{
		ImGuiInterface::Text(name_->c_str());
	}

	ImGuiInterface::EndChild();

	ImGuiInterface::Separator();
	ImGuiInterface::Separator();

	ImGuiInterface::Text(kInActiveListWindoName);
	ImGuiInterface::BeginChild(kInActiveListWindoName, 0.0f, 215.0f);

	for (auto const* name_ : inActiveList)
	{
		ImGuiInterface::Text(name_->c_str());
	}

	ImGuiInterface::EndChild();

	activeList.clear();
	inActiveList.clear();

#endif // !NDEBUG

}


void GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger::AddActiveList(std::string const& name_)
{
	activeList.emplace_back(&name_);
}

void GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger::AddInActiveList(std::string const& name_)
{
	inActiveList.emplace_back(&name_);
}
