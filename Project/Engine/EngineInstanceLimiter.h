#pragma once

template<typename... SceneTypes>
class aFourth;


//インスタンスを1つに制限するための
class EngineInstanceLimiter
{
	template<typename... SceneTypes>
	friend class aFourth;

	static void CanInstantiate()
	{
		static EngineInstanceLimiter instanceLimiter;

		ErrorMessageOutput::Assert::DetectError
		(
			instanceLimiter.instanceCnt++ == 0,
			"クラスaFourthは一つしかインスタンス化できません",
			"aFourth.h"
		);
	}

	EngineInstanceLimiter(const EngineInstanceLimiter&) = delete;
	EngineInstanceLimiter& operator=(const EngineInstanceLimiter&) = delete;
	EngineInstanceLimiter(EngineInstanceLimiter&&) = delete;
	EngineInstanceLimiter& operator=(EngineInstanceLimiter&&) = delete;

	~EngineInstanceLimiter() = default;
	EngineInstanceLimiter() = default;

	int instanceCnt{};

};
