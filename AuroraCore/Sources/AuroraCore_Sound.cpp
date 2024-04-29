#include "..\Headers\AuroraCore.hpp"



static std::vector<AuroraCore::Sound::Device> _Devices;

const std::vector<AuroraCore::Sound::Device>& AuroraCore::Sound::Devices = _Devices;



float AuroraCore::Sound::CPUBuffer::GetTotalTime(const size_t _Size, const WAVEFORMATEX& _SoundInfo)
{
	if ((_SoundInfo.nChannels != 1 && _SoundInfo.nChannels != 2) || (_SoundInfo.wBitsPerSample != 8 && _SoundInfo.wBitsPerSample != 16) || _SoundInfo.nAvgBytesPerSec == 0)
	{
		return 0.0f;
	}

	return (float)(_Size) / (float)(_SoundInfo.nAvgBytesPerSec);
}

size_t AuroraCore::Sound::CPUBuffer::GetSecondIndex(const float _Second, const size_t _Size, const WAVEFORMATEX& _SoundInfo)
{
	float _TotalTime = GetTotalTime(_Size, _SoundInfo);

	if (_TotalTime == 0.0f)
	{
		return 0;
	}

	float _MappedSecond = _Second - _TotalTime * std::floor(_Second / _TotalTime);

	size_t _Result = (size_t)(_MappedSecond / _TotalTime * (float)(_Size));

	if (_SoundInfo.nChannels == 1)
	{
		if (_SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 2;
		}
	}
	if (_SoundInfo.nChannels == 2)
	{
		if (_SoundInfo.wBitsPerSample == 8)
		{
			_Result -= _Result % 2;
		}
		if (_SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 4;
		}
	}

	return _Result;
}

float AuroraCore::Sound::CPUBuffer::GetIndexSecond(const size_t _Index, const size_t _Size, const WAVEFORMATEX& _SoundInfo)
{
	float _TotalTime = GetTotalTime(_Size, _SoundInfo);

	if (_TotalTime == 0.0f)
	{
		return 0.0f;
	}

	return _TotalTime * (float)(_Index % _Size) / (float)(_Size);
}

