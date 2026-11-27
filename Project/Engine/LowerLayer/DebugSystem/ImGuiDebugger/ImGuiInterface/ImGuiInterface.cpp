#include "PreCompileHeader.h"
#include "ImGuiInterface.h"
#include "../ImGuiInclude.h"
#include "../../../../Math/Vector/Vector3.h"
#include "../../../../Math/Vector/Vector4.h"


namespace
{
	auto const fileName = "ImGuiInterface.cpp";
}

ImGuiInterface::Window::Window
(
	char const* name_, 
	WindowAttach attach_
)	
{
#ifndef NDEBUG

	//attachFlagsResultをもとにImGui::Beginを呼ぶ
	visible = ImGui::Begin
	(
		name_,
		nullptr,
		ImGuiWindowFlags(ConvertAttachFlagsToImGuiStyle(attach_))
	);

	//デバッグ用に
	curWindowName = name_;

#endif

}

int ImGuiInterface::ConvertAttachFlagsToImGuiStyle(WindowAttach flags_)
{
#ifndef NDEBUG

	ImGuiWindowFlags flags{};

	if ((int)flags_ & (int)WindowAttach::kAddMenuBar)	flags	|= ImGuiWindowFlags_MenuBar;

	if ((int)flags_ & (int)WindowAttach::kNoMove)		flags	|= ImGuiWindowFlags_NoMove;

	if ((int)flags_ & (int)WindowAttach::kNoCollapse)	flags	|= ImGuiWindowFlags_NoCollapse;

	if ((int)flags_ & (int)WindowAttach::kNoResize)		flags	|= ImGuiWindowFlags_NoResize;

	return flags;

#else

	return 0;

#endif

}

ImGuiInterface::Window::~Window()
{
#ifndef NDEBUG

	Debug();

	ImGui::End();

#endif
}

void ImGuiInterface::Debug()
{
	ErrorMessageOutput::Assert::DetectError
	(
		treeNodeCnt == 0,
		curWindowName + "でImGuiInterface::TreePop()呼び足りない",
		fileName
	);

	ErrorMessageOutput::Assert::DetectError
	(
		childCnt == 0,
		curWindowName + "でImGuiInterface::EndChild()呼び足りない",
		fileName
	);

	ErrorMessageOutput::Assert::DetectError
	(
		menuCnt == 0,
		curWindowName + "でImGuiInterface::EndMenu()呼び足りない",
		fileName
	);
}


void ImGuiInterface::Text(char const* fmt_, ...)
{
#ifndef NDEBUG

	va_list args;
	va_start(args, fmt_);
	ImGui::TextV(fmt_, args);
	va_end(args);

#endif
}

void ImGuiInterface::Separator()
{
#ifndef NDEBUG

	ImGui::Separator();

#endif
}

bool ImGuiInterface::Button(char const* label_)
{
#ifndef NDEBUG

	return ImGui::Button(label_);


#else

	return {};

#endif
}

void ImGuiInterface::Checkbox(char const* label_, bool* valuePtr_)
{
#ifndef NDEBUG

	ImGui::Checkbox(label_, valuePtr_);

#endif
}

template<>
void ImGuiInterface::Slider(char const* label_, int& value_, int min_, int max_)
{
#ifndef NDEBUG

	ImGui::SliderInt(label_, &value_, min_, max_);

#endif

}

template<>
void ImGuiInterface::Slider(char const* label_, float& value_, float min_, float max_)
{
#ifndef NDEBUG

	ImGui::SliderFloat(label_, &value_, min_, max_);

#endif

}

void ImGuiInterface::DragVector3(char const* label_, Vector3& vec3_, float speed_)
{
#ifndef NDEBUG

	ImGui::DragFloat3(label_, &vec3_.data.x, speed_);

#endif

}

void ImGuiInterface::ColorEdit4(char const* label_, Vector4<float>& vec4_)
{

#ifndef NDEBUG

	ImGui::ColorEdit4(label_, &vec4_.x);

#endif
}

void ImGuiInterface::SameLine()
{

#ifndef NDEBUG

	ImGui::SameLine();

#endif

}

bool ImGuiInterface::RadioButton(char const* label_, int value_ , int dst_)
{

#ifndef NDEBUG

	return ImGui::RadioButton(label_, value_ == dst_);

#else

	return false;

#endif

}

bool ImGuiInterface::TreeNodeBool(char const* label_)
{

#ifndef NDEBUG

	bool isOpened = ImGui::TreeNode(label_);
	treeNodeCnt += isOpened;
	
	return isOpened;

#else

	return true;

#endif

}


void ImGuiInterface::TreePop()
{
#ifndef NDEBUG

	ErrorMessageOutput::Assert::DetectError
	(
		treeNodeCnt > 0,
		curWindowName + "TreePop()過剰呼び出し",
		fileName
	);

	treeNodeCnt--;	

	ImGui::TreePop();

#endif

}

void ImGuiInterface::BeginChild(char const* label_)
{

#ifndef NDEBUG

	childCnt++;
	ImGui::BeginChild(label_);

#endif

}

void ImGuiInterface::EndChild()
{
#ifndef NDEBUG

	ErrorMessageOutput::Assert::DetectError
	(
		childCnt > 0,
		curWindowName + "EndChild()過剰呼び出し",
		fileName
	);

	childCnt--;
	ImGui::EndChild();

#endif

}

bool ImGuiInterface::BeginMenuBool(char const* label_)
{
#ifndef NDEBUG

	bool isOpened = ImGui::BeginMenu(label_);
	menuCnt += isOpened;

	return isOpened;

#else

	return false;

#endif

}

void ImGuiInterface::EndMenu()
{
#ifndef NDEBUG

	ErrorMessageOutput::Assert::DetectError
	(
		menuCnt > 0,
		curWindowName + "EndMenu()過剰呼び出し",
		fileName
	);

	menuCnt--;

	ImGui::EndMenu();

#endif

}

bool ImGuiInterface::MenuItemBool(char const* label_)
{

#ifndef NDEBUG

	return ImGui::MenuItem(label_);

#else

	return false;

#endif

}