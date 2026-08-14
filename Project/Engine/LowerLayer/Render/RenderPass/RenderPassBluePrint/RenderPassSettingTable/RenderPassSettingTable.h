#pragma once
#include "../RenderPassBluePrint.h"
#include "../../RequiredInfo/PassSettings/PassSettings.h"


struct RenderPassBluePrint::RenderPassSettingTable
{

	RenderContext::PassBehavior::PassSettings SettingTable(RenderPassComponent::Pass pass_);
};