uint8_t* AuroraCore::Sound::CPUBuffer::LoadSoundFile(const wchar_t* _Path, size_t& _Size, WAVEFORMATEX& _SoundInfo)
{
	_Size = 0;
	_SoundInfo = { 0 };

	if (!_Path)
	{
		return nullptr;
	}

	FILE* _File = nullptr;

	_wfopen_s(&_File, _Path, L"rb");

	if (!_File)
	{
		return nullptr;
	}

	{
		char _MagicNumbers[5];

		if (fread(_MagicNumbers, 1, 4, _File) != 4)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		_MagicNumbers[4] = '\0';

		if (strcmp(_MagicNumbers, "RIFF") != 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}
	}

	{
		if (fseek(_File, 0, SEEK_END) != 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		int32_t _TotalFileSize = ftell(_File) - 8;

		if (_TotalFileSize == -9)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		if (fseek(_File, 4, SEEK_SET) != 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		int32_t _ReadFileSize = 0;

		if (fread(&_ReadFileSize, 4, 1, _File) != 1)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		if (_ReadFileSize != _TotalFileSize)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}
	}

	{
		char _MagicNumbers[9];

		if (fread(_MagicNumbers, 1, 8, _File) != 8)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		_MagicNumbers[8] = '\0';

		if (strcmp(_MagicNumbers, "WAVEfmt ") != 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}
	}

	{
		uint32_t _SubChunkSize = 0;

		if (fread(&_SubChunkSize, 4, 1, _File) != 1)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		if (_SubChunkSize != 16)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}
	}

	if (fread(&_SoundInfo.wFormatTag, 2, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.wFormatTag != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(&_SoundInfo.nChannels, 2, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nChannels != 1 && _SoundInfo.nChannels != 2)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(&_SoundInfo.nSamplesPerSec, 4, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nSamplesPerSec == 0)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(&_SoundInfo.nAvgBytesPerSec, 4, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nAvgBytesPerSec == 0)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(&_SoundInfo.nBlockAlign, 2, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nBlockAlign == 0)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(&_SoundInfo.wBitsPerSample, 2, 1, _File) != 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.wBitsPerSample != 8 && _SoundInfo.wBitsPerSample != 16)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	{
		char _MagicNumbers[5];

		if (fread(_MagicNumbers, 1, 4, _File) != 4)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		_MagicNumbers[4] = '\0';

		if (strcmp(_MagicNumbers, "data") != 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}
	}

	{
		uint32_t _BufferSize = 0;

		if (fread(&_BufferSize, 4, 1, _File) != 1)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		if (_BufferSize == 0)
		{
			_Size = 0;
			_SoundInfo = { 0 };
			fclose(_File);
			return nullptr;
		}

		_Size = _BufferSize;
	}

	if (_SoundInfo.wBitsPerSample == 16 && _Size % 2 == 1)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nBlockAlign != _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (_SoundInfo.nAvgBytesPerSec != _SoundInfo.nSamplesPerSec * _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	uint8_t* _Data = new uint8_t[_Size];

	if (_Data == nullptr)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

	if (fread(_Data, 1, _Size, _File) != _Size)
	{
		delete[] _Data;
		_Size = 0;
		_SoundInfo = { 0 };
		fclose(_File);
		return nullptr;
	}

#ifdef AURORA_CORE_BIG_ENDIAN

	if (_SoundInfo.wBitsPerSample == 16)
	{
		for (size_t _Index = 0; _Index < _Size / 2; _Index++)
		{
			uint8_t _Aux = _Data[_Index * 2 + 0];
			_Data[_Index * 2 + 0] = _Data[_Index * 2 + 1];
			_Data[_Index * 2 + 1] = _Aux;
		}
	}

#endif

	fclose(_File);

	return _Data;
}

uint8_t* AuroraCore::Sound::CPUBuffer::LoadSoundResource(const HINSTANCE _InstanceHandle, const uint32_t _ResourceId, size_t& _Size, WAVEFORMATEX& _SoundInfo)
{
	_Size = 0;
	_SoundInfo = { 0 };

	HRSRC _ResourceHandle = FindResource(_InstanceHandle, MAKEINTRESOURCE(_ResourceId), MAKEINTRESOURCE(AURORA_CORE_WAV_RESOURCE));

	if (!_ResourceHandle)
	{
		return nullptr;
	}

	_Size = SizeofResource(_InstanceHandle, _ResourceHandle);

	if (_Size <= 44)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_Size -= 44;

	HGLOBAL _ResourceMemory = LoadResource(_InstanceHandle, _ResourceHandle);

	if (!_ResourceMemory)
	{
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (((char*)(_ResourceMemory))[0] != 'R' || ((char*)(_ResourceMemory))[1] != 'I' || ((char*)(_ResourceMemory))[2] != 'F' || ((char*)(_ResourceMemory))[3] != 'F')
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	{
		int32_t _TotalFileSize = (int32_t)(_Size) + 44 - 8;

		int32_t _ReadFileSize = *(int32_t*)((uint8_t*)(_ResourceMemory) + 4);

		if (_ReadFileSize != _TotalFileSize)
		{
			FreeResource(_ResourceMemory);
			_Size = 0;
			_SoundInfo = { 0 };
			return nullptr;
		}
	}

	if (((char*)(_ResourceMemory))[8] != 'W' || ((char*)(_ResourceMemory))[9] != 'A' || ((char*)(_ResourceMemory))[10] != 'V' || ((char*)(_ResourceMemory))[11] != 'E')
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (((char*)(_ResourceMemory))[12] != 'f' || ((char*)(_ResourceMemory))[13] != 'm' || ((char*)(_ResourceMemory))[14] != 't' || ((char*)(_ResourceMemory))[15] != ' ')
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (*(uint32_t*)((uint8_t*)(_ResourceMemory) + 16) != 16)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.wFormatTag = *(uint16_t*)((uint8_t*)(_ResourceMemory) + 20);

	if (_SoundInfo.wFormatTag != 1)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.nChannels = *(uint16_t*)((uint8_t*)(_ResourceMemory) + 22);

	if (_SoundInfo.nChannels != 1 && _SoundInfo.nChannels != 2)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.nSamplesPerSec = *(uint32_t*)((uint8_t*)(_ResourceMemory) + 24);

	if (_SoundInfo.nSamplesPerSec == 0)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.nAvgBytesPerSec = *(uint32_t*)((uint8_t*)(_ResourceMemory) + 28);

	if (_SoundInfo.nAvgBytesPerSec == 0)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.nBlockAlign = *(uint16_t*)((uint8_t*)(_ResourceMemory) + 32);

	if (_SoundInfo.nBlockAlign == 0)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	_SoundInfo.wBitsPerSample = *(uint16_t*)((uint8_t*)(_ResourceMemory) + 34);

	if (_SoundInfo.wBitsPerSample != 8 && _SoundInfo.wBitsPerSample != 16)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (((char*)(_ResourceMemory))[36] != 'd' || ((char*)(_ResourceMemory))[37] != 'a' || ((char*)(_ResourceMemory))[38] != 't' || ((char*)(_ResourceMemory))[39] != 'a')
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	{
		uint32_t _BufferSize = *(uint32_t*)((uint8_t*)(_ResourceMemory) + 40);

		if (_BufferSize == 0)
		{
			FreeResource(_ResourceMemory);
			_Size = 0;
			_SoundInfo = { 0 };
			return nullptr;
		}

		if (_Size != _BufferSize)
		{
			FreeResource(_ResourceMemory);
			_Size = 0;
			_SoundInfo = { 0 };
			return nullptr;
		}
	}

	if (_SoundInfo.wBitsPerSample == 16 && _Size % 2 == 1)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (_SoundInfo.nBlockAlign != _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	if (_SoundInfo.nAvgBytesPerSec != _SoundInfo.nSamplesPerSec * _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	uint8_t* _Data = new uint8_t[_Size];

	if (_Data == nullptr)
	{
		FreeResource(_ResourceMemory);
		_Size = 0;
		_SoundInfo = { 0 };
		return nullptr;
	}

	for (size_t _Index = 0; _Index < _Size; _Index++)
	{
		_Data[_Index] = *((uint8_t*)(_ResourceMemory) + _Index);
	}

	FreeResource(_ResourceMemory);

	return _Data;
}

bool AuroraCore::Sound::CPUBuffer::SaveSoundFile(const wchar_t* _Path, const uint8_t* _Data, const size_t _Size, const WAVEFORMATEX& _SoundInfo)
{
	if (!_Path)
	{
		return false;
	}

	if (!_Data || !_Size)
	{
		return false;
	}

	if (_SoundInfo.wFormatTag != 1 || (_SoundInfo.nChannels != 1 && _SoundInfo.nChannels != 2) || _SoundInfo.nSamplesPerSec == 0 || _SoundInfo.nAvgBytesPerSec == 0 || _SoundInfo.nBlockAlign == 0 || (_SoundInfo.wBitsPerSample != 8 && _SoundInfo.wBitsPerSample != 16) || (_SoundInfo.wBitsPerSample == 16 && _Size % 2 == 1) || (_SoundInfo.nBlockAlign != _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8) || (_SoundInfo.nAvgBytesPerSec != _SoundInfo.nSamplesPerSec * _SoundInfo.nChannels * _SoundInfo.wBitsPerSample / 8))
	{
		return false;
	}

	FILE* _File = nullptr;

	_wfopen_s(&_File, _Path, L"wb");

	if (!_File)
	{
		return false;
	}

	if (fwrite("RIFF    WAVEfmt ", 1, 16, _File) != 16)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	{
		uint32_t _SubChunkSize = 16;

		if (fwrite(&_SubChunkSize, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}
	}

	if (fwrite(&_SoundInfo.wFormatTag, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&_SoundInfo.nChannels, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&_SoundInfo.nSamplesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&_SoundInfo.nAvgBytesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&_SoundInfo.nBlockAlign, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&_SoundInfo.wBitsPerSample, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite("data", 1, 4, _File) != 4)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	{
		uint32_t _BufferSize = (uint32_t)(_Size);

		if (fwrite(&_BufferSize, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}
	}

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (fwrite(_Data, 1, _Size, _File) != _Size)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (_SoundInfo.wBitsPerSample == 8)
	{
		if (fwrite(_Data, 1, _Size, _File) != _Size)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}
	}
	else
	{
		for (size_t _Index = 0; _Index < _Size / 2; _Index++)
		{
			if (fwrite(_Data + _Index * 2 + 1, 1, 1, _File) != 1)
			{
				fclose(_File);
				_wremove(_Path);
				return false;
			}

			if (fwrite(_Data + _Index * 2 + 0, 1, 1, _File) != 1)
			{
				fclose(_File);
				_wremove(_Path);
				return false;
			}
		}
	}

#endif

	{
		int32_t _FileSize = ftell(_File) - 8;

		if (_FileSize == -9)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}

		if (fseek(_File, 4, SEEK_SET) != 0)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}

		if (fwrite(&_FileSize, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}
	}

	fclose(_File);

	return true;
}



static BOOL CALLBACK GetDevices(LPGUID _Id, LPCWSTR _Name, LPCWSTR _Driver, LPVOID _Context)
{
	if (_Id == nullptr)
	{
		return TRUE;
	}

	AuroraCore::Sound::Device _Device;

	_Device.Id = _Id;
	_Device.Name = std::move(std::wstring(_Name));
	_Device.Driver = std::move(std::wstring(_Driver));

	_Devices.emplace_back(_Device);

	return TRUE;
}

bool AuroraCore::Sound::UpdateDevices()
{
	_Devices.clear();

	HRESULT _Result = DirectSoundEnumerate(GetDevices, nullptr);

	if (_Result != S_OK)
	{
		_Devices.clear();
		return false;
	}

	return true;
}

void AuroraCore::Sound::CleanDevices()
{
	_Devices.clear();
}

size_t AuroraCore::Sound::GetDefaultDeviceIndex()
{
	IMMDeviceEnumerator* _DeviceEnumerator = nullptr;

	HRESULT _Result = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)(&_DeviceEnumerator));

	if (_Result != S_OK)
	{
		return MAXSIZE_T;
	}

	IMMDevice* _Device = nullptr;

	_Result = _DeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &_Device);

	if (_Result != S_OK)
	{
		AURORA_CORE_COM_RELEASE(_DeviceEnumerator);
		return MAXSIZE_T;
	}

	LPWSTR _Name = nullptr;

	_Result = _Device->GetId(&_Name);

	if (_Result != S_OK)
	{
		AURORA_CORE_COM_RELEASE(_Device);
		AURORA_CORE_COM_RELEASE(_DeviceEnumerator);
		return MAXSIZE_T;
	}

	size_t _IndexDevice = MAXSIZE_T;

	for (size_t _Index = 0; _Index < Devices.size(); _Index++)
	{
		if (Devices[_Index].Driver == _Name)
		{
			_IndexDevice = _Index;
			break;
		}
	}

	CoTaskMemFree(_Name);
	AURORA_CORE_COM_RELEASE(_Device);
	AURORA_CORE_COM_RELEASE(_DeviceEnumerator);

	return _IndexDevice;
}



AuroraCore::Sound::Context::Context() : DirectSoundContext(nullptr), PrimaryBuffer(nullptr), Listener(nullptr)
{

}

AuroraCore::Sound::Context::Context(Context&& _Other) noexcept : DirectSoundContext(_Other.DirectSoundContext), PrimaryBuffer(_Other.PrimaryBuffer), Listener(_Other.Listener)
{
	_Other.DirectSoundContext = nullptr;
	_Other.PrimaryBuffer = nullptr;
	_Other.Listener = nullptr;
}

AuroraCore::Sound::Context::~Context()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("The sound context was not cleaned up!"));
}

bool AuroraCore::Sound::Context::Create(const size_t _DeviceIndex)
{
	Destroy();

	if (_DeviceIndex >= Devices.size())
	{
		return false;
	}

	HRESULT _Result = DirectSoundCreate8(Devices[_DeviceIndex].Id, &DirectSoundContext, nullptr);

	if (_Result != S_OK)
	{
		return false;
	}

	_Result = DirectSoundContext->SetCooperativeLevel(GetDesktopWindow(), DSSCL_PRIORITY);

	if (_Result != S_OK)
	{
		Destroy();
		return false;
	}

	DSBUFFERDESC _PrimaryBufferDesc = { 0 };

	_PrimaryBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_PrimaryBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME;
	_PrimaryBufferDesc.dwBufferBytes = 0;
	_PrimaryBufferDesc.dwReserved = 0;
	_PrimaryBufferDesc.lpwfxFormat = nullptr;
	_PrimaryBufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	_Result = DirectSoundContext->CreateSoundBuffer(&_PrimaryBufferDesc, &PrimaryBuffer, nullptr);

	if (_Result != S_OK)
	{
		Destroy();
		return false;
	}

	WAVEFORMATEX _PrimaryBufferFormat = { 0 };

	_PrimaryBufferFormat.wFormatTag = WAVE_FORMAT_PCM;
	_PrimaryBufferFormat.nChannels = 2;
	_PrimaryBufferFormat.nSamplesPerSec = 44100;
	_PrimaryBufferFormat.nAvgBytesPerSec = (44100 * 16 * 2) / 8;
	_PrimaryBufferFormat.nBlockAlign = 4;
	_PrimaryBufferFormat.wBitsPerSample = 16;
	_PrimaryBufferFormat.cbSize = 0;

	_Result = PrimaryBuffer->SetFormat(&_PrimaryBufferFormat);

	if (_Result != S_OK)
	{
		Destroy();
		return false;
	}

	_Result = PrimaryBuffer->QueryInterface(IID_IDirectSound3DListener8, (void**)(&Listener));

	if (_Result != S_OK)
	{
		Destroy();
		return false;
	}

	return true;
}

void AuroraCore::Sound::Context::Destroy()
{
	AURORA_CORE_COM_RELEASE(Listener);
	AURORA_CORE_COM_RELEASE(PrimaryBuffer);
	AURORA_CORE_COM_RELEASE(DirectSoundContext);
}

bool AuroraCore::Sound::Context::SetVolume(const float _Volume)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = PrimaryBuffer->SetVolume(DSBVOLUME_MIN + (LONG)((float)(DSBVOLUME_MAX - DSBVOLUME_MIN) * _Volume));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Context::SetPosition(const Math::Vec3f& _Position, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetPosition(_Position.x, _Position.y, -_Position.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Context::SetOrientation(const Math::Vec3f& _Front, const Math::Vec3f& _Up, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetOrientation(_Front.x, _Front.y, -_Front.z, _Up.x, _Up.y, -_Up.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Context::SetVelocity(const Math::Vec3f& _Velocity, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetVelocity(_Velocity.x, _Velocity.y, -_Velocity.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

const bool AuroraCore::Sound::Context::GetVolume(float& _Volume) const
{
	if (!CheckCreated())
	{
		return false;
	}

	LONG _AuxVolume = 0;

	HRESULT _Result = PrimaryBuffer->GetVolume(&_AuxVolume);

	if (_Result != S_OK)
	{
		return false;
	}

	_Volume = (float)(_AuxVolume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);

	return true;
}

const bool AuroraCore::Sound::Context::GetPosition(Math::Vec3f& _Position) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxPosition;

	HRESULT _Result = Listener->GetPosition(&_AuxPosition);

	if (_Result != S_OK)
	{
		return false;
	}

	_Position.x = _AuxPosition.x;
	_Position.y = _AuxPosition.y;
	_Position.z = -_AuxPosition.z;

	return true;
}

const bool AuroraCore::Sound::Context::GetOrientation(Math::Vec3f& _Front, Math::Vec3f& _Up) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxFront;

	D3DVECTOR _AuxUp;

	HRESULT _Result = Listener->GetOrientation(&_AuxFront, &_AuxUp);

	if (_Result != S_OK)
	{
		return false;
	}

	_Front.x = _AuxFront.x;
	_Front.y = _AuxFront.y;
	_Front.z = -_AuxFront.z;

	_Up.x = _AuxUp.x;
	_Up.y = _AuxUp.y;
	_Up.z = -_AuxUp.z;

	return true;
}

const bool AuroraCore::Sound::Context::GetVelocity(Math::Vec3f& _Velocity) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxVelocity;

	HRESULT _Result = Listener->GetVelocity(&_AuxVelocity);

	if (_Result != S_OK)
	{
		return false;
	}

	_Velocity.x = _AuxVelocity.x;
	_Velocity.y = _AuxVelocity.y;
	_Velocity.z = -_AuxVelocity.z;

	return true;
}

bool AuroraCore::Sound::Context::CommitChanges()
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->CommitDeferredSettings();

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

const bool AuroraCore::Sound::Context::CheckCreated() const
{
	return DirectSoundContext != nullptr;
}

AuroraCore::Sound::Context& AuroraCore::Sound::Context::operator= (Context&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound context until this one is free!"));

	DirectSoundContext = _Other.DirectSoundContext;
	PrimaryBuffer = _Other.PrimaryBuffer;
	Listener = _Other.Listener;

	_Other.DirectSoundContext = nullptr;
	_Other.PrimaryBuffer = nullptr;
	_Other.Listener = nullptr;

	return *this;
}



AuroraCore::Sound::Buffer::Buffer() : DirectSoundBuffer(nullptr), Size(0), SoundInfo({0})
{

}

AuroraCore::Sound::Buffer::Buffer(Buffer&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer), Size(_Other.Size), SoundInfo(_Other.SoundInfo)
{
	_Other.DirectSoundBuffer = nullptr;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
}

AuroraCore::Sound::Buffer::~Buffer()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Sound buffer was not cleaned up!"));
}

bool AuroraCore::Sound::Buffer::Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _SoundInfo, const uint8_t* _Data)
{
	Destroy();

	if (!_Context.CheckCreated() || _Size == 0)
	{
		return false;
	}

	WAVEFORMATEX _BufferSoundInfo = _SoundInfo;

	DSBUFFERDESC _BufferDesc = { 0 };

	_BufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_BufferDesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	_BufferDesc.dwBufferBytes = (DWORD)(_Size);
	_BufferDesc.dwReserved = 0;
	_BufferDesc.lpwfxFormat = &_BufferSoundInfo;
	_BufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	HRESULT _Result = _Context.DirectSoundContext->CreateSoundBuffer(&_BufferDesc, &DirectSoundBuffer, nullptr);

	if (_Result != S_OK)
	{
		return false;
	}

	if (_Data)
	{
		uint8_t* _Buff1 = nullptr;
		uint8_t* _Buff2 = nullptr;
		size_t _BuffSize1 = 0;
		size_t _BuffSize2 = 0;

		if (!Lock(0, _Size, &_Buff1, _BuffSize1, &_Buff2, _BuffSize2))
		{
			Destroy();
			return false;
		}

		if (_BuffSize1 != _Size || _Buff2 != nullptr || _BuffSize2 != 0)
		{
			Unlock(_Buff1, _BuffSize1, _Buff2, _BuffSize2);
			Destroy();
			return false;
		}

		for (size_t _Index = 0; _Index < _Size; _Index++)
		{
			_Buff1[_Index] = _Data[_Index];
		}

		if (!Unlock(_Buff1, _BuffSize1, _Buff2, _BuffSize2))
		{
			Destroy();
			return false;
		}
	}

	Size = _Size;
	SoundInfo = _SoundInfo;

	return true;
}

void AuroraCore::Sound::Buffer::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
	Size = 0;
	SoundInfo = { 0 };
}

bool AuroraCore::Sound::Buffer::Lock(const size_t _Offset, const size_t _Size, uint8_t** _Buff1, size_t& _BuffSize1, uint8_t** _Buff2, size_t& _BuffSize2)
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxBuffSize1 = 0;
	DWORD _AuxBuffSize2 = 0;

	HRESULT _Result = DirectSoundBuffer->Lock((DWORD)(_Offset), (DWORD)(_Size), (void**)(_Buff1), &_AuxBuffSize1, (void**)(_Buff2), &_AuxBuffSize2, NULL);

	if (_Result != S_OK)
	{
		return false;
	}

	_BuffSize1 = _AuxBuffSize1;
	_BuffSize2 = _AuxBuffSize2;

	return true;
}

