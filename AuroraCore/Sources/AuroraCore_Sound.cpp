#include "..\Headers\AuroraCore.hpp"



static std::vector<AuroraCore::Sound::Device> _Devices;



const std::vector<AuroraCore::Sound::Device>& AuroraCore::Sound::Devices = _Devices;



static BOOL CALLBACK GetDevices(LPGUID _Id, LPCWSTR _Name, LPCWSTR _Driver, LPVOID _Context)
{
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

bool AuroraCore::Sound::Context::SetPosition(const Math::Vec3f& _Position)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetPosition(_Position.x, _Position.y, _Position.z, DS3D_DEFERRED);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Context::SetOrientation(const Math::Vec3f& _Front, const Math::Vec3f& _Up)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetOrientation(_Front.x, _Front.y, _Front.z, _Up.x, _Up.y, _Up.z, DS3D_DEFERRED);

	if (_Result != S_OK)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Sound::Context::SetVelocity(const Math::Vec3f& _Velocity)
{
	if (!CheckCreated())
	{
		return false;
	}

	HRESULT _Result = Listener->SetVelocity(_Velocity.x, _Velocity.y, _Velocity.z, DS3D_DEFERRED);

	if (_Result != S_OK)
	{
		return false;
	}

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



AuroraCore::Sound::Buffer::Buffer() : DirectSoundBuffer(nullptr)
{

}

AuroraCore::Sound::Buffer::Buffer(Buffer&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer)
{
	_Other.DirectSoundBuffer = nullptr;
}

AuroraCore::Sound::Buffer::~Buffer()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Sound buffer was not cleaned up!"));
}

bool AuroraCore::Sound::Buffer::Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _AudioInfo, const uint8_t* _Data)
{
	Destroy();

	if (!_Context.CheckCreated() || _Size == 0)
	{
		return false;
	}

	WAVEFORMATEX _BufferAudioInfo = _AudioInfo;

	DSBUFFERDESC _BufferDesc = { 0 };

	_BufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_BufferDesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	_BufferDesc.dwBufferBytes = (DWORD)(_Size);
	_BufferDesc.dwReserved = 0;
	_BufferDesc.lpwfxFormat = &_BufferAudioInfo;
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

	return true;
}

void AuroraCore::Sound::Buffer::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
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

AuroraCore::Sound::Buffer& AuroraCore::Sound::Buffer::operator= (Buffer&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound buffer until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;

	_Other.DirectSoundBuffer = nullptr;

	return *this;
}



AuroraCore::Sound::Buffer3D::Buffer3D() : DirectSoundBuffer(nullptr)
{

}

AuroraCore::Sound::Buffer3D::Buffer3D(Buffer3D&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer)
{
	_Other.DirectSoundBuffer = nullptr;
}

AuroraCore::Sound::Buffer3D::~Buffer3D()
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("3D sound buffer was not cleaned up!"));
}

bool AuroraCore::Sound::Buffer3D::Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _AudioInfo, const uint8_t* _Data)
{
	Destroy();

	if (!_Context.CheckCreated() || _Size == 0 || _AudioInfo.nChannels != 1)
	{
		return false;
	}

	WAVEFORMATEX _BufferAudioInfo = _AudioInfo;

	DSBUFFERDESC _BufferDesc = { 0 };

	_BufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_BufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	_BufferDesc.dwBufferBytes = (DWORD)(_Size);
	_BufferDesc.dwReserved = 0;
	_BufferDesc.lpwfxFormat = &_BufferAudioInfo;
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

	return true;
}

void AuroraCore::Sound::Buffer3D::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
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

AuroraCore::Sound::Buffer3D& AuroraCore::Sound::Buffer3D::operator= (Buffer3D&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another 3D sound buffer until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;

	_Other.DirectSoundBuffer = nullptr;

	return *this;
}



AuroraCore::Sound::Source::Source() : DirectSoundBuffer(nullptr)
{

}

AuroraCore::Sound::Source::Source(Source&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer)
{
	_Other.DirectSoundBuffer = nullptr;
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

	return true;
}

void AuroraCore::Sound::Source::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
}

const bool AuroraCore::Sound::Source::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

AuroraCore::Sound::Source& AuroraCore::Sound::Source::operator= (Source&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound source until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;

	_Other.DirectSoundBuffer = nullptr;

	return *this;
}



AuroraCore::Sound::Source3D::Source3D() : DirectSoundBuffer(nullptr), DirectSound3DBuffer(nullptr)
{

}

AuroraCore::Sound::Source3D::Source3D(Source3D&& _Other) noexcept : DirectSoundBuffer(_Other.DirectSoundBuffer), DirectSound3DBuffer(_Other.DirectSound3DBuffer)
{
	_Other.DirectSoundBuffer = nullptr;
	_Other.DirectSound3DBuffer = nullptr;
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

	return true;
}

void AuroraCore::Sound::Source3D::Destroy()
{
	AURORA_CORE_COM_RELEASE(DirectSound3DBuffer);
	AURORA_CORE_COM_RELEASE(DirectSoundBuffer);
}

const bool AuroraCore::Sound::Source3D::CheckCreated() const
{
	return DirectSoundBuffer != nullptr;
}

AuroraCore::Sound::Source3D& AuroraCore::Sound::Source3D::operator= (Source3D&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(!CheckCreated(), AURORA_CORE_STRING_PREFIX("Can not take ownership of another sound 3D source until this one is free!"));

	DirectSoundBuffer = _Other.DirectSoundBuffer;
	DirectSound3DBuffer = _Other.DirectSound3DBuffer;

	_Other.DirectSoundBuffer = nullptr;
	_Other.DirectSound3DBuffer = nullptr;

	return *this;
}
