#pragma once

class SceneInitInterface;
class SceneRuntimeInterface;

using SceneInterfacesPtr = std::tuple<SceneInitInterface*, SceneRuntimeInterface*>;