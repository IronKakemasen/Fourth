#pragma once
#include "../ImGuiDebugger.h"

class DebugContext::ImGuiDebugger::HierarchyWindow
{
public:

	enum class Tag
	{
		kGameObject,


		kCount
	};

	HierarchyWindow();

	//ヒエラルキーウィンドウの表示
	void ShowHierarchyWindow();
	
	//アクティブリストへの追加
	template<Tag tag>
	void AddToActiveList(AgentKey key_,std::string const& name_)
	{
		activeListArr[UINT(tag)].emplace_back(&name_);
	}

	//非アクティブリストへの追加
	template<Tag tag>
	void AddToInActiveList(AgentKey key_, std::string const& name_)
	{
		inActiveListArr[UINT(tag)].emplace_back(&name_);
	}

private:

	template<Tag tag>
	struct TagTraits;

	//サイズ確保
	template<Tag tag>
	void Reserve()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			callChecker == tag,
			"Reserve()が正常に行われていない可能性がある(エンジン)",
			"HierarchyWindow.h"
		);

		UINT constexpr reserveSize = TagTraits<tag>::kListSize;

		activeListArr[UINT(tag)].reserve(reserveSize);
		inActiveListArr[UINT(tag)].reserve(reserveSize);

		callChecker = Tag((UINT)callChecker + 1);

		Logger::Log("Reserved " + std::string(TagTraits<tag>::kName) + "Lists: " + std::to_string(reserveSize), "HierarchyWindow.h");
	}

	//クリア
	template<Tag tag>
	void Clear()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			callChecker == tag,
			"Clear()が正常に行われていない可能性がある(エンジン)",
			"HierarchyWindow.h"
		);

		activeListArr[UINT(tag)].clear();
		inActiveListArr[UINT(tag)].clear();

		callChecker = Tag((UINT)callChecker + 1);
	}

	//子ウィンドウでリストを表示する
	template<Tag tag>
	void ShowChildWindow();


	char const* kHierarchyWindowName	= "Hierarchy";
	char const* kActiveListWindowName	= "ActiveList";
	char const* kInActiveListWindowName	= "InActiveList";

	std::array<std::vector<std::string const*> ,UINT(Tag::kCount)>  activeListArr;
	std::array<std::vector<std::string const*>, UINT(Tag::kCount)>  inActiveListArr;


	//デバッグ用
	Tag callChecker = Tag(0);
};


template<>
struct DebugContext::ImGuiDebugger::HierarchyWindow::TagTraits<DebugContext::ImGuiDebugger::HierarchyWindow::Tag::kGameObject>
{
	static constexpr UINT kListSize = 1000;
	static inline char const* kName = "GameObject";
};
