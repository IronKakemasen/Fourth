#pragma once
#include "../PSO_Context.h"


class ShaderLibrary;

class PSO_Context::Assembler
{
public:

	Assembler(PSO_Context::InstanceKey key_, ShaderLibrary* shaderLibrary_);


private:

	ShaderLibrary* shaderLibrary;
};