bool AuroraCore::Sound::Buffer::Unlock(uint8_t* _Buff1, const size_t _BuffSize1, uint8_t* _Buff2, const size_t _BuffSize2)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->Unlock(_Buff1, (DWORD)(_BuffSize1), _Buff2, (DWORD)(_BuffSize2));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

const bool AuroraCore::Sound::Buffer::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

const float AuroraCore::Sound::Buffer::GetTotalTime() const
{
	if (!CheckCreated() || (SoundInfo.nChannels != 1 && SoundInfo.nChannels != 2) || (SoundInfo.wBitsPerSample != 8 && SoundInfo.wBitsPerSample != 16) || SoundInfo.nAvgBytesPerSec == 0)
	{
		return 0.0f;
	}

	return (float)(Size) / (float)(SoundInfo.nAvgBytesPerSec);
}

const size_t AuroraCore::Sound::Buffer::GetSecondIndex(const float _Second) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0;
	}

	float _MappedSecond = _Second - _TotalTime * std::floor(_Second / _TotalTime);

	size_t _Result = (size_t)(_MappedSecond / _TotalTime * (float)(Size));

	if (SoundInfo.nChannels == 1)
	{
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 2;
		}
	}
	if (SoundInfo.nChannels == 2)
	{
		if (SoundInfo.wBitsPerSample == 8)
		{
			_Result -= _Result % 2;
		}
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 4;
		}
	}

	return _Result;
}

