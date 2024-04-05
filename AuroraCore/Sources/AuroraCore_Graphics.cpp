#include "..\Headers\AuroraCore.hpp"

#include <Windows.h>


HMODULE AuroraCore::Graphics::GL::DllHandle = NULL;


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


void* (__stdcall* AuroraCore::Graphics::GL::wglGetProcAddress)(const char*) = nullptr;
int(__stdcall* AuroraCore::Graphics::GL::wglChoosePixelFormatARB)(HDC, const int*, const float*, unsigned int, int*, unsigned int*) = nullptr;
HGLRC(__stdcall* AuroraCore::Graphics::GL::wglCreateContextAttribsARB)(HDC, HGLRC, const int*) = nullptr;
int(__stdcall* AuroraCore::Graphics::GL::wglSwapIntervalEXT)(int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glViewport)(int, int, int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glClearColor)(float, float, float, float) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glClear)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUseProgram)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glBindVertexArray)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDrawElements)(unsigned int, int, unsigned int, const void*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glEnable)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDisable)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glBlendFunc)(unsigned int, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDepthFunc)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGenBuffers)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glBindBuffer)(unsigned int, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glBufferData)(unsigned int, intptr_t, const void*, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGenVertexArrays)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glEnableVertexAttribArray)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glVertexAttribPointer)(unsigned int, int, unsigned int, unsigned char, int, const void*) = nullptr;
unsigned int(__stdcall* AuroraCore::Graphics::GL::glCreateProgram)() = nullptr;
unsigned int(__stdcall* AuroraCore::Graphics::GL::glCreateShader)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glShaderSource)(unsigned int, int, const char* const*, int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glCompileShader)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glAttachShader)(unsigned int, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glLinkProgram)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glValidateProgram)(unsigned int) = nullptr;
int(__stdcall* AuroraCore::Graphics::GL::glGetUniformLocation)(unsigned int, const char*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform1f)(int, float) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform2f)(int, float, float) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform3f)(int, float, float, float) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform4f)(int, float, float, float, float) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform1i)(int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform2i)(int, int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform3i)(int, int, int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform4i)(int, int, int, int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniform1ui)(int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniformMatrix2fv)(int, int, unsigned char, const float*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniformMatrix3fv)(int, int, unsigned char, const float*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glUniformMatrix4fv)(int, int, unsigned char, const float*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDetachShader)(unsigned int, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDeleteBuffers)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDeleteVertexArrays)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDisableVertexAttribArray)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDeleteProgram)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDeleteShader)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGetShaderiv)(unsigned int, unsigned int, int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGetShaderInfoLog)(unsigned int, int, int*, char*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGetProgramiv)(unsigned int, unsigned int, int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGetProgramInfoLog)(unsigned int, int, int*, char*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGenTextures)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glBindTexture)(unsigned int, unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glTexParameteri)(unsigned int, unsigned int, int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glTexImage2D)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glActiveTexture)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glDeleteTextures)(int, unsigned int*) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glCullFace)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glFrontFace)(unsigned int) = nullptr;
void(__stdcall* AuroraCore::Graphics::GL::glGenerateMipmap)(unsigned int) = nullptr;



static void* CustomGetProcAddress(const char* _Name)
{
	if (!_Name)
	{
		return nullptr;
	}

	void* _Rez = nullptr;

	if (AuroraCore::Graphics::GL::wglGetProcAddress)
	{
		_Rez = AuroraCore::Graphics::GL::wglGetProcAddress(_Name);
	}

	if (!_Rez)
	{
		_Rez = GetProcAddress(AuroraCore::Graphics::GL::DllHandle, _Name);
	}

	return _Rez;
}

#define LOAD(Func, Type, Name) Func = (Type)(CustomGetProcAddress(Name));\
if (!Func)\
{\
	wglMakeCurrent(NULL, NULL);\
	wglDeleteContext(wglContext);\
	ReleaseDC(_hWnd, _WndDC);\
	DestroyWindow(_hWnd);\
	UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);\
	Unload();\
	return false;\
}

