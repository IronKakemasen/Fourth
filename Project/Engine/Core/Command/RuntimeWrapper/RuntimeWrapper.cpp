#include "PreCompileHeader.h"
#include "RuntimeWrapper.h"

CommandContext::RuntimeWrapper::RuntimeWrapper(ID3D12GraphicsCommandList6* cmdList_)
	:cmdList(cmdList_)
{

}
