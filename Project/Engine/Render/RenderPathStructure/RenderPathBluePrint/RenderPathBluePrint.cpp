#include "RenderPathBluePrint.h"

namespace
{
	auto const fileName = "RenderPathBluePrint.cpp";
}

using namespace RenderPathBluePrint;
using namespace ShaderPathComponent;


template<>
std::string ShaderTable::Watch
(
	MeshType meshType_,
	Pass pathType_
)
{
	std::string shaderKey{};

	switch (pathType_)
	{
	case Pass::kBasic:

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
	Pass pathType_
)
{
	std::string shaderKey{};

	switch (pathType_)
	{
	case Pass::kBasic:

		if (materialType_ == MaterialType::kTest) shaderKey = "TestPS";

		break;

	default:
		ErrorMessageOutput::Assert::OutputError("シェーダーテーブルのパターンとして定義されていない(PS)", fileName);

		break;
	}

	return shaderKey;
}