const float AuroraCore::Sound::Buffer::GetIndexSecond(const size_t _Index) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0.0f;
	}

	return _TotalTime * (float)(_Index % Size) / (float)(Size);
}

const size_t AuroraCore::Sound::Buffer::GetSize() const
{
	return Size;
}

const WAVEFORMATEX AuroraCore::Sound::Buffer::GetSoundInfo() const
{
	return SoundInfo;
}

AuroraCore::Sound::Buffer& AuroraCore::Sound::Buffer::operator= (Buffer&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound buffer until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;
	Size = _Other.Size;
	SoundInfo = _Other.SoundInfo;

	_Other.DirectSoundBuffer = nullptr;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };

	return *this;
}



AuroraCore::Sound::Buffer3D::Buffer3D() : DirectSoundBuffer(nullptr), Size(0), SoundInfo({0})
{

}

AuroraCore::Sound::Buffer3D::Buffer3D(Buffer3D&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer), Size(_Other.Size), SoundInfo(_Other.SoundInfo)
{
	_Other.DirectSoundBuffer = nullptr;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
}

AuroraCore::Sound::Buffer3D::~Buffer3D()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("3D sound buffer was not cleaned up!"));
}

bool AuroraCore::Sound::Buffer3D::Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _SoundInfo, const uint8_t* _Data)
{
	Destroy();

	if (!_Context.CheckCreated() || _Size == 0 || _SoundInfo.nChannels != 1)
	{
		return false;
	}

	WAVEFORMATEX _BufferSoundInfo = _SoundInfo;

	DSBUFFERDESC _BufferDesc = { 0 };

	_BufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_BufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	_BufferDesc.dwBufferBytes = (DWORD)(_Size);
	_BufferDesc.dwReserved = 0;
	_BufferDesc.lpwfxFormat = &_BufferSoundInfo;
	_BufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;

	HRESULT _Result = _Context.DirectSoundContext->CreateSoundBuffer(&_BufferDesc, &DirectSoundBuffer, nullptr);

	if (_Result != S_OK)
	{
		return false;
	}

	if (_Data)
	{
		uint8_t* _Buff1 = nullptr;
		uint8_t* _Buff2 = nullptr;
		size_t _BuffSize1 = 0;
		size_t _BuffSize2 = 0;

		if (!Lock(0, _Size, &_Buff1, _BuffSize1, &_Buff2, _BuffSize2))
		{
			Destroy();
			return false;
		}

		if (_BuffSize1 != _Size || _Buff2 != nullptr || _BuffSize2 != 0)
		{
			Unlock(_Buff1, _BuffSize1, _Buff2, _BuffSize2);
			Destroy();
			return false;
		}

		for (size_t _Index = 0; _Index < _Size; _Index++)
		{
			_Buff1[_Index] = _Data[_Index];
		}

		if (!Unlock(_Buff1, _BuffSize1, _Buff2, _BuffSize2))
		{
			Destroy();
			return false;
		}
	}

	Size = _Size;
	SoundInfo = _SoundInfo;

	return true;
}

