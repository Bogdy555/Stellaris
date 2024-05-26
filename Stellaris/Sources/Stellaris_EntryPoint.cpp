#include "..\Headers\Stellaris.hpp"



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED) != S_OK)
	{
		MessageBox(NULL, AURORA_CORE_STRING_PREFIX("An unexpected error occurred."), AURORA_CORE_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		return -1;
	}

	if (!AuroraCore::Time::Init())
	{
		MessageBox(NULL, AURORA_CORE_STRING_PREFIX("An unexpected error occurred."), AURORA_CORE_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		CoUninitialize();
		return -1;
	}

	if (!AuroraCore::Graphics::GL::Load())
	{
		MessageBox(NULL, AURORA_CORE_STRING_PREFIX("An unexpected error occurred."), AURORA_CORE_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		AuroraCore::Time::Stop();
		CoUninitialize();
		return -1;
	}

	if (!AuroraCore::Networking::Init())
	{
		MessageBox(NULL, AURORA_CORE_STRING_PREFIX("An unexpected error occurred."), AURORA_CORE_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
		AuroraCore::Graphics::GL::Unload();
		AuroraCore::Time::Stop();
		CoUninitialize();
		return -1;
	}

	Stellaris::RunTime::Application* _Application = Stellaris::RunTime::Application::GetInstance();

	int32_t _ReturnValue = _Application->Run(_hInstance, _CmdLine, _ShowCmd, L"BSR_APP_SharedInstanceMemory", L"BSR_APP_SharedInstanceMutex");

	if (_ReturnValue != 0)
	{
		MessageBox(NULL, AURORA_CORE_STRING_PREFIX("An unexpected error occurred."), AURORA_CORE_STRING_PREFIX("Error!"), MB_OK | MB_ICONERROR);
	}

	AuroraCore::Networking::Stop();
	AuroraCore::Graphics::GL::Unload();
	AuroraCore::Time::Stop();
	CoUninitialize();

	return _ReturnValue;
}
