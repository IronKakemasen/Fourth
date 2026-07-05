
#include "ShaderCombiner.h"

//外部
#include "../../../../Resource/Shader/ShaderLibrary/ShaderLibrary.h"

RenderPath::MS_PS RenderPath::PathComposer::ShaderCombiner::Combine(ShaderLibrary* lib_, std::string const msKey_, std::string const psKey_)
{
	return
	{
		lib_->Export(ShaderLibrary::GetDataKey{}, msKey_) ,
		(psKey_.size() > 0) ? lib_->Export(ShaderLibrary::GetDataKey{}, psKey_) : nullptr
	};
}

