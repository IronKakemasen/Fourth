#include "PreCompileHeader.h"
#include "ShaderTable.h"


namespace
{
	auto const fileName = "RenderPathBluePrint.cpp";
}

using namespace RenderPathBluePrint;
using namespace ShaderPathComponent;
using namespace RenderPathComponent;


template<>
std::string ShaderTable::Watch
(
	MeshType meshType_,
	Pass passType_
)
{
	std::string shaderKey{};

	switch (passType_)
	{
	case Pass::kCreateSceneTexture:

		if (meshType_ == MeshType::kTest) shaderKey = "TestMS";

		break;

	default:
		ErrorMessageOutput::Assert::OutputError("シェーダーテーブルのパターンとして定義されていない(MS)", fileName);

		break;
	}

	return shaderKey;
}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
std::string ShaderTable::Watch
(
	MaterialType materialType_,
	Pass passType_
)
{
	std::string shaderKey{};

	switch (passType_)
	{
	case Pass::kCreateSceneTexture:

		if (materialType_ == MaterialType::kTest) shaderKey = "TestPS";

		break;

	default:
		ErrorMessageOutput::Assert::OutputError("シェーダーテーブルのパターンとして定義されていない(PS)", fileName);

		break;
	}

	return shaderKey;
}
