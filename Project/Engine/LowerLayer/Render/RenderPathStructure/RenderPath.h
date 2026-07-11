#pragma once
#include "../RenderContext.h"


class RenderPath
{
	struct Desc;


public:
	//レンダーパスを構成します
	class PathComposer;
	///Pathを構成するPass
	struct Pass;

protected:

	using MS_PS = std::pair<IDxcBlob*, IDxcBlob*>;
	

};

