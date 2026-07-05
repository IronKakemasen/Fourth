#include "RenderPathBluePrint.h"

namespace
{
	auto const fileName = "RenderPathBluePrint.cpp";
}

using namespace RenderPathBluePrint;
using namespace RenderPathComponent;


template<>
std::string ShaderTable::Watch
(
	MeshType meshType_,
	PathType pathType_
)
{
	std::string shaderKey{};

	switch (pathType_)
	{
	case PathType::kBasic:

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
	PathType pathType_
)
{
	std::string shaderKey{};

	switch (pathType_)
	{
	case PathType::kBasic:

		if (materialType_ == MaterialType::kTest) shaderKey = "TestPS";

		break;

	default:
		ErrorMessageOutput::Assert::OutputError("シェーダーテーブルのパターンとして定義されていない(PS)", fileName);

		break;
	}

	return shaderKey;
}