bool AuroraCore::Graphics::GL::Load()
{
	if (DllHandle)
	{
		return true;
	}

	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	_WndClass.lpfnWndProc = DefWindowProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetModuleHandle(nullptr);
	_WndClass.hIcon = NULL;
	_WndClass.hCursor = NULL;
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = L"DummyWndClass";
	_WndClass.hIconSm = NULL;

	if (!RegisterClassEx(&_WndClass))
	{
		return false;
	}

	HWND _hWnd = CreateWindowEx(NULL, _WndClass.lpszClassName, L"DummyWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, _WndClass.hInstance, nullptr);

	if (!_hWnd)
	{
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	HDC _WndDC = GetDC(_hWnd);

	if (!_WndDC)
	{
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	PIXELFORMATDESCRIPTOR _PFD = { 0 };

	_PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	_PFD.nVersion = 1;
	_PFD.iPixelType = PFD_TYPE_RGBA;
	_PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	_PFD.cColorBits = 32;
	_PFD.cAlphaBits = 8;
	_PFD.cDepthBits = 24;
	_PFD.cStencilBits = 8;
	_PFD.iLayerType = PFD_MAIN_PLANE;

	int _PForm = ChoosePixelFormat(_WndDC, &_PFD);

	if (!_PForm)
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	if (!SetPixelFormat(_WndDC, _PForm, &_PFD))
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	HGLRC wglContext = wglCreateContext(_WndDC);

	if (!wglContext)
	{
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	if (!wglMakeCurrent(_WndDC, wglContext))
	{
		wglDeleteContext(wglContext);
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	DllHandle = LoadLibrary(L"opengl32.dll");

	if (!DllHandle)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(wglContext);
		ReleaseDC(_hWnd, _WndDC);
		DestroyWindow(_hWnd);
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	LOAD(wglGetProcAddress, void* (__stdcall*)(const char*), "wglGetProcAddress");
	LOAD(wglChoosePixelFormatARB, int(__stdcall*)(HDC, const int*, const float*, unsigned int, int*, unsigned int*), "wglChoosePixelFormatARB");
	LOAD(wglCreateContextAttribsARB, HGLRC(__stdcall*)(HDC, HGLRC, const int*), "wglCreateContextAttribsARB");
	LOAD(wglSwapIntervalEXT, int(__stdcall*)(int), "wglSwapIntervalEXT");
	LOAD(glViewport, void(__stdcall*)(int, int, int, int), "glViewport");
	LOAD(glClearColor, void(__stdcall*)(float, float, float, float), "glClearColor");
	LOAD(glClear, void(__stdcall*)(unsigned int), "glClear");
	LOAD(glUseProgram, void(__stdcall*)(unsigned int), "glUseProgram");
	LOAD(glBindVertexArray, void(__stdcall*)(unsigned int), "glBindVertexArray");
	LOAD(glDrawElements, void(__stdcall*)(unsigned int, int, unsigned int, const void*), "glDrawElements");
	LOAD(glEnable, void(__stdcall*)(unsigned int), "glEnable");
	LOAD(glDisable, void(__stdcall*)(unsigned int), "glDisable");
	LOAD(glBlendFunc, void(__stdcall*)(unsigned int, unsigned int), "glBlendFunc");
	LOAD(glDepthFunc, void(__stdcall*)(unsigned int), "glDepthFunc");
	LOAD(glGenBuffers, void(__stdcall*)(int, unsigned int*), "glGenBuffers");
	LOAD(glBindBuffer, void(__stdcall*)(unsigned int, unsigned int), "glBindBuffer");
	LOAD(glBufferData, void(__stdcall*)(unsigned int, intptr_t, const void*, unsigned int), "glBufferData");
	LOAD(glGenVertexArrays, void(__stdcall*)(int, unsigned int*), "glGenVertexArrays");
	LOAD(glEnableVertexAttribArray, void(__stdcall*)(unsigned int), "glEnableVertexAttribArray");
	LOAD(glVertexAttribPointer, void(__stdcall*)(unsigned int, int, unsigned int, unsigned char, int, const void*), "glVertexAttribPointer");
	LOAD(glCreateProgram, unsigned int(__stdcall*)(), "glCreateProgram");
	LOAD(glCreateShader, unsigned int(__stdcall*)(unsigned int), "glCreateShader");
	LOAD(glShaderSource, void(__stdcall*)(unsigned int, int, const char* const*, int*), "glShaderSource");
	LOAD(glCompileShader, void(__stdcall*)(unsigned int), "glCompileShader");
	LOAD(glAttachShader, void(__stdcall*)(unsigned int, unsigned int), "glAttachShader");
	LOAD(glLinkProgram, void(__stdcall*)(unsigned int), "glLinkProgram");
	LOAD(glValidateProgram, void(__stdcall*)(unsigned int), "glValidateProgram");
	LOAD(glGetUniformLocation, int(__stdcall*)(unsigned int, const char*), "glGetUniformLocation");
	LOAD(glUniform1f, void(__stdcall*)(int, float), "glUniform1f");
	LOAD(glUniform2f, void(__stdcall*)(int, float, float), "glUniform2f");
	LOAD(glUniform3f, void(__stdcall*)(int, float, float, float), "glUniform3f");
	LOAD(glUniform4f, void(__stdcall*)(int, float, float, float, float), "glUniform4f");
	LOAD(glUniform1i, void(__stdcall*)(int, int), "glUniform1i");
	LOAD(glUniform2i, void(__stdcall*)(int, int, int), "glUniform2i");
	LOAD(glUniform3i, void(__stdcall*)(int, int, int, int), "glUniform3i");
	LOAD(glUniform4i, void(__stdcall*)(int, int, int, int, int), "glUniform4i");
	LOAD(glUniform1ui, void(__stdcall*)(int, int), "glUniform1ui");
	LOAD(glUniformMatrix2fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix2fv");
	LOAD(glUniformMatrix3fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix3fv");
	LOAD(glUniformMatrix4fv, void(__stdcall*)(int, int, unsigned char, const float*), "glUniformMatrix4fv");
	LOAD(glDetachShader, void(__stdcall*)(unsigned int, unsigned int), "glDetachShader");
	LOAD(glDeleteBuffers, void(__stdcall*)(int, unsigned int*), "glDeleteBuffers");
	LOAD(glDeleteVertexArrays, void(__stdcall*)(int, unsigned int*), "glDeleteVertexArrays");
	LOAD(glDisableVertexAttribArray, void(__stdcall*)(unsigned int), "glDisableVertexAttribArray");
	LOAD(glDeleteProgram, void(__stdcall*)(unsigned int), "glDeleteProgram");
	LOAD(glDeleteShader, void(__stdcall*)(unsigned int), "glDeleteShader");
	LOAD(glGetShaderiv, void(__stdcall*)(unsigned int, unsigned int, int*), "glGetShaderiv");
	LOAD(glGetShaderInfoLog, void(__stdcall*)(unsigned int, int, int*, char*), "glGetShaderInfoLog");
	LOAD(glGetProgramiv, void(__stdcall*)(unsigned int, unsigned int, int*), "glGetProgramiv");
	LOAD(glGetProgramInfoLog, void(__stdcall*)(unsigned int, int, int*, char*), "glGetProgramInfoLog");
	LOAD(glGenTextures, void(__stdcall*)(int, unsigned int*), "glGenTextures");
	LOAD(glBindTexture, void(__stdcall*)(unsigned int, unsigned int), "glBindTexture");
	LOAD(glTexParameteri, void(__stdcall*)(unsigned int, unsigned int, int), "glTexParameteri");
	LOAD(glTexImage2D, void(__stdcall*)(unsigned int, int, int, int, int, int, unsigned int, unsigned int, const void*), "glTexImage2D");
	LOAD(glActiveTexture, void(__stdcall*)(unsigned int), "glActiveTexture");
	LOAD(glDeleteTextures, void(__stdcall*)(int, unsigned int*), "glDeleteTextures");
	LOAD(glCullFace, void(__stdcall*)(unsigned int), "glCullFace");
	LOAD(glFrontFace, void(__stdcall*)(unsigned int), "glFrontFace");
	LOAD(glGenerateMipmap, void(__stdcall*)(unsigned int), "glGenerateMipmap");

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(wglContext);
	ReleaseDC(_hWnd, _WndDC);
	DestroyWindow(_hWnd);
	UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);


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

#define UNLOAD(Func) Func = nullptr

void AuroraCore::Graphics::GL::Unload()
{
	if (!DllHandle)
	{
		return;
	}

	FreeLibrary(DllHandle);
	DllHandle = NULL;

	UNLOAD(wglGetProcAddress);
	UNLOAD(wglChoosePixelFormatARB);
	UNLOAD(wglCreateContextAttribsARB);
	UNLOAD(wglSwapIntervalEXT);
	UNLOAD(glViewport);
	UNLOAD(glClearColor);
	UNLOAD(glClear);
	UNLOAD(glUseProgram);
	UNLOAD(glBindVertexArray);
	UNLOAD(glDrawElements);
	UNLOAD(glEnable);
	UNLOAD(glDisable);
	UNLOAD(glBlendFunc);
	UNLOAD(glDepthFunc);
	UNLOAD(glGenBuffers);
	UNLOAD(glBindBuffer);
	UNLOAD(glBufferData);
	UNLOAD(glGenVertexArrays);
	UNLOAD(glEnableVertexAttribArray);
	UNLOAD(glVertexAttribPointer);
	UNLOAD(glCreateProgram);
	UNLOAD(glCreateShader);
	UNLOAD(glShaderSource);
	UNLOAD(glCompileShader);
	UNLOAD(glAttachShader);
	UNLOAD(glLinkProgram);
	UNLOAD(glValidateProgram);
	UNLOAD(glGetUniformLocation);
	UNLOAD(glUniform1f);
	UNLOAD(glUniform2f);
	UNLOAD(glUniform3f);
	UNLOAD(glUniform4f);
	UNLOAD(glUniform1i);
	UNLOAD(glUniform2i);
	UNLOAD(glUniform3i);
	UNLOAD(glUniform4i);
	UNLOAD(glUniform1ui);
	UNLOAD(glUniformMatrix2fv);
	UNLOAD(glUniformMatrix3fv);
	UNLOAD(glUniformMatrix4fv);
	UNLOAD(glDetachShader);
	UNLOAD(glDeleteBuffers);
	UNLOAD(glDeleteVertexArrays);
	UNLOAD(glDisableVertexAttribArray);
	UNLOAD(glDeleteProgram);
	UNLOAD(glDeleteShader);
	UNLOAD(glGetShaderiv);
	UNLOAD(glGetShaderInfoLog);
	UNLOAD(glGetProgramiv);
	UNLOAD(glGetProgramInfoLog);
	UNLOAD(glGenTextures);
	UNLOAD(glBindTexture);
	UNLOAD(glTexParameteri);
	UNLOAD(glTexImage2D);
	UNLOAD(glActiveTexture);
	UNLOAD(glDeleteTextures);
	UNLOAD(glCullFace);
	UNLOAD(glFrontFace);
	UNLOAD(glGenerateMipmap);

}