void AuroraCore::Sound::Buffer3D::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
	Size = 0;
	SoundInfo = { 0 };
}

bool AuroraCore::Sound::Buffer3D::Lock(const size_t _Offset, const size_t _Size, uint8_t** _Buff1, size_t& _BuffSize1, uint8_t** _Buff2, size_t& _BuffSize2)
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxBuffSize1 = 0;
	DWORD _AuxBuffSize2 = 0;

	HRESULT _Result = DirectSoundBuffer->Lock((DWORD)(_Offset), (DWORD)(_Size), (void**)(_Buff1), &_AuxBuffSize1, (void**)(_Buff2), &_AuxBuffSize2, NULL);

	if (_Result != S_OK)
	{
		return false;
	}

	_BuffSize1 = _AuxBuffSize1;
	_BuffSize2 = _AuxBuffSize2;

	return true;
}

bool AuroraCore::Sound::Buffer3D::Unlock(uint8_t* _Buff1, const size_t _BuffSize1, uint8_t* _Buff2, const size_t _BuffSize2)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->Unlock(_Buff1, (DWORD)(_BuffSize1), _Buff2, (DWORD)(_BuffSize2));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

const bool AuroraCore::Sound::Buffer3D::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

const float AuroraCore::Sound::Buffer3D::GetTotalTime() const
{
	if (!CheckCreated() || (SoundInfo.nChannels != 1 && SoundInfo.nChannels != 2) || (SoundInfo.wBitsPerSample != 8 && SoundInfo.wBitsPerSample != 16) || SoundInfo.nAvgBytesPerSec == 0)
	{
		return 0.0f;
	}

	return (float)(Size) / (float)(SoundInfo.nAvgBytesPerSec);
}

const size_t AuroraCore::Sound::Buffer3D::GetSecondIndex(const float _Second) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0;
	}

	float _MappedSecond = _Second - _TotalTime * std::floor(_Second / _TotalTime);

	size_t _Result = (size_t)(_MappedSecond / _TotalTime * (float)(Size));

	if (SoundInfo.nChannels == 1)
	{
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 2;
		}
	}
	if (SoundInfo.nChannels == 2)
	{
		if (SoundInfo.wBitsPerSample == 8)
		{
			_Result -= _Result % 2;
		}
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 4;
		}
	}

	return _Result;
}

const float AuroraCore::Sound::Buffer3D::GetIndexSecond(const size_t _Index) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0.0f;
	}

	return _TotalTime * (float)(_Index % Size) / (float)(Size);
}

const size_t AuroraCore::Sound::Buffer3D::GetSize() const
{
	return Size;
}

const WAVEFORMATEX AuroraCore::Sound::Buffer3D::GetSoundInfo() const
{
	return SoundInfo;
}

AuroraCore::Sound::Buffer3D& AuroraCore::Sound::Buffer3D::operator= (Buffer3D&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another 3D sound buffer until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;
	Size = _Other.Size;
	SoundInfo = _Other.SoundInfo;

	_Other.DirectSoundBuffer = nullptr;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };

	return *this;
}



AuroraCore::Sound::Source::Source() : DirectSoundBuffer(nullptr), Playing(false), Looping(false), Size(0), SoundInfo({0}), PlayTime(), StartTime(0.0f)
{

}

AuroraCore::Sound::Source::Source(Source&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer), Playing(_Other.Playing), Looping(_Other.Looping), Size(_Other.Size), SoundInfo(_Other.SoundInfo), PlayTime(std::move(_Other.PlayTime)), StartTime(_Other.StartTime)
{
	_Other.DirectSoundBuffer = nullptr;
	_Other.Playing = false;
	_Other.Looping = false;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
	_Other.StartTime = 0.0f;
}

