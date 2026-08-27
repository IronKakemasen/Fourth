#pragma once
#include "AllPassFwd.h"
#include "../RenderPassComponent.h"

namespace RenderPassTraits
{
	//クラスから名前と列挙型を
	template<typename PassType>
	struct PassClassTraits;

	template<>
	struct PassClassTraits<SceneTextureCreatorOpaque>
	{
		static inline const std::string name = "SceneTextureCreatorOpaque";
		static constexpr RenderPassComponent::Pass passEnum = RenderPassComponent::Pass::kSceneTextureCreatorOpaque;

	};

	template<>
	struct PassClassTraits<SceneTextureCompositor>
	{
		static inline const std::string name = "SceneTextureCompositor";
		static constexpr RenderPassComponent::Pass passEnum = RenderPassComponent::Pass::kSceneTextureCompositor;

	};

	//名前から列挙型を特定
	constexpr RenderPassComponent::Pass PassNameToPassType(std::string const passName_)
	{
		RenderPassComponent::Pass pass = RenderPassComponent::Pass::kEnd;

		if (passName_ == PassClassTraits<SceneTextureCreatorOpaque>::name)
		{
			pass = PassClassTraits<SceneTextureCreatorOpaque>::passEnum;
		}
		else if (passName_ == PassClassTraits<SceneTextureCompositor>::name)
		{
			pass = PassClassTraits<SceneTextureCompositor>::passEnum;
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
	struct PassTypeToPassClass<RenderPassComponent::Pass::kSceneTextureCreatorOpaque>
	{
		using PassClass = SceneTextureCreatorOpaque;
	};

	template<>
	struct PassTypeToPassClass<RenderPassComponent::Pass::kSceneTextureCompositor>
	{
		using PassClass = SceneTextureCompositor;
	};

}
