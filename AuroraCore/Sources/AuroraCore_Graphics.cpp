#include "..\Headers\AuroraCore.hpp"



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
	HBITMAP _HBitMap = (HBITMAP)(LoadImage(NULL, _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	BITMAP _BitMap = { 0 };

	GetObject(_HBitMap, sizeof(BITMAP), &_BitMap);

	Width = _BitMap.bmWidth;
	Height = _BitMap.bmHeight;
	ChannelsCount = 4;
	Data = new uint8_t[Width * Height * ChannelsCount];

	GetBitmapBits(_HBitMap, (LONG)(Width) * (LONG)(Height) * (LONG)(ChannelsCount), Data);

	for (size_t index = 0; index < Width * Height; index++)
	{
		std::swap(Data[(index * ChannelsCount) + 0], Data[(index * ChannelsCount) + 2]);
	}

	for (size_t y = 0; y < Height / 2; y++)
	{
		for (size_t x = 0; x < Width; x++)
		{
			std::swap(Data[(x + y * Width) * ChannelsCount + 0], Data[(x + (Height - y - 1) * Width) * ChannelsCount + 0]);
			std::swap(Data[(x + y * Width) * ChannelsCount + 1], Data[(x + (Height - y - 1) * Width) * ChannelsCount + 1]);
			std::swap(Data[(x + y * Width) * ChannelsCount + 2], Data[(x + (Height - y - 1) * Width) * ChannelsCount + 2]);
			std::swap(Data[(x + y * Width) * ChannelsCount + 3], Data[(x + (Height - y - 1) * Width) * ChannelsCount + 3]);
		}
	}

	DeleteObject(_HBitMap);

	return true;
}

const bool AuroraCore::Graphics::Assets::Image::Save(const wchar_t* _Path) const
{
	if (!Data || !Width || !Height || ChannelsCount != 4)
	{
		return false;
	}

	uint8_t* NewData;
	NewData = new uint8_t[Width * Height * ChannelsCount];

	if (!NewData)
	{
		return false;
	}

	for (size_t y = 0; y < Height; y++)
	{
		for (size_t x = 0; x < Width; x++)
		{
			NewData[(x + y * Width) * ChannelsCount + 0] = Data[(x + y * Width) * ChannelsCount + 2];
			NewData[(x + y * Width) * ChannelsCount + 1] = Data[(x + y * Width) * ChannelsCount + 1];
			NewData[(x + y * Width) * ChannelsCount + 2] = Data[(x + y * Width) * ChannelsCount + 0];
			NewData[(x + y * Width) * ChannelsCount + 3] = Data[(x + y * Width) * ChannelsCount + 3];
		}
	}

	FILE* File = nullptr;
	_wfopen_s(&File, _Path, L"wb");

	if (!File)
	{
		delete[] NewData;
		return false;
	}

	fwrite("BM", 1, 2, File);

	uint32_t size = (uint32_t)(Width) * (uint32_t)(Height) * (uint32_t)(ChannelsCount) + 54;
	fwrite(&size, 4, 1, File);

	fwrite("\0\0\0\0\x36\0\0\0\x28\0\0\0", 1, 12, File);

	uint32_t widthAux = (uint32_t)(Width);
	fwrite(&widthAux, 4, 1, File);

	uint32_t heightAux = (uint32_t)(Height);
	fwrite(&heightAux, 4, 1, File);
	fwrite("\x01\0\x20\0\0\0\0\0\0\0\0\0\x13\x0B\0\0\x13\x0B\0\0\0\0\0\0\0\0\0\0", 1, 28, File);

	fwrite(NewData, 1, Width * Height * ChannelsCount, File);

	fclose(File);

	return true;
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



HMODULE AuroraCore::Graphics::GL::DllHandle = NULL;



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

AuroraCore::Graphics::GL::Context::Context() : Handle(NULL), WndPtr(nullptr)
{

}

AuroraCore::Graphics::GL::Context::Context(Context&& _Other) noexcept : Handle(_Other.Handle), WndPtr(_Other.WndPtr)
{
	_Other.Handle = NULL;
	_Other.WndPtr = nullptr;
}

AuroraCore::Graphics::GL::Context::~Context()
{
	AURORA_CORE_ASSERT_MSG(Handle == NULL, L"An OpenGL context was not released!");
}

bool AuroraCore::Graphics::GL::Context::Create(Window& _WndPtr)
{
	if (Handle)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"The OpenGL context was not destroyed before trying to create another one!");

		return false;
	}

	HWND _hWnd = _WndPtr.GetHandle();

	if (!_hWnd)
	{
		return false;
	}

	HDC _hWndDC = GetDC(_hWnd);

	if (!_hWndDC)
	{
		return false;
	}

	int _PixelDescriptionVec[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int _PixelFormatID = 0;
	unsigned int _FormatCount = 0;

	if (!wglChoosePixelFormatARB(_hWndDC, _PixelDescriptionVec, nullptr, 1, &_PixelFormatID, &_FormatCount))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	PIXELFORMATDESCRIPTOR _PFD = { 0 };

	if (!DescribePixelFormat(_hWndDC, _PixelFormatID, sizeof(PIXELFORMATDESCRIPTOR), &_PFD))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	if (!SetPixelFormat(_hWndDC, _PixelFormatID, &_PFD))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	int _AttribList[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	Handle = wglCreateContextAttribsARB(_hWndDC, 0, _AttribList);

	if (!Handle)
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	WndPtr = &_WndPtr;

	ReleaseDC(_hWnd, _hWndDC);

	return true;
}

void AuroraCore::Graphics::GL::Context::Destroy()
{
	if (!Handle)
	{
		return;
	}

	wglDeleteContext(Handle);

	Handle = NULL;
	WndPtr = nullptr;
}

bool AuroraCore::Graphics::GL::Context::Bind()
{
	if (!Handle)
	{
		return false;
	}

	HWND _hWnd = WndPtr->GetHandle();

	if (!_hWnd)
	{
		return false;
	}

	HDC _hWndDC = GetDC(_hWnd);

	if (!_hWndDC)
	{
		return false;
	}

	if (!wglMakeCurrent(_hWndDC, Handle))
	{
		ReleaseDC(_hWnd, _hWndDC);
		return false;
	}

	ReleaseDC(_hWnd, _hWndDC);

	return true;
}

const HGLRC AuroraCore::Graphics::GL::Context::GetHandle() const
{
	return Handle;
}

AuroraCore::Window* AuroraCore::Graphics::GL::Context::GetWndPtr()
{
	return WndPtr;
}

const AuroraCore::Window* AuroraCore::Graphics::GL::Context::GetWndPtr() const
{
	return WndPtr;
}

AuroraCore::Graphics::GL::Context::operator const HGLRC() const
{
	return Handle;
}

void AuroraCore::Graphics::GL::Context::operator= (Context&& _Other) noexcept
{
	Handle = _Other.Handle;
	WndPtr = _Other.WndPtr;

	_Other.Handle = NULL;
	_Other.WndPtr = nullptr;
}

void AuroraCore::Graphics::GL::Context::Unbind()
{
	wglMakeCurrent(NULL, NULL);
}



AuroraCore::Graphics::GL::VertexBuffer::VertexBuffer() : ID(0)
{

}

AuroraCore::Graphics::GL::VertexBuffer::VertexBuffer(VertexBuffer&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

AuroraCore::Graphics::GL::VertexBuffer::~VertexBuffer()
{
	AURORA_CORE_ASSERT_MSG(ID == 0, L"A vertex buffer was not destroyed!");
}

bool AuroraCore::Graphics::GL::VertexBuffer::Create(const VertexBufferCPUCash& _VBO_CPUCash)
{
	if (ID)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create a vertex buffer without deleting the old one!");
		return false;
	}

	if (!_VBO_CPUCash.size())
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create a vertex buffer without data!");
		return false;
	}

	glGenBuffers(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, ID);

	glBufferData(GL_ARRAY_BUFFER, _VBO_CPUCash.size() * sizeof(VertexData), _VBO_CPUCash.data(), GL_DYNAMIC_DRAW);

	Unbind();

	return true;
}

void AuroraCore::Graphics::GL::VertexBuffer::Destroy()
{
	if (!ID)
	{
		return;
	}

	glDeleteBuffers(1, &ID);
	ID = 0;
}

bool AuroraCore::Graphics::GL::VertexBuffer::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, ID);

	return true;
}