AuroraCore::Sound::Source::~Source()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("The sound source was not cleaned up!"));
}

bool AuroraCore::Sound::Source::Create(Context& _Context, Buffer& _Buffer)
{
	Destroy();

	if (!_Context.CheckCreated() || !_Buffer.CheckCreated())
	{
		return false;
	}

	IDirectSoundBuffer* _TempBuffer = nullptr;

	HRESULT _Result = _Context.DirectSoundContext->DuplicateSoundBuffer(_Buffer.DirectSoundBuffer, &_TempBuffer);

	if (_Result != S_OK)
	{
		return false;
	}

	_Result = _TempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)(&DirectSoundBuffer));

	if (_Result != S_OK)
	{
		AURORA_CORE_COM_RELEASE(_TempBuffer);
		return false;
	}

	AURORA_CORE_COM_RELEASE(_TempBuffer);

	Size = _Buffer.GetSize();
	SoundInfo = _Buffer.GetSoundInfo();

	return true;
}

void AuroraCore::Sound::Source::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
	Playing = false;
	Looping = false;
	Size = 0;
	SoundInfo = { 0 };
	PlayTime.Reset();
	StartTime = 0.0f;
}

bool AuroraCore::Sound::Source::SetVolume(const float _Volume)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->SetVolume(DSBVOLUME_MIN + (LONG)((float)(DSBVOLUME_MAX - DSBVOLUME_MIN) * _Volume));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source::SetFrequency(const float _Frequency)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->SetFrequency(DSBFREQUENCY_MIN + (DWORD)((float)(DSBFREQUENCY_MAX - DSBFREQUENCY_MIN) * _Frequency));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source::SetCurrentPosition(const size_t _CurrentPosition)
{
	if (!CheckCreated())
	{
		return false;
	}

	bool _Playing = Playing;
	bool _Looping = Looping;

	if (Playing)
	{
		Stop();
	}

	StartTime = GetIndexSecond(_CurrentPosition);

	HRESULT _Result = DirectSoundBuffer->SetCurrentPosition((DWORD)(_CurrentPosition));

	if (_Result != S_OK)
	{
		return false;
	}

	if (_Playing)
	{
		if (!Play(_Looping))
		{
			return false;
		}
	}

	return true;
}

const bool AuroraCore::Sound::Source::GetVolume(float& _Volume) const
{
	if (!CheckCreated())
	{
		return false;
	}

	LONG _AuxVolume = 0;

	HRESULT _Result = DirectSoundBuffer->GetVolume(&_AuxVolume);

	if (_Result != S_OK)
	{
		return false;
	}

	_Volume = (float)(_AuxVolume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);

	return true;
}

const bool AuroraCore::Sound::Source::GetFrequency(float& _Frequency) const
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxFrequency = 0;

	HRESULT _Result = DirectSoundBuffer->GetFrequency(&_AuxFrequency);

	if (_Result != S_OK)
	{
		return false;
	}

	_Frequency = (float)(_AuxFrequency - DSBFREQUENCY_MIN) / (float)(DSBFREQUENCY_MAX - DSBFREQUENCY_MIN);

	return true;
}

const bool AuroraCore::Sound::Source::GetCurrentPosition(size_t& _CurrentPosition) const
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxCurrentPosition = 0;

	HRESULT _Result = DirectSoundBuffer->GetCurrentPosition(&_AuxCurrentPosition, nullptr);

	if (_Result != S_OK)
	{
		return false;
	}

	_CurrentPosition = _AuxCurrentPosition;

	return true;
}

bool AuroraCore::Sound::Source::Play(const bool _Looping)
{
	if (!CheckCreated())
	{
		return false;
	}

	if (Playing)
	{
		Stop();
	}

	HRESULT _Result = DirectSoundBuffer->Play(0, 0, _Looping ? DSBPLAY_LOOPING : NULL);

	if (_Result != S_OK)
	{
		return false;
	}

	Playing = true;
	Looping = _Looping;
	PlayTime.Reset();

	return true;
}

bool AuroraCore::Sound::Source::Stop()
{
	if (!CheckCreated())
	{
		return false;
	}

	Playing = false;
	Looping = false;
	PlayTime.Reset();
	StartTime = 0.0f;

	HRESULT _Result = DirectSoundBuffer->Stop();

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

void AuroraCore::Sound::Source::UpdatePlayTime()
{
	if (Playing)
	{
		if (Looping)
		{
			PlayTime.Stop();
		}
		else
		{
			PlayTime.Stop();

			if (StartTime + PlayTime >= GetTotalTime())
			{
				Playing = false;
				PlayTime.Reset();
				StartTime = 0.0f;
			}
		}
	}
}

const bool AuroraCore::Sound::Source::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

const bool AuroraCore::Sound::Source::IsPlaying() const
{
	return Playing;
}

const bool AuroraCore::Sound::Source::IsLooping() const
{
	return Looping;
}

const float AuroraCore::Sound::Source::GetTotalTime() const
{
	if (!CheckCreated() || (SoundInfo.nChannels != 1 && SoundInfo.nChannels != 2) || (SoundInfo.wBitsPerSample != 8 && SoundInfo.wBitsPerSample != 16) || SoundInfo.nAvgBytesPerSec == 0)
	{
		return 0.0f;
	}

	return (float)(Size) / (float)(SoundInfo.nAvgBytesPerSec);
}

const size_t AuroraCore::Sound::Source::GetSecondIndex(const float _Second) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0;
	}

	float _MappedSecond = _Second - _TotalTime * std::floor(_Second / _TotalTime);

	size_t _Result = (size_t)(_MappedSecond / _TotalTime * (float)(Size));

	if (SoundInfo.nChannels == 1)
	{
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 2;
		}
	}
	if (SoundInfo.nChannels == 2)
	{
		if (SoundInfo.wBitsPerSample == 8)
		{
			_Result -= _Result % 2;
		}
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 4;
		}
	}

	return _Result;
}

const float AuroraCore::Sound::Source::GetIndexSecond(const size_t _Index) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0.0f;
	}

	return _TotalTime * (float)(_Index % Size) / (float)(Size);
}

const float AuroraCore::Sound::Source::GetPlayTime() const
{
	return PlayTime;
}

const float AuroraCore::Sound::Source::GetStartTime() const
{
	return StartTime;
}

const size_t AuroraCore::Sound::Source::GetSize() const
{
	return Size;
}

const WAVEFORMATEX AuroraCore::Sound::Source::GetSoundInfo() const
{
	return SoundInfo;
}

