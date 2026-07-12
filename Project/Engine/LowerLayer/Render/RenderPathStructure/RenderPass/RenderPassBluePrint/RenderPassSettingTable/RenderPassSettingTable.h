#pragma once
#include "../RenderPassBluePrint.h"
#include "../../RequiredInfo/PassSettings/PassSettings.h"


struct RenderPassBluePrint::RenderPassSettingTable
{

	RenderPath::Pass::PassSettings SettingTable(RenderPassComponent::Pass pass_);
};

