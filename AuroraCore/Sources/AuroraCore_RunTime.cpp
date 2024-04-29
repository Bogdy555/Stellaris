#include "..\Headers\AuroraCore.hpp"



AuroraCore::RunTime::Application::Application() :
	On(false), ReturnValue(-1),
	CurrentMenu(_NullMenu),
	FrameTime(), LagTime(1.0f / 10.0f), SimulationSpeed(1.0f), Sync(60),
	InstanceHandle(NULL), CmdLine(nullptr), ShowCmd(SW_HIDE)
{

}

AuroraCore::RunTime::Application::~Application()
{
	AURORA_CORE_ASSERT_MSG(On == false, AURORA_CORE_STRING_PREFIX("Can not delete an application object that is running."));
}

int32_t AuroraCore::RunTime::Application::Run(const HINSTANCE _InstanceHandle, const LPWSTR _CmdLine, const int32_t _ShowCmd, const wchar_t* _SharedMemoryName, const wchar_t* _SharedMutexName)
{
	InstanceHandle = _InstanceHandle;
	CmdLine = _CmdLine;
	ShowCmd = _ShowCmd;

	Setup();
	while (On)
	{
		Update();
	}
	Stop();

	CurrentMenu = _NullMenu;

	FrameTime[_Previous].Reset();
	FrameTime[_Current].Reset();
	LagTime = 1.0f / 10.0f;
	SimulationSpeed = 1.0f;
	Sync = 60;

	InstanceHandle = NULL;
	CmdLine = nullptr;
	ShowCmd = SW_HIDE;

	int32_t _ReturnValue = ReturnValue;
	ReturnValue = -1;

	return _ReturnValue;
}

void AuroraCore::RunTime::Application::TurnOn()
{
	On = true;
}

void AuroraCore::RunTime::Application::Close(const int32_t _ReturnValue)
{
	On = false;
	ReturnValue = _ReturnValue;
}

void AuroraCore::RunTime::Application::SetCurrentMenu(const uint64_t _CurrentMenu)
{
	CurrentMenu = _CurrentMenu;
}

void AuroraCore::RunTime::Application::UpdateCurrentFrameTime()
{
	FrameTime[_Current].Stop();
}

void AuroraCore::RunTime::Application::SetLagTime(const float _LagTime)
{
	LagTime = _LagTime;
}

void AuroraCore::RunTime::Application::SetSimulationSpeed(const float _SimulationSpeed)
{
	SimulationSpeed = _SimulationSpeed;
}

void AuroraCore::RunTime::Application::SetSync(const uint64_t _Sync)
{
	Sync = _Sync;
}

const bool AuroraCore::RunTime::Application::CheckOn() const
{
	return On;
}

const int32_t AuroraCore::RunTime::Application::GetReturnValue() const
{
	return ReturnValue;
}

const uint64_t AuroraCore::RunTime::Application::GetCurrentMenu() const
{
	return CurrentMenu;
}

AuroraCore::Time::Timer& AuroraCore::RunTime::Application::GetFrameTime(const size_t _Index)
{
	return FrameTime[_Index];
}

const AuroraCore::Time::Timer& AuroraCore::RunTime::Application::GetFrameTime(const size_t _Index) const
{
	return FrameTime[_Index];
}

const float AuroraCore::RunTime::Application::GetTimeStep() const
{
	if (LagTime != 0.0f && FrameTime[_Previous] >= LagTime)
	{
		return LagTime * SimulationSpeed;
	}

	return FrameTime[_Previous] * SimulationSpeed;
}

const float AuroraCore::RunTime::Application::GetLagTime() const
{
	return LagTime;
}

const float AuroraCore::RunTime::Application::GetSimulationSpeed() const
{
	return SimulationSpeed;
}

const uint64_t AuroraCore::RunTime::Application::GetSync() const
{
	return Sync;
}

const HINSTANCE AuroraCore::RunTime::Application::GetInstanceHandle() const
{
	return InstanceHandle;
}

const LPWSTR AuroraCore::RunTime::Application::GetCmdLine() const
{
	return CmdLine;
}

