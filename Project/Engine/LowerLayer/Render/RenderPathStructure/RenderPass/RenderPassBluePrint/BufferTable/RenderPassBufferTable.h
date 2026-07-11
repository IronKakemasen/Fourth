#pragma once
#include "../RenderPassBluePrint.h"
#include "../../RequiredInfo/BufferRequiredInfo/BufferRequiredInfo.h"

struct RenderPassBluePrint::BufferTable
{
	std::unique_ptr<RenderPath::Pass::RequiredBufferInfo> BufferInfoTable(RenderPassComponent ::Pass pass_);

};