const bool AuroraCore::Graphics::GL::VertexBuffer::CheckCreated() const
{
	return ID != 0;
}

const unsigned int AuroraCore::Graphics::GL::VertexBuffer::GetID() const
{
	return ID;
}

void AuroraCore::Graphics::GL::VertexBuffer::operator= (VertexBuffer&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void AuroraCore::Graphics::GL::VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



AuroraCore::Graphics::GL::IndexBuffer::IndexBuffer() : ID(0)
{

}

AuroraCore::Graphics::GL::IndexBuffer::IndexBuffer(IndexBuffer&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

AuroraCore::Graphics::GL::IndexBuffer::~IndexBuffer()
{
	AURORA_CORE_ASSERT_MSG(ID == 0, L"An index buffer was not destroyed!");
}

bool AuroraCore::Graphics::GL::IndexBuffer::Create(const IndexBufferCPUCash& _IBO_CPUCash)
{
	if (ID)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create an index buffer without deleting the old one!");
		return false;
	}

	if (!_IBO_CPUCash.size())
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create an index buffer without data!");
		return false;
	}

	glGenBuffers(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _IBO_CPUCash.size() * sizeof(unsigned int), _IBO_CPUCash.data(), GL_DYNAMIC_DRAW);

	Unbind();

	return true;
}