AuroraCore::Sound::Source& AuroraCore::Sound::Source::operator= (Source&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound source until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;
	Playing = _Other.Playing;
	Looping = _Other.Looping;
	Size = _Other.Size;
	SoundInfo = _Other.SoundInfo;
	PlayTime = std::move(_Other.PlayTime);
	StartTime = _Other.StartTime;

	_Other.DirectSoundBuffer = nullptr;
	_Other.Playing = false;
	_Other.Looping = false;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
	_Other.StartTime = 0.0f;

	return *this;
}



AuroraCore::Sound::Source3D::Source3D() : DirectSoundBuffer(nullptr), DirectSound3DBuffer(nullptr), Playing(false), Looping(false), Size(0), SoundInfo({0}), PlayTime(), StartTime(0.0f)
{

}

AuroraCore::Sound::Source3D::Source3D(Source3D&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer), DirectSound3DBuffer(_Other.DirectSound3DBuffer), Playing(_Other.Playing), Looping(_Other.Looping), Size(_Other.Size), SoundInfo(_Other.SoundInfo), PlayTime(std::move(_Other.PlayTime)), StartTime(_Other.StartTime)
{
	_Other.DirectSoundBuffer = nullptr;
	_Other.DirectSound3DBuffer = nullptr;
	_Other.Playing = false;
	_Other.Looping = false;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
	_Other.StartTime = 0.0f;
}

AuroraCore::Sound::Source3D::~Source3D()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("The 3D sound source was not cleaned up!"));
}

bool AuroraCore::Sound::Source3D::Create(Context& _Context, Buffer3D& _Buffer)
{
	Destroy();

	if (!_Context.CheckCreated() || !_Buffer.CheckCreated())
	{
		return false;
	}

	IDirectSoundBuffer* _TempBuffer = nullptr;

	HRESULT _Result = _Context.DirectSoundContext->DuplicateSoundBuffer(_Buffer.DirectSoundBuffer, &_TempBuffer);

	if (_Result != S_OK)
	{
		return false;
	}

	_Result = _TempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)(&DirectSoundBuffer));

	if (_Result != S_OK)
	{
		AURORA_CORE_COM_RELEASE(_TempBuffer);
		return false;
	}

	AURORA_CORE_COM_RELEASE(_TempBuffer);

	_Result = DirectSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer8, (void**)(&DirectSound3DBuffer));

	if (_Result != S_OK)
	{
		Destroy();
		return false;
	}

	Size = _Buffer.GetSize();
	SoundInfo = _Buffer.GetSoundInfo();

	return true;
}

void AuroraCore::Sound::Source3D::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSound3DBuffer);
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
	Playing = false;
	Looping = false;
	Size = 0;
	SoundInfo = { 0 };
	PlayTime.Reset();
	StartTime = 0.0f;
}

