#pragma once

#include "SceneTextureCreatorOpaque/SceneTextureCreatorOpaque.h"
#include "SceneTextureCompositor/SceneTextureCompositor.h"





using AllPassUnique = std::tuple
<
	std::unique_ptr<SceneTextureCreatorOpaque>,
	std::unique_ptr<SceneTextureCompositor>
>;
