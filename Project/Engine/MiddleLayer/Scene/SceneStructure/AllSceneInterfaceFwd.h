#pragma once

class SceneInitInterface;
class SceneRuntimeInterface;

using SceneInterfacesPtr = std::tuple<SceneInitInterface*, SceneRuntimeInterface*>;

using SceneInterfacesUnique = std::tuple
<
	std::unique_ptr<SceneInitInterface>,		//シーン初期化用のインターフェース。初期化フェーズが終わったら破棄
	std::unique_ptr<SceneRuntimeInterface>		//シーンのランタイム用インターフェース。破棄されない
>;