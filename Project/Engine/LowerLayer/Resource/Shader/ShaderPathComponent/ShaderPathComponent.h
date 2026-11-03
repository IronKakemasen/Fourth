#pragma once


namespace ShaderPathComponent
{
	enum class MeshType
	{
		//RenderPass専用！！
		kOffscreen,


		kStatic

		,kCount

	};

	enum class MaterialType
	{
		//RenderPass専用！！
		kOffscreen,
		//ピクセルシェーダーを通さないケースはあるので
		kNone,
		//グリッドライン
		kGridLine,

		kStandard

		,kCount

	};

};