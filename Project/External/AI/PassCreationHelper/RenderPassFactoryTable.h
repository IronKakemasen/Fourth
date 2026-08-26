#pragma once
// RenderPassFactoryTable.h
#include "../../../Engine/LowerLayer/Render/RenderPass/AllRenderPass/RenderPassTraits.h"
#include "../../../Engine/LowerLayer/Render/RenderPass/AllRenderPass/AllPassFwd.h"
#include "../../../Engine/LowerLayer/Render/RenderPass/AllRenderPass/AllPassInclude.h"// 型の完全定義が要る
#include "../../../Engine/LowerLayer/Render/RenderPass/RenderPassCreator/RenderPassCreator.h"
#include "../../../Engine/LowerLayer/Render/RenderPath/AllRenderPath/PathBehavior.h"


//心の余裕がなかったのでAIに書いてもらった、switch-case撲滅用テーブル。
//2026/08/26
namespace RenderPassTraitsAI
{

	using PassFactory = void(*)
	(
			RenderContext::RenderPassCreator&,
			RenderContext::PathBehavior&,
			RenderContext::NexusFieldProof,
			std::string const&,
			BufferContextDiplomat&
	);

	// 型ごとに生成される、生成+登録をまとめて行う関数
	template<typename PassType>
	void CreateAndRegister
	(
		RenderContext::RenderPassCreator& creator_,
		RenderContext::PathBehavior& dstPath_,
		RenderContext::NexusFieldProof proof_,
		std::string const& name_,
		BufferContextDiplomat& bufferContextDiplomat_
	)
	{
		dstPath_.AddPass(proof_, creator_.Create<PassType>(proof_, name_, bufferContextDiplomat_));
	}

	template<typename... PassTypes>
	std::array<PassFactory, (size_t)RenderPassComponent::Pass::kCount> BuildTable(std::tuple<PassTypes...>*)
	{
		std::array<PassFactory, (size_t)RenderPassComponent::Pass::kCount> table{};

		((table[(size_t)RenderPassTraits::PassClassTraits<PassTypes>::passEnum] = &CreateAndRegister<PassTypes>), ...);

		return table;
	}

	inline const auto& PassFactoryTable()
	{
		static const auto table = BuildTable(static_cast<AllPassTypes*>(nullptr));
		return table;
	}
}
