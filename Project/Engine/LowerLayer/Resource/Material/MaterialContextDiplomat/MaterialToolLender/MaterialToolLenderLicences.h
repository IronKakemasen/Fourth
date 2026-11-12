#pragma once
#include "MaterialToolLender.h"

class ModelContext;

struct MaterialContext::ToolLender::AccessMaterialAttacherLicence
{
private:

	friend class ModelContext;

	explicit AccessMaterialAttacherLicence() = default;
};