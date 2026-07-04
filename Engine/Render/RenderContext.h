#pragma once

class Nexus;
class ShaderContext;

class RenderContext
{
public:

	struct InstacnceKey;

	//モデルの描画情報を収集して整理する
	class ModelRenderingInfoOrganizer;


};


struct RenderContext::InstacnceKey
{
private:
	friend class Nexus;
	explicit InstacnceKey() = default;
};
