#pragma once
#include "EngineInstanceLimiter.h"


//外部
#include "../Nexus/Nexus.h"

//シーン作成のために必要
#include "MiddleLayer/Scene/ScenePresetIncludes.h"
#include "MiddleLayer/Scene/SceneContextDiplomat/SceneContextDiplomat.h"
#include "MiddleLayer/Scene/SceneContextDiplomat/SceneExecutionAgent/SceneExecutionAgent.h"
#include "MiddleLayer/Scene/SceneContextDiplomat/SceneExecutionAgent/SceneExecutionAgentLicences.h"

template<typename... SceneTypes>
class aFourth
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void Run()
	{
		MSG msg = {};
		Nexus::aFourthProof proof;

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
				nexus->Run(proof);
			}
		}
	}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	aFourth(std::vector<std::string> const& correspondedSceneNames_)
	{
		Logger::Entry("EngineInterface: Constructor");

		correspondedSceneNames = correspondedSceneNames_;

		//自身のインスタンス制限
		EngineInstanceLimiter::CanInstantiate();

		InitializeInSequence<InitSequence::kCoInitializeEx>();
		InitializeInSequence<InitSequence::kLoadProjectFiles>();
		InitializeInSequence<InitSequence::kInstantiateNexus>();
		InitializeInSequence<InitSequence::kInstantiateScene>();
		InitializeInSequence<InitSequence::kNexusSecInit>();

		ErrorMessageOutput::Assert::DetectError(nextInit == InitSequence::kEnd, "初期化が正常に行われていない可能性がある", "EngineInterface.h");
		
		Logger::End("EngineInterface: Constructor");
	}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	~aFourth() 
	{
		Logger::Entry("EngineInterface: Destructor");


		nexus.reset();
		Logger::Log("Delete Nexus", "EngineInterface.h");


		CoUninitialize();
		Logger::Log("CoUninitialize", "EngineInterface.h");


		Logger::End("EngineInterface: Destructor");

	};
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

	enum class InitSequence
	{
		kCoInitializeEx,
		kLoadProjectFiles,
		kInstantiateNexus,
		kInstantiateScene,
		kNexusSecInit,

		kEnd
	}nextInit = InitSequence::kCoInitializeEx;

	template<InitSequence initSequence>
	void Init()
	{
		if constexpr (initSequence == InitSequence::kCoInitializeEx)
		{
			//COMの初期化
			HRESULT hr = CoInitializeEx(0, COINITBASE_MULTITHREADED);
			ErrorMessageOutput::Abort::DetectError(SUCCEEDED(hr), "CoInitializeEx()でエラー", "EngineInterface.h");
			Logger::Log("CoInitializeEx", "EngineInterface.h");
		}
		else if constexpr (initSequence == InitSequence::kInstantiateNexus)
		{
			//ネクサスのインスタンス化
			nexus = std::make_unique<Nexus>(Nexus::aFourthProof{});
			Logger::Log("Comp Instantiate Nexus", "EngineInterface.h");
		}
		else if constexpr (initSequence == InitSequence::kInstantiateScene)
		{
			//main.cppで指定されたシーンをインスタンス化する
			InstantiateScene();
			Logger::Log("Comp InstantiateScene", "EngineInterface.h");
		}
		else if constexpr (initSequence == InitSequence::kNexusSecInit)
		{
			nexus->SecondaryInit(Nexus::aFourthProof{});
			Logger::Log("Comp Nexus's SecondaryInit", "EngineInterface.h");
		}
		else if constexpr (initSequence == InitSequence::kLoadProjectFiles)
		{
			//Miyajisonの初期化
			auto* miyajison = Miyajison::Get();
			
			//ここでプロジェクト設定も初期化しちゃう
			ProjectConfig::Window::LoadData();

			//シーンの数を記録
			miyajison->WriteData<int>("ProjectConfig", { "numScene" }, (int)correspondedSceneNames.size());
			miyajison->Save();

		}


	}

	template<InitSequence next_>
	void InitializeInSequence()
	{
		ErrorMessageOutput::Assert::DetectError
		(
			nextInit == next_,
			"初期化が正常に行われていない可能性がある",
			"EngineInterface.h"
		);

		Init<next_>();

		nextInit = InitSequence((UINT)nextInit + 1);
	}


///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void InstantiateScene()
	{
		auto aFourthProof = Nexus::aFourthProof{};

		auto& sceneContext	= nexus->AccessContext<SceneContext>(aFourthProof);
		auto& cameraContext = nexus->AccessContext<CameraContext>(aFourthProof);
		auto& modelContext	= nexus->AccessContext<ModelContext>(aFourthProof);

		//シーンコンテキストのエージェントがシーン作成関数を呼び出す
		auto& agent = sceneContext.AccessDiplomat().Access<SceneContext::ExecutionAgent>();

		//シーンの数とシーンネームの数が一致しているかチェック
		auto const numScenes = sizeof...(SceneTypes);
		ErrorMessageOutput::Assert::DetectError
		(
			numScenes == correspondedSceneNames.size(),
			"シーンの数と、シーン名の数が合わへん",
			"EngineInterface.h"
		);

		//ProjectConfig.jsonにシーンの数を書き込む

		//シーン作成
		size_t cnt{};

		(
			agent.template CreateScene<SceneTypes>
			(
				SceneContext::ExecutionAgent::EngineInterfaceProof{},
				correspondedSceneNames[cnt++],
				cameraContext.AccessDiplomat(),
				modelContext.AccessDiplomat()
			), 
			...
		);	
	}
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///+///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::unique_ptr<Nexus> nexus;
	//生成するシーン名
	std::vector<std::string> correspondedSceneNames;

};

