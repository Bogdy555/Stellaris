#include "..\Headers\AuroraCore.hpp"



AuroraCore::Sound::Buffer::Buffer() : MetaData({ 0 }), Size(0), Data(nullptr)
{

}

AuroraCore::Sound::Buffer::Buffer(Buffer&& _Other) noexcept : MetaData(_Other.MetaData), Size(_Other.Size), Data(_Other.Data)
{
	_Other.MetaData = { 0 };
	_Other.Size = 0;
	_Other.Data = nullptr;
}

AuroraCore::Sound::Buffer::~Buffer()
{
	Destroy();
}

bool AuroraCore::Sound::Buffer::Create(const WAVEFORMATEX& _MetaData, const size_t _Size)
{
	Destroy();

	Data = new uint8_t[_Size];

	if (!Data)
	{
		return false;
	}

	MetaData = _MetaData;
	Size = _Size;

	return true;
}

void AuroraCore::Sound::Buffer::Destroy()
{
	delete[] Data;
	Data = nullptr;
	MetaData = { 0 };
	Size = 0;
}

bool AuroraCore::Sound::Buffer::LoadFromFile(const wchar_t* _Path)
{
	return false;
}

bool AuroraCore::Sound::Buffer::LoadFromResource(const HINSTANCE _InstanceHandle, const uint16_t _ResourceId)
{
	return false;
}

const bool AuroraCore::Sound::Buffer::SaveToFile(const wchar_t* _Path) const
{
	if (!_Path)
	{
		return false;
	}

	if (!Data || !Size)
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

	if (fwrite(&MetaData.wFormatTag, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&MetaData.nChannels, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&MetaData.nSamplesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&MetaData.nAvgBytesPerSec, 4, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&MetaData.nBlockAlign, 2, 1, _File) != 1)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

	if (fwrite(&MetaData.wBitsPerSample, 2, 1, _File) != 1)
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
		uint32_t _Size = Size;

		if (fwrite(&_Size, 4, 1, _File) != 1)
		{
			fclose(_File);
			_wremove(_Path);
			return false;
		}
	}

	if (fwrite(Data, 1, Size, _File) != Size)
	{
		fclose(_File);
		_wremove(_Path);
		return false;
	}

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

const WAVEFORMATEX AuroraCore::Sound::Buffer::GetMetaData() const
{
	return MetaData;
}

const size_t AuroraCore::Sound::Buffer::GetSize() const
{
	return Size;
}

uint8_t* AuroraCore::Sound::Buffer::GetData()
{
	return Data;
}

const uint8_t* AuroraCore::Sound::Buffer::GetData() const
{
	return Data;
}

uint8_t& AuroraCore::Sound::Buffer::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& AuroraCore::Sound::Buffer::operator[] (const size_t _Index) const
{
	return Data[_Index];
}

AuroraCore::Sound::Buffer& AuroraCore::Sound::Buffer::operator= (Buffer&& _Other) noexcept
{
	MetaData = _Other.MetaData;
	Size = _Other.Size;
	Data = _Other.Data;

	_Other.MetaData = { 0 };
	_Other.Size = 0;
	_Other.Data = nullptr;

	return *this;
}
