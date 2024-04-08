#include "..\Headers\Stellaris.hpp"



bool LoadFile(const wchar_t* _FileName, uint8_t** _Buff, size_t& _BuffSize, WAVEFORMATEX& _AudioInfo)
{
	FILE* _File = nullptr;

	_wfopen_s(&_File, _FileName, L"rb");

	if (!_File)
	{
		return false;
	}

	fseek(_File, 20, SEEK_SET);

	fread_s(&_AudioInfo.wFormatTag, 2, 2, 1, _File);
	fread_s(&_AudioInfo.nChannels, 2, 2, 1, _File);
	fread_s(&_AudioInfo.nSamplesPerSec, 4, 4, 1, _File);
	fread_s(&_AudioInfo.nAvgBytesPerSec, 4, 4, 1, _File);
	fread_s(&_AudioInfo.nBlockAlign, 2, 2, 1, _File);
	fread_s(&_AudioInfo.wBitsPerSample, 2, 2, 1, _File);

	fseek(_File, 40, SEEK_SET);

	uint32_t _AuxBuffSize = 0;

	fread_s(&_AuxBuffSize, 4, 4, 1, _File);

	_BuffSize = _AuxBuffSize;

	*_Buff = new uint8_t[_BuffSize];

	if (!*_Buff)
	{
		return false;
	}

	size_t _ReadSize = 0;

	while (_ReadSize < _BuffSize)
	{
		_ReadSize += fread_s((*_Buff) + _ReadSize, _BuffSize - _ReadSize, 1, _BuffSize - _ReadSize, _File);
	}

	fclose(_File);

	return true;
}



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	uint8_t* _Data = nullptr;
	size_t _Size = 0;
	WAVEFORMATEX _AudioInfo;

	if (!LoadFile(L"C:\\Users\\Bogdan\\source\\repos\\DirectSound\\DirectSound\\Files\\Test.wav", &_Data, _Size, _AudioInfo))
	{
		return -1;
	}

	if (CoInitializeEx(nullptr, COINIT_MULTITHREADED) != S_OK)
	{
		delete[] _Data;
		return -1;
	}

	if (!AuroraCore::Sound::UpdateDevices())
	{
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	AuroraCore::Sound::Context _Context;

	if (!_Context.Create(0))
	{
		AuroraCore::Sound::CleanDevices();
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	AuroraCore::Sound::Buffer3D _Buffer;

	if (!_Buffer.Create(_Context, _Size, _AudioInfo, _Data))
	{
		_Context.Destroy();
		AuroraCore::Sound::CleanDevices();
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	AuroraCore::Sound::Source3D _Source;

	if (!_Source.Create(_Context, _Buffer))
	{
		_Buffer.Destroy();
		_Context.Destroy();
		AuroraCore::Sound::CleanDevices();
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	if (!_Source.Play(true))
	{
		_Source.Destroy();
		_Buffer.Destroy();
		_Context.Destroy();
		AuroraCore::Sound::CleanDevices();
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	float _Time = 0.0f;

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		if (!_Source.SetPosition(AuroraCore::Math::Vec3f(5.0f * sin(_Time), 0.0f, 5.0f * cos(_Time))))
		{
			_Source.Destroy();
			_Buffer.Destroy();
			_Context.Destroy();
			AuroraCore::Sound::CleanDevices();
			CoUninitialize();
			delete[] _Data;
			return -1;
		}

		if (!_Context.CommitChanges())
		{
			_Source.Destroy();
			_Buffer.Destroy();
			_Context.Destroy();
			AuroraCore::Sound::CleanDevices();
			CoUninitialize();
			delete[] _Data;
			return -1;
		}

		_Time += 0.01f;

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	if (!_Source.Stop())
	{
		_Source.Destroy();
		_Buffer.Destroy();
		_Context.Destroy();
		AuroraCore::Sound::CleanDevices();
		CoUninitialize();
		delete[] _Data;
		return -1;
	}

	_Source.Destroy();
	_Buffer.Destroy();
	_Context.Destroy();
	AuroraCore::Sound::CleanDevices();
	CoUninitialize();
	delete[] _Data;

	return 0;
}
