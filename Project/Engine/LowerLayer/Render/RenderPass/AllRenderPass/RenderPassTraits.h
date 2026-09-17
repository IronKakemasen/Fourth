#pragma once
#include "AllPassFwd.h"
#include "../RenderPassComponent.h"

namespace RenderPassTraits
{
	//クラスから名前と列挙型を
	template<typename PassType>
	struct PassClassTraits;

	template<>
	struct PassClassTraits<SceneOpaque>
	{
		static inline const std::string name = "SceneOpaque";
		static constexpr RenderPassComponent::Pass passEnum = RenderPassComponent::Pass::kSceneOpaque;

	};

	template<>
	struct PassClassTraits<SceneCompositor>
	{
		static inline const std::string name = "SceneCompositor";
		static constexpr RenderPassComponent::Pass passEnum = RenderPassComponent::Pass::kSceneCompositor;

	};

	//名前から列挙型を特定
	constexpr RenderPassComponent::Pass PassNameToPassType(std::string const passName_)
	{
		RenderPassComponent::Pass pass = RenderPassComponent::Pass::kEnd;

		if (passName_ == PassClassTraits<SceneOpaque>::name)
		{
			pass = PassClassTraits<SceneOpaque>::passEnum;
		}
		else if (passName_ == PassClassTraits<SceneCompositor>::name)
		{
			pass = PassClassTraits<SceneCompositor>::passEnum;
		}
		else
		{
			ErrorMessageOutput::Assert::OutputError(passName_ + "こんなパスネームは存在しない", "RenderPassComponent.cpp");
		}

		return pass;
	}


	//クラスから列挙型を特定
    template<RenderPassComponent::Pass passType>
    struct PassTypeToPassClass;

	template<>
	struct PassTypeToPassClass<RenderPassComponent::Pass::kSceneOpaque>
	{
		using PassClass = SceneOpaque;
	};

	template<>
	struct PassTypeToPassClass<RenderPassComponent::Pass::kSceneCompositor>
	{
		using PassClass = SceneCompositor;
	};

}
