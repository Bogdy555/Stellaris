#include "..\Headers\AuroraCore.hpp"

#include <Windows.h>



AuroraCore::Graphics::Assets::Image::Image() : Width(0), Height(0), ChannelsCount(0), Data(nullptr)
{

}

AuroraCore::Graphics::Assets::Image::Image(Image&& _Other) noexcept : Width(_Other.Width), Height(_Other.Height), ChannelsCount(_Other.ChannelsCount), Data(_Other.Data)
{
	_Other.Width = 0;
	_Other.Height = 0;
	_Other.ChannelsCount = 0;
	_Other.Data = nullptr;
}

AuroraCore::Graphics::Assets::Image::~Image()
{
	Destroy();
}

AuroraCore::Graphics::Assets::Image& AuroraCore::Graphics::Assets::Image::operator= (Image&& _Other) noexcept
{
	Width = _Other.Width;
	Height = _Other.Height;
	ChannelsCount = _Other.ChannelsCount;
	Data = _Other.Data;

	_Other.Width = 0;
	_Other.Height = 0;
	_Other.ChannelsCount = 0;
	_Other.Data = nullptr;

	return *this;
}

bool AuroraCore::Graphics::Assets::Image::Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount)
{
	Destroy();

	Data = new uint8_t[_Width * _Height * _ChannelsCount];
	if (!Data)
	{
		return false;
	}
	Width = _Width;
	Height = _Height;
	ChannelsCount = _ChannelsCount;

	return true;
}

bool AuroraCore::Graphics::Assets::Image::Load(const wchar_t* _Path)
{
	Destroy();
	HBITMAP _HBitMap = (HBITMAP)(LoadImage(NULL, _Path, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));

	BITMAP _BitMap = { 0 };

	GetObject(_HBitMap, sizeof(BITMAP), &_BitMap);

	DeleteObject(_HBitMap);

	return false;
}

const bool AuroraCore::Graphics::Assets::Image::Save(const wchar_t* _Path) const
{
	return false;
}

void AuroraCore::Graphics::Assets::Image::Destroy()
{
	delete[] Data;
	Data = nullptr;
	Width = 0;
	Height = 0;
	ChannelsCount = 0;
}

const size_t AuroraCore::Graphics::Assets::Image::GetWidth() const
{
	return Width;
}

const size_t AuroraCore::Graphics::Assets::Image::GetHeight() const
{
	return Height;
}

const size_t AuroraCore::Graphics::Assets::Image::GetChannelsCount() const
{
	return ChannelsCount;
}

uint8_t* AuroraCore::Graphics::Assets::Image::GetData()
{
	return Data;
}

const uint8_t* AuroraCore::Graphics::Assets::Image::GetData() const
{
	return Data;
}

uint8_t& AuroraCore::Graphics::Assets::Image::operator[] (const size_t _Index)
{
	return Data[_Index];
}

const uint8_t& AuroraCore::Graphics::Assets::Image::operator[] (const size_t _Index) const
{
	return Data[_Index];
}
