#include "PreCompileHeader.h"
#include "ObjDebugger.h"
#include "ImGuiInterface.h"



void GameObjectContext::FrontlineSystems::GameObjController::ObjDebugger::ShowActiveList(std::string const name_)
{
	ImGuiInterface::Window window("Hierarchy");
	if (window) ImGuiInterface::Text("Hello, ImGui!");

	if (window)
	{
		ImGuiInterface::Text("Hello, ImGui!");
		ImGuiInterface::Separator();

		//if (ImGuiInterface::Button("Click me")) ++counter;
		//ImGuiInterface::Text("Clicked: %d times", counter);

		//ImGuiInterface::Separator();

		//ImGuiInterface::Text("enabled=%d level=%d gain=%.2f", enabled, level, gain);

		//ImGuiInterface::RadioButton("radio", 3, 3);

		//ImGuiInterface::BeginChild("AAAAA");

		//ImGuiInterface::Checkbox("Enabled", &enabled);
		//ImGuiInterface::Slider("Level", level, 0, 10);          // int 版
		//ImGuiInterface::Slider("Gain", gain, 0.0f, 1.0f);       // float 版
		//ImGuiInterface::DragVector3("Position", position);      // 速度は省略(0.01f)
		//ImGuiInterface::ColorEdit4("Color", color);

		//ImGuiInterface::EndChild();

	}

}
