#pragma once
#include "../../RenderPassBehavior.h"

class SceneTextureCreator :public RenderContext::PassBehavior
{
public:

	SceneTextureCreator(std::unique_ptr<RenderContext::PassDesc>&& desc_);

private:



};