const int32_t AuroraCore::RunTime::Application::GetShowCmd() const
{
	return ShowCmd;
}

const size_t AuroraCore::RunTime::Application::GetArgC() const
{
	return __argc;
}

const wchar_t* AuroraCore::RunTime::Application::GetArgV(const size_t _Index) const
{
	return __wargv[_Index];
}



AuroraCore::RunTime::Menu::Menu() : On(false), NextMenu(_NullMenu), ApplicationObj(nullptr)
{

}

AuroraCore::RunTime::Menu::~Menu()
{
	AURORA_CORE_ASSERT_MSG(On == false, AURORA_CORE_STRING_PREFIX("Can not delete a menu object that is running."));
}

void AuroraCore::RunTime::Menu::Run(Application* _ApplicationObj)
{
	if (!_ApplicationObj)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(AURORA_CORE_STRING_PREFIX("An application is required to run a menu."));
		return;
	}

	ApplicationObj = _ApplicationObj;

	Setup();
	while (On)
	{
		GetFrameTime(_Current).Start();

		Update();

		if (GetSync())
		{
			GetFrameTime(_Current).Stop();

			if (GetFrameTime(_Current) < 1.0f / (float)(GetSync()))
			{
				std::this_thread::sleep_for(std::chrono::microseconds((uint64_t)(floorf((1.0f / (float)(GetSync()) - GetFrameTime(_Current)) * 1000000.0f))));
			}
		}

		GetFrameTime(_Current).Stop();

		GetFrameTime(_Previous) = GetFrameTime(_Current);

		if (!ApplicationObj->CheckOn())
		{
			Close(_NullMenu);
		}
	}
	Stop();

	ApplicationObj->SetCurrentMenu(NextMenu);
	NextMenu = _NullMenu;

	ApplicationObj = nullptr;
}

void AuroraCore::RunTime::Menu::TurnOn()
{
	On = true;
}

void AuroraCore::RunTime::Menu::Close(const uint64_t _NextMenu)
{
	On = false;
	NextMenu = _NextMenu;
}

void AuroraCore::RunTime::Menu::UpdateCurrentFrameTime()
{
	ApplicationObj->UpdateCurrentFrameTime();
}

void AuroraCore::RunTime::Menu::SetLagTime(const float _LagTime)
{
	ApplicationObj->SetLagTime(_LagTime);
}

void AuroraCore::RunTime::Menu::SetSimulationSpeed(const float _SimulationSpeed)
{
	ApplicationObj->SetSimulationSpeed(_SimulationSpeed);
}

void AuroraCore::RunTime::Menu::SetSync(const uint64_t _Sync)
{
	ApplicationObj->SetSync(_Sync);
}

const bool AuroraCore::RunTime::Menu::CheckOn() const
{
	return On;
}

const uint64_t AuroraCore::RunTime::Menu::GetNextMenu() const
{
	return NextMenu;
}

AuroraCore::RunTime::Application* AuroraCore::RunTime::Menu::GetApplicationObj()
{
	return ApplicationObj;
}

const AuroraCore::RunTime::Application* AuroraCore::RunTime::Menu::GetApplicationObj() const
{
	return ApplicationObj;
}

AuroraCore::Time::Timer& AuroraCore::RunTime::Menu::GetFrameTime(const size_t _Index)
{
	return ApplicationObj->GetFrameTime(_Index);
}

const AuroraCore::Time::Timer& AuroraCore::RunTime::Menu::GetFrameTime(const size_t _Index) const
{
	return ApplicationObj->GetFrameTime(_Index);
}

const float AuroraCore::RunTime::Menu::GetTimeStep() const
{
	return ApplicationObj->GetTimeStep();
}

const float AuroraCore::RunTime::Menu::GetLagTime() const
{
	return ApplicationObj->GetLagTime();
}

const float AuroraCore::RunTime::Menu::GetSimulationSpeed() const
{
	return ApplicationObj->GetSimulationSpeed();
}

const uint64_t AuroraCore::RunTime::Menu::GetSync() const
{
	return ApplicationObj->GetSync();
}
