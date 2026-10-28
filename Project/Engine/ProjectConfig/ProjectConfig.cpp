#include "ProjectConfig.h"

ProjectConfig::Window::Window()
{
	Miyajison* miyajison = Miyajison::Get();
	kFirstSceneDebug = miyajison->LoadData<std::string>("ProjectConfig", { "FirstSceneDebug" });
	kFirstSceneRelease = miyajison->LoadData<std::string>("ProjectConfig", { "FirstSceneRelease" });
	kWidth = (UINT)miyajison->LoadData<int>("ProjectConfig", { "Width" });
	kHeight = (UINT)miyajison->LoadData<int>("ProjectConfig", { "Height" });
}
