#pragma once
#include "../Nexus/Nexus.h"

template<typename... SceneTypes>
class aFourth
{
	//インスタンスを1つに制限するための
	class InstanceLimiter
	{
	public:
		static void CanInstantiate()
		{
			static InstanceLimiter instanceLimiter;

			ErrorMessageOutput::Assert::DetectError
			(
				instanceLimiter.instanceCnt++ == 0,
				"クラスaFourthは一つしかインスタンス化できません",
				"aFourth.h"
			);
		}

		InstanceLimiter(const InstanceLimiter&) = delete;
		InstanceLimiter& operator=(const InstanceLimiter&) = delete;
		InstanceLimiter(InstanceLimiter&&) = delete;
		InstanceLimiter& operator=(InstanceLimiter&&) = delete;

	private:
		int instanceCnt{};

		~InstanceLimiter() = default;
		InstanceLimiter() = default;
	};


public:

	void Run()
	{
		MSG msg = {};

		while (true)
		{
			//Windowにメッセージが来てたら最優先で処理させる
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				nexus->Run();
			}
		}

	}

	aFourth()
	{
		//自身のインスタンス制限
		InstanceLimiter::CanInstantiate();

		//COMの初期化
		HRESULT hr = CoInitializeEx(0, COINITBASE_MULTITHREADED);
		ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "CoInitializeEx()でエラー", "aFourth.h");
		Logger::Log("CoInitializeEx", "aFourth.h");


		nexus = std::make_unique<Nexus>();
		
	}

	~aFourth() 
	{
		Logger::Entry("aFourth: Destructor");


		nexus.reset();
		Logger::Log("Delete Nexus", "aFourth.h");


		CoUninitialize();
		Logger::Log("CoUninitialize", "aFourth.h");


		Logger::End("aFourth: Destructor");

	};

private:


	std::unique_ptr<Nexus> nexus;
};

