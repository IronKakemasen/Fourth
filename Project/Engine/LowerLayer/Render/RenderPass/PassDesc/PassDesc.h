#pragma once
#include "PassRequiredInfo.h"

class RenderContext::PassDesc
{
public:

	PassDesc(const PassRequiredInfo& info_);


private:

	PassRequiredInfo info;

};

