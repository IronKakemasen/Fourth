#pragma once

struct Vector3;

template<typename T>
struct Vector4;

class ImGuiInterface 
{
public:

	ImGuiInterface() = delete;

	enum class WindowAttach:UINT
	{
		kNone		= 0,
		kAddMenuBar = 1 << 0,  
		kNoCollapse = 1 << 1,  
		kNoMove		= 1 << 2,  
		kNoResize	= 1 << 3

	};

	friend constexpr WindowAttach operator|(WindowAttach left_, WindowAttach right_)
	{
		return WindowAttach(UINT(left_) | UINT(right_));
	}

	class Window
	{
	public:

		Window
		(
			char const* name_,
			WindowAttach attach_ = WindowAttach::kNone
		);

		~Window();

		Window(Window const&) = delete;
		Window& operator=(Window const&) = delete;

		//ウィンドウがたたまれているかどうかなどを返すため
		explicit operator bool() const { return visible; }

	private:

		bool visible = false;
	};

	//フォーマット形式のテキスト出力
	static void TextFormatable(char const* fmt_, ...);
	//ただの文字列形式
	static void Text(char const* text_);


	//区切り線
	static void Separator();
	//ボタン
	static bool Button(char const* label_);
	//チェックボックス（そのまま）
	static void Checkbox(char const* label_, bool* valuePtr_);
	//スライダー
	template<typename ValueType>
	static void Slider(char const* label_, ValueType& value_, ValueType min_, ValueType max_);
	//ベクタ3専用
	static void DragVector3(char const* label_, Vector3& vec3_, float speed_ = 0.01f);
	//カラー(Vector4<float>)
	static void ColorEdit4(char const* label_, Vector4<float>& vec4_);
	//横並び
	static void SameLine();
	//ラジオボタン
	static bool RadioButton(char const* label_, int value_, int dst_);
	//折り畳み
	static bool TreeNodeBool(char const* label_);
	static void TreePop();
	//子ウィンドウ開始
	static void BeginChild(char const* label_, float width_ = 0.0f, float height_ = 0.0f);
	static void EndChild();
	//メニュー
	static bool BeginMenuBool(char const* label_);
	static void EndMenu();
	static bool MenuItemBool(char const* label_);
	//ウィンドウサイズの指定
	static void SetWindowSize(float x_, float y_);


private:

	//アタッチフラグをImGuiように変換
	static int ConvertAttachFlagsToImGuiStyle(WindowAttach flags_);

	//以下デバッグ用
	static inline std::string curWindowName;
	static inline int treeNodeCnt{};
	static inline int childCnt{};
	static inline int menuCnt{};


	static void Debug();

};

template<>
void ImGuiInterface::Slider(char const* label_, int& value_, int min_, int max_);

template<>
void ImGuiInterface::Slider(char const* label_, float& value_, float min_, float max_);