bool AuroraCore::Sound::Source3D::SetVolume(const float _Volume)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->SetVolume(DSBVOLUME_MIN + (LONG)((float)(DSBVOLUME_MAX - DSBVOLUME_MIN) * _Volume));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetFrequency(const float _Frequency)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSoundBuffer->SetFrequency(DSBFREQUENCY_MIN + (DWORD)((float)(DSBFREQUENCY_MAX - DSBFREQUENCY_MIN) * _Frequency));

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetPosition(const Math::Vec3f& _Position, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetPosition(_Position.x, _Position.y, -_Position.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetVelocity(const Math::Vec3f& _Velocity, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetVelocity(_Velocity.x, _Velocity.y, -_Velocity.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetMinDistance(const float _Distance, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetMinDistance(_Distance, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetMaxDistance(const float _Distance, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetMaxDistance(_Distance, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetConeAngles(const uint32_t _Inside, const uint32_t _Outside, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetConeAngles(_Inside, _Outside, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetConeOrientation(const Math::Vec3f& _Orientation, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetConeOrientation(_Orientation.x, _Orientation.y, -_Orientation.z, _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetConeOutsideVolume(const float _Volume, const bool _Deferred)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = DirectSound3DBuffer->SetConeOutsideVolume(DSBVOLUME_MIN + (LONG)((float)(DSBVOLUME_MAX - DSBVOLUME_MIN) * _Volume), _Deferred ? DS3D_DEFERRED : DS3D_IMMEDIATE);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Source3D::SetCurrentPosition(const size_t _CurrentPosition)
{
	if (!CheckCreated())
	{
		return false;
	}

	bool _Playing = Playing;
	bool _Looping = Looping;

	if (Playing)
	{
		Stop();
	}

	StartTime = GetIndexSecond(_CurrentPosition);

	HRESULT _Result = DirectSoundBuffer->SetCurrentPosition((DWORD)(_CurrentPosition));

	if (_Result != S_OK)
	{
		return false;
	}

	if (_Playing)
	{
		if (!Play(_Looping))
		{
			return false;
		}
	}

	return true;
}

const bool AuroraCore::Sound::Source3D::GetVolume(float& _Volume) const
{
	if (!CheckCreated())
	{
		return false;
	}

	LONG _AuxVolume = 0;

	HRESULT _Result = DirectSoundBuffer->GetVolume(&_AuxVolume);

	if (_Result != S_OK)
	{
		return false;
	}

	_Volume = (float)(_AuxVolume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);

	return true;
}

const bool AuroraCore::Sound::Source3D::GetFrequency(float& _Frequency) const
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxFrequency = 0;

	HRESULT _Result = DirectSoundBuffer->GetFrequency(&_AuxFrequency);

	if (_Result != S_OK)
	{
		return false;
	}

	_Frequency = (float)(_AuxFrequency - DSBFREQUENCY_MIN) / (float)(DSBFREQUENCY_MAX - DSBFREQUENCY_MIN);

	return true;
}

const bool AuroraCore::Sound::Source3D::GetPosition(Math::Vec3f& _Position) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxPosition;

	HRESULT _Result = DirectSound3DBuffer->GetPosition(&_AuxPosition);

	if (_Result != S_OK)
	{
		return false;
	}

	_Position.x = _AuxPosition.x;
	_Position.y = _AuxPosition.y;
	_Position.z = -_AuxPosition.z;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetVelocity(Math::Vec3f& _Velocity) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxVelocity;

	HRESULT _Result = DirectSound3DBuffer->GetVelocity(&_AuxVelocity);

	if (_Result != S_OK)
	{
		return false;
	}

	_Velocity.x = _AuxVelocity.x;
	_Velocity.y = _AuxVelocity.y;
	_Velocity.z = -_AuxVelocity.z;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetMinDistance(float& _Distance) const
{
	if (!CheckCreated())
	{
		return false;
	}

	float _AuxDistance = 0.0f;

	HRESULT _Result = DirectSound3DBuffer->GetMinDistance(&_AuxDistance);

	if (_Result != S_OK)
	{
		return false;
	}

	_Distance = _AuxDistance;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetMaxDistance(float& _Distance) const
{
	if (!CheckCreated())
	{
		return false;
	}

	float _AuxDistance = 0.0f;

	HRESULT _Result = DirectSound3DBuffer->GetMaxDistance(&_AuxDistance);

	if (_Result != S_OK)
	{
		return false;
	}

	_Distance = _AuxDistance;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetConeAngles(uint32_t& _Inside, uint32_t& _Outside) const
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxInside = 0;
	DWORD _AuxOutside = 0;

	HRESULT _Result = DirectSound3DBuffer->GetConeAngles(&_AuxInside, &_AuxOutside);

	if (_Result != S_OK)
	{
		return false;
	}

	_Inside = _AuxInside;
	_Outside = _AuxOutside;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetConeOrientation(Math::Vec3f& _Orientation) const
{
	if (!CheckCreated())
	{
		return false;
	}

	D3DVECTOR _AuxOrientation;

	HRESULT _Result = DirectSound3DBuffer->GetConeOrientation(&_AuxOrientation);

	if (_Result != S_OK)
	{
		return false;
	}

	_Orientation.x = _AuxOrientation.x;
	_Orientation.y = _AuxOrientation.y;
	_Orientation.z = -_AuxOrientation.z;

	return true;
}

const bool AuroraCore::Sound::Source3D::GetConeOutsideVolume(float& _Volume) const
{
	if (!CheckCreated())
	{
		return false;
	}

	LONG _AuxVolume = 0;

	HRESULT _Result = DirectSound3DBuffer->GetConeOutsideVolume(&_AuxVolume);

	if (_Result != S_OK)
	{
		return false;
	}

	_Volume = (float)(_AuxVolume - DSBVOLUME_MIN) / (float)(DSBVOLUME_MAX - DSBVOLUME_MIN);

	return true;
}

const bool AuroraCore::Sound::Source3D::GetCurrentPosition(size_t& _CurrentPosition) const
{
	if (!CheckCreated())
	{
		return false;
	}

	DWORD _AuxCurrentPosition = 0;

	HRESULT _Result = DirectSoundBuffer->GetCurrentPosition(&_AuxCurrentPosition, nullptr);

	if (_Result != S_OK)
	{
		return false;
	}

	_CurrentPosition = _AuxCurrentPosition;

	return true;
}

bool AuroraCore::Sound::Source3D::Play(const bool _Looping)
{
	if (!CheckCreated())
	{
		return false;
	}

	if (Playing)
	{
		Stop();
	}

	HRESULT _Result = DirectSoundBuffer->Play(0, 0, _Looping ? DSBPLAY_LOOPING : NULL);

	if (_Result != S_OK)
	{
		return false;
	}

	Playing = true;
	Looping = _Looping;
	PlayTime.Reset();

	return true;
}

bool AuroraCore::Sound::Source3D::Stop()
{
	if (!CheckCreated())
	{
		return false;
	}

	Playing = false;
	Looping = false;
	PlayTime.Reset();
	StartTime = 0.0f;

	HRESULT _Result = DirectSoundBuffer->Stop();

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

void AuroraCore::Sound::Source3D::UpdatePlayTime()
{
	if (Playing)
	{
		if (Looping)
		{
			PlayTime.Stop();
		}
		else
		{
			PlayTime.Stop();

			if (StartTime + PlayTime >= GetTotalTime())
			{
				Playing = false;
				PlayTime.Reset();
				StartTime = 0.0f;
			}
		}
	}
}

const bool AuroraCore::Sound::Source3D::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

const bool AuroraCore::Sound::Source3D::IsPlaying() const
{
	return Playing;
}

const bool AuroraCore::Sound::Source3D::IsLooping() const
{
	return Looping;
}

const float AuroraCore::Sound::Source3D::GetTotalTime() const
{
	if (!CheckCreated() || (SoundInfo.nChannels != 1 && SoundInfo.nChannels != 2) || (SoundInfo.wBitsPerSample != 8 && SoundInfo.wBitsPerSample != 16) || SoundInfo.nAvgBytesPerSec == 0)
	{
		return 0.0f;
	}

	return (float)(Size) / (float)(SoundInfo.nAvgBytesPerSec);
}

const size_t AuroraCore::Sound::Source3D::GetSecondIndex(const float _Second) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0;
	}

	float _MappedSecond = _Second - _TotalTime * std::floor(_Second / _TotalTime);

	size_t _Result = (size_t)(_MappedSecond / _TotalTime * (float)(Size));

	if (SoundInfo.nChannels == 1)
	{
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 2;
		}
	}
	if (SoundInfo.nChannels == 2)
	{
		if (SoundInfo.wBitsPerSample == 8)
		{
			_Result -= _Result % 2;
		}
		if (SoundInfo.wBitsPerSample == 16)
		{
			_Result -= _Result % 4;
		}
	}

	return _Result;
}

const float AuroraCore::Sound::Source3D::GetIndexSecond(const size_t _Index) const
{
	float _TotalTime = GetTotalTime();

	if (_TotalTime == 0.0f)
	{
		return 0.0f;
	}

	return _TotalTime * (float)(_Index % Size) / (float)(Size);
}

const float AuroraCore::Sound::Source3D::GetPlayTime() const
{
	return PlayTime;
}

const float AuroraCore::Sound::Source3D::GetStartTime() const
{
	return StartTime;
}

const size_t AuroraCore::Sound::Source3D::GetSize() const
{
	return Size;
}

const WAVEFORMATEX AuroraCore::Sound::Source3D::GetSoundInfo() const
{
	return SoundInfo;
}

AuroraCore::Sound::Source3D& AuroraCore::Sound::Source3D::operator= (Source3D&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound 3D source until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;
	DirectSound3DBuffer = _Other.DirectSound3DBuffer;
	Playing = _Other.Playing;
	Looping = _Other.Looping;
	Size = _Other.Size;
	SoundInfo = _Other.SoundInfo;
	PlayTime = std::move(_Other.PlayTime);
	StartTime = _Other.StartTime;

	_Other.DirectSoundBuffer = nullptr;
	_Other.DirectSound3DBuffer = nullptr;
	_Other.Playing = false;
	_Other.Looping = false;
	_Other.Size = 0;
	_Other.SoundInfo = { 0 };
	_Other.StartTime = 0.0f;

	return *this;
}