void AuroraCore::Graphics::GL::IndexBuffer::Destroy()
{
	if (!ID)
	{
		return;
	}

	glDeleteBuffers(1, &ID);
	ID = 0;
}

bool AuroraCore::Graphics::GL::IndexBuffer::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	return true;
}

const bool AuroraCore::Graphics::GL::IndexBuffer::CheckCreated() const
{
	return ID != 0;
}

const unsigned int AuroraCore::Graphics::GL::IndexBuffer::GetID() const
{
	return ID;
}

void AuroraCore::Graphics::GL::IndexBuffer::operator= (IndexBuffer&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void AuroraCore::Graphics::GL::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



AuroraCore::Graphics::GL::VertexAttribArray::VertexAttribArray() : ID(0)
{

}

AuroraCore::Graphics::GL::VertexAttribArray::VertexAttribArray(VertexAttribArray&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

AuroraCore::Graphics::GL::VertexAttribArray::~VertexAttribArray()
{
	AURORA_CORE_ASSERT_MSG(ID == 0, L"An attrib array was not destroyed!");
}

bool AuroraCore::Graphics::GL::VertexAttribArray::Create()
{
	if (ID)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create an attrib array object without deleting the old one!");
		return false;
	}

	glGenVertexArrays(1, &ID);

	if (!ID)
	{
		return false;
	}

	return true;
}

void AuroraCore::Graphics::GL::VertexAttribArray::Destroy()
{
	if (!ID)
	{
		return;
	}

	glDeleteVertexArrays(1, &ID);
	ID = 0;
}

bool AuroraCore::Graphics::GL::VertexAttribArray::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindVertexArray(ID);

	return true;
}

bool AuroraCore::Graphics::GL::VertexAttribArray::EnableAttrib(unsigned int _AttribID, int _ElementsCount, int _ElementsCountTotal, size_t _Offset)
{
	if (!ID)
	{
		return false;
	}

	glEnableVertexAttribArray(_AttribID);
	glVertexAttribPointer(_AttribID, _ElementsCount, GL_FLOAT, GL_FALSE, sizeof(float) * _ElementsCountTotal, (const void*)(_Offset * sizeof(float)));

	return true;
}

bool AuroraCore::Graphics::GL::VertexAttribArray::DisableAttrib(unsigned int _AttribID)
{
	if (!ID)
	{
		return false;
	}

	glDisableVertexAttribArray(_AttribID);

	return true;
}

const bool AuroraCore::Graphics::GL::VertexAttribArray::CheckCreated() const
{
	return ID != 0;
}

const unsigned int AuroraCore::Graphics::GL::VertexAttribArray::GetID() const
{
	return ID;
}

