#pragma once
#include "../GameObjController.h"

class GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger
{
public:

	ObjDebugger(size_t sumGameObject_);

	void ShowHierarchyWindow();
	void AddActiveList(std::string const& name_);
	void AddInActiveList(std::string const& name_);

private:

	char const* kHierarchyWindowName	= "Hierarchy";
	char const* kActiveListWindoName	= "ActiveList";
	char const* kInActiveListWindoName	= "InActiveList";

	std::vector<std::string const*> activeList;
	std::vector<std::string const*> inActiveList;

};