void AuroraCore::Graphics::GL::VertexAttribArray::operator= (VertexAttribArray&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void AuroraCore::Graphics::GL::VertexAttribArray::Unbind()
{
	glBindVertexArray(0);
}



AuroraCore::Graphics::GL::Shader::Shader() : ID(0)
{

}

AuroraCore::Graphics::GL::Shader::Shader(Shader&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

AuroraCore::Graphics::GL::Shader::~Shader()
{
	AURORA_CORE_ASSERT_MSG(ID == 0, L"A shader was not destroyed!");
}

bool AuroraCore::Graphics::GL::Shader::Create(const char* _VS, const char* _FS)
{
	if (ID)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create a shader without deleting the old one!");

		return false;
	}

	if (!_VS || !_FS)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create a shader without the code!");

		return false;
	}

	ID = glCreateProgram();

	if (!ID)
	{
		return false;
	}

	const char** _VPtr = &_VS;
	const char** _FPtr = &_FS;

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);

	if (!vs)
	{
		glDeleteProgram(ID);
		ID = 0;
		return false;
	}

	glShaderSource(vs, 1, _VPtr, nullptr);

	glCompileShader(vs);

	{
		int _Result;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetShaderInfoLog(vs, _Len + 1, &_Len, _Msg);
			AURORA_CORE_LOG_LINE("Vertex shader error:");
			AURORA_CORE_LOG_LINE(_Msg);
			delete[] _Msg;

			glDeleteShader(vs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	if (!fs)
	{
		glDeleteShader(vs);
		glDeleteProgram(ID);
		ID = 0;
		return false;
	}

	glShaderSource(fs, 1, _FPtr, nullptr);

	glCompileShader(fs);

	{
		int _Result;
		glGetShaderiv(fs, GL_COMPILE_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetShaderInfoLog(fs, _Len + 1, &_Len, _Msg);
			AURORA_CORE_LOG_LINE("Fragment shader error:");
			AURORA_CORE_LOG_LINE(_Msg);
			delete[] _Msg;

			glDeleteShader(vs);
			glDeleteShader(fs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	glAttachShader(ID, vs);
	glAttachShader(ID, fs);

	glLinkProgram(ID);

	{
		int _Result;
		glGetProgramiv(ID, GL_LINK_STATUS, &_Result);
		if (_Result == GL_FALSE)
		{
			int _Len = 0;
			glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &_Len);
			char* _Msg = new char[(size_t)(_Len)+1];
			glGetProgramInfoLog(ID, _Len + 1, &_Len, _Msg);
			AURORA_CORE_LOG_LINE("Link error:");
			AURORA_CORE_LOG_LINE(_Msg);
			delete[] _Msg;

			glDetachShader(ID, vs);
			glDeleteShader(vs);
			glDetachShader(ID, fs);
			glDeleteShader(fs);
			glDeleteProgram(ID);
			ID = 0;
			return false;
		}
	}

	glValidateProgram(ID);

	glDetachShader(ID, vs);
	glDeleteShader(vs);
	glDetachShader(ID, fs);
	glDeleteShader(fs);

	return true;
}

void AuroraCore::Graphics::GL::Shader::Destroy()
{
	if (!ID)
	{
		return;
	}

	glDeleteProgram(ID);
	ID = 0;
}

bool AuroraCore::Graphics::GL::Shader::Bind()
{
	if (!ID)
	{
		return false;
	}

	glUseProgram(ID);

	return true;
}

const bool AuroraCore::Graphics::GL::Shader::CheckCreated() const
{
	return ID != 0;
}

const unsigned int AuroraCore::Graphics::GL::Shader::GetID() const
{
	return ID;
}

void AuroraCore::Graphics::GL::Shader::operator= (Shader&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void AuroraCore::Graphics::GL::Shader::Unbind()
{
	glUseProgram(0);
}



AuroraCore::Graphics::GL::Uniform::Uniform() : ID(-1)
{

}

AuroraCore::Graphics::GL::Uniform::Uniform(Uniform&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = -1;
}

AuroraCore::Graphics::GL::Uniform::~Uniform()
{
	AURORA_CORE_ASSERT_MSG(ID == -1, L"An uniform was not released!");
}

bool AuroraCore::Graphics::GL::Uniform::GetLocation(const Shader& _Shader, const char* _Name)
{
	if (ID != -1)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"An uniform was not released before trying to bind another one!");

		return false;
	}

	if (!_Name)
	{
		return false;
	}

	ID = glGetUniformLocation(_Shader.GetID(), _Name);

	if (ID == -1)
	{
		return false;
	}

	return true;
}

void AuroraCore::Graphics::GL::Uniform::ReleaseLocation()
{
	ID = -1;
}

const bool AuroraCore::Graphics::GL::Uniform::CheckBind() const
{
	return ID != -1;
}

const int AuroraCore::Graphics::GL::Uniform::GetID() const
{
	return ID;
}

bool AuroraCore::Graphics::GL::Uniform::Set1f(float _x)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1f(ID, _x);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set2f(float _x, float _y)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform2f(ID, _x, _y);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set3f(float _x, float _y, float _z)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform3f(ID, _x, _y, _z);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set4f(float _x, float _y, float _z, float _w)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform4f(ID, _x, _y, _z, _w);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set1i(int _x)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1i(ID, _x);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set2i(int _x, int _y)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform2i(ID, _x, _y);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set3i(int _x, int _y, int _z)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform3i(ID, _x, _y, _z);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set4i(int _x, int _y, int _z, int _w)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform4i(ID, _x, _y, _z, _w);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set1b(bool _Value)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1i(ID, _Value);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::Set1ui(unsigned int _Value)
{
	if (ID == -1)
	{
		return false;
	}

	glUniform1ui(ID, _Value);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::SetMatrix2fv(float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix2fv(ID, 1, GL_TRUE, _Data);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::SetMatrix3fv(float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix3fv(ID, 1, GL_TRUE, _Data);

	return true;
}

bool AuroraCore::Graphics::GL::Uniform::SetMatrix4fv(float* _Data)
{
	if (ID == -1)
	{
		return false;
	}

	glUniformMatrix4fv(ID, 1, GL_TRUE, _Data);

	return true;
}

void AuroraCore::Graphics::GL::Uniform::operator= (Uniform&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = -1;
}



AuroraCore::Graphics::GL::Texture2D::Texture2D() : ID(0)
{

}

AuroraCore::Graphics::GL::Texture2D::Texture2D(Texture2D&& _Other) noexcept : ID(_Other.ID)
{
	_Other.ID = 0;
}

AuroraCore::Graphics::GL::Texture2D::~Texture2D()
{
	AURORA_CORE_ASSERT_MSG(ID == 0, L"A texture was not destroyed!");
}

bool AuroraCore::Graphics::GL::Texture2D::Create(const Assets::Image& _TexData)
{
	if (ID)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(L"Trying to create a texture before deleting old one!");
		return false;
	}

	if (!_TexData.GetWidth() || !_TexData.GetHeight() || !_TexData.GetData())
	{
		return false;
	}

	glGenTextures(1, &ID);

	if (!ID)
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)(_TexData.GetWidth()), (int)(_TexData.GetHeight()), 0, GL_RGBA, GL_UNSIGNED_BYTE, _TexData.GetData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return true;
}

void AuroraCore::Graphics::GL::Texture2D::Destroy()
{
	if (!ID)
	{
		return;
	}

	glDeleteTextures(1, &ID);
	ID = 0;
}

bool AuroraCore::Graphics::GL::Texture2D::Bind()
{
	if (!ID)
	{
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, ID);

	return true;
}

const bool AuroraCore::Graphics::GL::Texture2D::CheckCreated() const
{
	return ID != 0;
}

const unsigned int AuroraCore::Graphics::GL::Texture2D::GetID() const
{
	return ID;
}

void AuroraCore::Graphics::GL::Texture2D::operator= (Texture2D&& _Other) noexcept
{
	ID = _Other.ID;

	_Other.ID = 0;
}

void AuroraCore::Graphics::GL::Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



const std::string AuroraCore::Graphics::GL::GetUniformIndexName(const std::string _Name, const size_t _Index)
{
	return _Name + std::string("[") + std::to_string(_Index) + std::string("]");
}



bool AuroraCore::Graphics::GL::UniformSetCamera(const CameraStruct& _Camera, const Shader& _Shader, const char* _Name)
{
	if (!_Name || !_Shader.CheckCreated())
	{
		return false;
	}

	GL::Uniform u_CameraPosition;
	GL::Uniform u_CameraAngle;
	GL::Uniform u_CameraFov;
	GL::Uniform u_CameraZNear;
	GL::Uniform u_CameraZFar;

	u_CameraPosition.GetLocation(_Shader, (std::string(_Name) + std::string(".Position")).c_str());
	u_CameraAngle.GetLocation(_Shader, (std::string(_Name) + std::string(".Angle")).c_str());
	u_CameraFov.GetLocation(_Shader, (std::string(_Name) + std::string(".Fov")).c_str());
	u_CameraZNear.GetLocation(_Shader, (std::string(_Name) + std::string(".ZNear")).c_str());
	u_CameraZFar.GetLocation(_Shader, (std::string(_Name) + std::string(".ZFar")).c_str());

	u_CameraPosition.Set2f(_Camera.Position.x, _Camera.Position.y);
	u_CameraAngle.Set1f(_Camera.Angle);
	u_CameraFov.Set1f(_Camera.Fov);
	u_CameraZNear.Set1f(_Camera.ZNear);
	u_CameraZFar.Set1f(_Camera.ZFar);

	u_CameraPosition.ReleaseLocation();
	u_CameraAngle.ReleaseLocation();
	u_CameraFov.ReleaseLocation();
	u_CameraZNear.ReleaseLocation();
	u_CameraZFar.ReleaseLocation();

	return true;
}

bool AuroraCore::Graphics::GL::UniformSetMeshWorldData(const MeshWorldDataStruct& _MeshWorldData, const Shader& _Shader, const char* _Name)
{
	if (!_Name || !_Shader.CheckCreated())
	{
		return false;
	}

	GL::Uniform u_WorldDataPosition;
	GL::Uniform u_WorldDataAngle;
	GL::Uniform u_WorldDataScale;

	u_WorldDataPosition.GetLocation(_Shader, (std::string(_Name) + std::string(".Position")).c_str());
	u_WorldDataAngle.GetLocation(_Shader, (std::string(_Name) + std::string(".Angle")).c_str());
	u_WorldDataScale.GetLocation(_Shader, (std::string(_Name) + std::string(".Scale")).c_str());

	u_WorldDataPosition.Set3f(_MeshWorldData.Position.x, _MeshWorldData.Position.y, _MeshWorldData.Position.z);
	u_WorldDataAngle.Set1f(_MeshWorldData.Angle);
	u_WorldDataScale.Set2f(_MeshWorldData.Scale.x, _MeshWorldData.Scale.y);

	u_WorldDataPosition.ReleaseLocation();
	u_WorldDataAngle.ReleaseLocation();
	u_WorldDataScale.ReleaseLocation();

	return true;
}

bool AuroraCore::Graphics::GL::UniformSetMaterial(const MaterialStruct& _Material, const Shader& _Shader, const char* _Name)
{
	if (!_Name || !_Shader.CheckCreated())
	{
		return false;
	}

	GL::Uniform u_MaterialTextureAlbedo;
	GL::Uniform u_MaterialColor;
	GL::Uniform u_MaterialStart;
	GL::Uniform u_MaterialSize;

	u_MaterialTextureAlbedo.GetLocation(_Shader, (std::string(_Name) + std::string(".TextureAlbedo")).c_str());
	u_MaterialColor.GetLocation(_Shader, (std::string(_Name) + std::string(".Color")).c_str());
	u_MaterialStart.GetLocation(_Shader, (std::string(_Name) + std::string(".Start")).c_str());
	u_MaterialSize.GetLocation(_Shader, (std::string(_Name) + std::string(".Size")).c_str());

	u_MaterialTextureAlbedo.Set1i(_Material.TextureAlbedo);
	u_MaterialColor.Set4f(_Material.Color.x, _Material.Color.y, _Material.Color.z, _Material.Color.w);
	u_MaterialStart.Set2f(_Material.Start.x, _Material.Start.y);
	u_MaterialSize.Set2f(_Material.Size.x, _Material.Size.y);

	u_MaterialTextureAlbedo.ReleaseLocation();
	u_MaterialColor.ReleaseLocation();
	u_MaterialStart.ReleaseLocation();
	u_MaterialSize.ReleaseLocation();

	return true;
}



AuroraCore::Math::Mat4f AuroraCore::Graphics::GL::GetProjectionFromCamera(const CameraStruct& _CameraStr, const float _AspectRatio)
{
	return Math::Mat4f::GetOrtho(-_CameraStr.Fov / 2.0f * _AspectRatio, _CameraStr.Fov / 2.0f * _AspectRatio, -_CameraStr.Fov / 2.0f, _CameraStr.Fov / 2.0f, _CameraStr.ZFar, _CameraStr.ZNear);
}

AuroraCore::Math::Mat4f AuroraCore::Graphics::GL::GetViewFromCamera(const CameraStruct& _CameraStr)
{
	return Math::Mat4f::GetRotation(-_CameraStr.Angle, Math::Vec3f(0.0f, 0.0f, 1.0f)) * Math::Mat4f::GetTranslation(-Math::Vec3f(_CameraStr.Position, 0.0f));
}

AuroraCore::Math::Mat4f AuroraCore::Graphics::GL::GetModelFromWorldData(const MeshWorldDataStruct& _WorldData)
{
	return Math::Mat4f::GetTranslation(_WorldData.Position) * Math::Mat4f::GetRotation(_WorldData.Angle, Math::Vec3f(0.0f, 0.0f, 1.0f)) * Math::Mat4f::GetScale(_WorldData.Scale.x, _WorldData.Scale.y, 0.0f, 1.0f);
}
