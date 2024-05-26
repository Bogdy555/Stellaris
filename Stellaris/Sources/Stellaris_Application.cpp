#include "..\Headers\Stellaris.hpp"



Stellaris::RunTime::Application::Application() : AuroraCore::RunTime::Application(), MainWindow(), MainWindowData(), PlacementMutex(), RectMutex(), FullScreenMutex(), CloseMutex(), InputMutex(), MinSizeMutex(), ContextMutex(), Context(), Assets(), SoundContext(), CurrentDeviceDriver(L""), BackgroundSound(), CollectSound(), SoundSources(), Score(0), Volume(true)
{
	
}

Stellaris::RunTime::Application::~Application()
{

}

AuroraCore::Window& Stellaris::RunTime::Application::GetMainWindow()
{
	return MainWindow;
}

const AuroraCore::Window& Stellaris::RunTime::Application::GetMainWindow() const
{
	return MainWindow;
}

Stellaris::Window::Data& Stellaris::RunTime::Application::GetMainWindowData()
{
	return MainWindowData;
}

const Stellaris::Window::Data& Stellaris::RunTime::Application::GetMainWindowData() const
{
	return MainWindowData;
}

void Stellaris::RunTime::Application::UpdateFullScreen()
{
	MainWindowData.FullScreenMutex->lock();

	MainWindowData.FullScreen = !MainWindowData.FullScreen;

	if (MainWindowData.FullScreen)
	{
		MainWindowData.FullScreenMutex->unlock();

		MainWindowData.PlacementMutex->lock();

		GetWindowPlacement(MainWindow, &MainWindowData.Placement);

		MainWindowData.PlacementMutex->unlock();

		MainWindowData.RectMutex->lock();

		GetWindowRect(MainWindow, &MainWindowData.Rect);

		MainWindowData.RectMutex->unlock();

		HMONITOR _hMonitor = MonitorFromWindow(MainWindow, MONITOR_DEFAULTTOPRIMARY);

		MONITORINFOEX _MonitorInfo = { 0 };

		_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

		GetMonitorInfo(_hMonitor, &_MonitorInfo);

		SetWindowLongPtr(MainWindow, GWL_STYLE, WS_POPUP);

		SetWindowPos(MainWindow, HWND_TOP, _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.top, _MonitorInfo.rcMonitor.right - _MonitorInfo.rcMonitor.left, _MonitorInfo.rcMonitor.bottom - _MonitorInfo.rcMonitor.top, SWP_ASYNCWINDOWPOS);

		MainWindow.Show(SW_SHOW);
	}
	else
	{
		MainWindowData.FullScreenMutex->unlock();

		SetWindowLongPtr(MainWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		MainWindowData.PlacementMutex->lock();

		if (MainWindowData.Placement.showCmd != SW_NORMAL)
		{
			SetWindowPos(MainWindow, HWND_TOP, MainWindowData.Placement.rcNormalPosition.left, MainWindowData.Placement.rcNormalPosition.top, MainWindowData.Placement.rcNormalPosition.right - MainWindowData.Placement.rcNormalPosition.left, MainWindowData.Placement.rcNormalPosition.bottom - MainWindowData.Placement.rcNormalPosition.top, SWP_ASYNCWINDOWPOS);

			MainWindow.Show(MainWindowData.Placement.showCmd);

			MainWindowData.PlacementMutex->unlock();
		}
		else
		{
			MainWindowData.PlacementMutex->unlock();

			MainWindowData.RectMutex->lock();

			SetWindowPos(MainWindow, HWND_TOP, MainWindowData.Rect.left, MainWindowData.Rect.top, MainWindowData.Rect.right - MainWindowData.Rect.left, MainWindowData.Rect.bottom - MainWindowData.Rect.top, SWP_ASYNCWINDOWPOS);

			MainWindow.Show(SW_SHOW);

			MainWindowData.RectMutex->unlock();
		}
	}
}

AuroraCore::AssetManager& Stellaris::RunTime::Application::GetAssets()
{
	return Assets;
}

const AuroraCore::AssetManager& Stellaris::RunTime::Application::GetAssets() const
{
	return Assets;
}

Stellaris::RunTime::Application* Stellaris::RunTime::Application::GetInstance()
{
	static Application _App;

	return &_App;
}

void Stellaris::RunTime::Application::RenderText(const char* _Text, const float& _AspectRatio, const float& _Fov, const AuroraCore::Graphics::GL::MeshWorldDataStruct& _WorldData, const int& _TextureAlbedo, const AuroraCore::Math::Vec4f& _Color, const AuroraCore::Graphics::GL::Shader& _Shader)
{
	AuroraCore::Math::Vec2f _LookupList[256];

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		_LookupList[_Index] = AuroraCore::Math::Vec2f(6.0f, 0.0f);
	}

	_LookupList['A'] = AuroraCore::Math::Vec2f(0.0f, 6.0f);
	_LookupList['B'] = AuroraCore::Math::Vec2f(1.0f, 6.0f);
	_LookupList['C'] = AuroraCore::Math::Vec2f(2.0f, 6.0f);
	_LookupList['D'] = AuroraCore::Math::Vec2f(3.0f, 6.0f);
	_LookupList['E'] = AuroraCore::Math::Vec2f(4.0f, 6.0f);
	_LookupList['F'] = AuroraCore::Math::Vec2f(5.0f, 6.0f);
	_LookupList['G'] = AuroraCore::Math::Vec2f(6.0f, 6.0f);
	_LookupList['H'] = AuroraCore::Math::Vec2f(0.0f, 5.0f);
	_LookupList['I'] = AuroraCore::Math::Vec2f(1.0f, 5.0f);
	_LookupList['J'] = AuroraCore::Math::Vec2f(2.0f, 5.0f);
	_LookupList['K'] = AuroraCore::Math::Vec2f(3.0f, 5.0f);
	_LookupList['L'] = AuroraCore::Math::Vec2f(4.0f, 5.0f);
	_LookupList['M'] = AuroraCore::Math::Vec2f(5.0f, 5.0f);
	_LookupList['N'] = AuroraCore::Math::Vec2f(6.0f, 5.0f);
	_LookupList['O'] = AuroraCore::Math::Vec2f(0.0f, 4.0f);
	_LookupList['P'] = AuroraCore::Math::Vec2f(1.0f, 4.0f);
	_LookupList['Q'] = AuroraCore::Math::Vec2f(2.0f, 4.0f);
	_LookupList['R'] = AuroraCore::Math::Vec2f(3.0f, 4.0f);
	_LookupList['S'] = AuroraCore::Math::Vec2f(4.0f, 4.0f);
	_LookupList['T'] = AuroraCore::Math::Vec2f(5.0f, 4.0f);
	_LookupList['U'] = AuroraCore::Math::Vec2f(6.0f, 4.0f);
	_LookupList['V'] = AuroraCore::Math::Vec2f(0.0f, 3.0f);
	_LookupList['W'] = AuroraCore::Math::Vec2f(1.0f, 3.0f);
	_LookupList['X'] = AuroraCore::Math::Vec2f(2.0f, 3.0f);
	_LookupList['Y'] = AuroraCore::Math::Vec2f(3.0f, 3.0f);
	_LookupList['Z'] = AuroraCore::Math::Vec2f(4.0f, 3.0f);
	_LookupList['1'] = AuroraCore::Math::Vec2f(5.0f, 3.0f);
	_LookupList['2'] = AuroraCore::Math::Vec2f(6.0f, 3.0f);
	_LookupList['3'] = AuroraCore::Math::Vec2f(0.0f, 2.0f);
	_LookupList['4'] = AuroraCore::Math::Vec2f(1.0f, 2.0f);
	_LookupList['5'] = AuroraCore::Math::Vec2f(2.0f, 2.0f);
	_LookupList['6'] = AuroraCore::Math::Vec2f(3.0f, 2.0f);
	_LookupList['7'] = AuroraCore::Math::Vec2f(4.0f, 2.0f);
	_LookupList['8'] = AuroraCore::Math::Vec2f(5.0f, 2.0f);
	_LookupList['9'] = AuroraCore::Math::Vec2f(6.0f, 2.0f);
	_LookupList['0'] = AuroraCore::Math::Vec2f(0.0f, 1.0f);
	_LookupList['!'] = AuroraCore::Math::Vec2f(1.0f, 1.0f);
	_LookupList['?'] = AuroraCore::Math::Vec2f(2.0f, 1.0f);
	_LookupList['.'] = AuroraCore::Math::Vec2f(3.0f, 1.0f);
	_LookupList[':'] = AuroraCore::Math::Vec2f(4.0f, 1.0f);
	_LookupList[','] = AuroraCore::Math::Vec2f(5.0f, 1.0f);
	_LookupList['-'] = AuroraCore::Math::Vec2f(6.0f, 1.0f);
	_LookupList['"'] = AuroraCore::Math::Vec2f(0.0f, 0.0f);
	_LookupList['('] = AuroraCore::Math::Vec2f(1.0f, 0.0f);
	_LookupList[')'] = AuroraCore::Math::Vec2f(2.0f, 0.0f);

	if (!_Text)
	{
		return;
	}

	size_t _Len = strlen(_Text);

	for (size_t _Index = 0; _Index < _Len; _Index++)
	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;

		_Camera.Fov = _Fov;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _AuxWorldData;

		_AuxWorldData.Position = _WorldData.Position + AuroraCore::Math::Vec3f(AuroraCore::Math::Mat2f::GetRotation(_WorldData.Angle) * AuroraCore::Math::Mat2f::GetScale((float)(_Index), (float)(_Index)) * AuroraCore::Math::Vec2f(_WorldData.Scale.x, 0.0f), 0.0f);
		_AuxWorldData.Angle = _WorldData.Angle;
		_AuxWorldData.Scale = _WorldData.Scale;

		AuroraCore::Graphics::GL::MaterialStruct _Material;

		_Material.TextureAlbedo = _TextureAlbedo;
		_Material.Color = _Color;
		_Material.Start = AuroraCore::Math::Vec2f(1.0f / 7.0f, 1.0f / 7.0f) * _LookupList[_Text[_Index]];
		_Material.Size = AuroraCore::Math::Vec2f(1.0f / 7.0f, 1.0f / 7.0f);

		RenderSprite(_AspectRatio, _Camera, _AuxWorldData, _Material, _Shader);
	}
}

void Stellaris::RunTime::Application::RenderSprite(const float _AspectRatio, const AuroraCore::Graphics::GL::CameraStruct& _Camera, const AuroraCore::Graphics::GL::MeshWorldDataStruct& _WorldData, const AuroraCore::Graphics::GL::MaterialStruct& _Material, const AuroraCore::Graphics::GL::Shader& _Shader)
{
	AuroraCore::Graphics::GL::UniformSetCamera(_Camera, _Shader, "u_Camera");

	AuroraCore::Graphics::GL::UniformSetMeshWorldData(_WorldData, _Shader, "u_WorldData");

	AuroraCore::Graphics::GL::UniformSetMaterial(_Material, _Shader, "u_Material");

	AuroraCore::Math::Mat4f _Model = AuroraCore::Graphics::GL::GetModelFromWorldData(_WorldData);
	AuroraCore::Math::Mat4f _View = AuroraCore::Graphics::GL::GetViewFromCamera(_Camera);
	AuroraCore::Math::Mat4f _Projection = AuroraCore::Graphics::GL::GetProjectionFromCamera(_Camera, _AspectRatio);
	AuroraCore::Math::Mat4f _MVP = _Projection * _View * _Model;

	AuroraCore::Graphics::GL::Uniform u_Model;
	AuroraCore::Graphics::GL::Uniform u_View;
	AuroraCore::Graphics::GL::Uniform u_Projection;
	AuroraCore::Graphics::GL::Uniform u_MVP;

	u_Model.GetLocation(_Shader, "u_Model");
	u_View.GetLocation(_Shader, "u_View");
	u_Projection.GetLocation(_Shader, "u_Projection");
	u_MVP.GetLocation(_Shader, "u_MVP");

	u_Model.SetMatrix4fv(_Model.Data());
	u_View.SetMatrix4fv(_View.Data());
	u_Projection.SetMatrix4fv(_Projection.Data());
	u_MVP.SetMatrix4fv(_MVP.Data());

	u_Model.ReleaseLocation();
	u_View.ReleaseLocation();
	u_Projection.ReleaseLocation();
	u_MVP.ReleaseLocation();

	AuroraCore::Graphics::GL::glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Stellaris::RunTime::Application::PlayCollectSound()
{
	AuroraCore::Sound::Source* _Source = new AuroraCore::Sound::Source;

	_Source->Create(SoundContext, CollectSound);
	_Source->Play(false);
	SoundSources.push_back(_Source);
}

void Stellaris::RunTime::Application::UpdateSound()
{
	for (size_t _Index = 0; _Index < SoundSources.size(); _Index++)
	{
		SoundSources[_Index]->UpdatePlayTime();

		if (SoundSources[_Index]->IsPlaying())
		{
			continue;
		}

		SoundSources[_Index]->Destroy();
		delete SoundSources[_Index];
		SoundSources.erase(SoundSources.begin() + _Index);
	}

	AuroraCore::Sound::UpdateDevices();

	size_t _DefaultIndex = AuroraCore::Sound::GetDefaultDeviceIndex();

	if (_DefaultIndex == MAXSIZE_T)
	{
		CleanUpSound();
		return;
	}

	if (AuroraCore::Sound::Devices[_DefaultIndex].Driver == CurrentDeviceDriver)
	{
		return;
	}

	CleanUpSound();
	InitSound();
}

void Stellaris::RunTime::Application::UpdateMute()
{
	Volume = 1 - Volume;

	if (Volume)
	{
		SoundContext.SetVolume(1.0f);
	}
	else
	{
		SoundContext.SetVolume(0.0f);
	}
}

void Stellaris::RunTime::Application::SetScore(const size_t _Score)
{
	Score = _Score;
}

const size_t Stellaris::RunTime::Application::GetScore() const
{
	return Score;
}

void Stellaris::RunTime::Application::SetHighScore(const size_t _Score)
{
	std::wofstream _FileOut;

	_FileOut.open(L"SavedData");

	if (!_FileOut.is_open())
	{
		return;
	}

	_FileOut << _Score;

	_FileOut.close();
}

const size_t Stellaris::RunTime::Application::GetHighScore() const
{
	std::wifstream _FileIn;

	_FileIn.open(L"SavedData");

	if (!_FileIn.is_open())
	{
		return 0;
	}

	size_t _HighScore = 0;

	_FileIn >> _HighScore;

	_FileIn.close();

	return _HighScore;
}

bool Stellaris::RunTime::Application::InitMainWindow()
{
	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	_WndClass.lpfnWndProc = Window::WindowProcedure;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = GetInstanceHandle();
	_WndClass.hIcon = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(STELLARIS_IDI_MAIN_ICON));
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = STELLARIS_WND_CLASS_NAME;
	_WndClass.hIconSm = LoadIcon(GetInstanceHandle(), MAKEINTRESOURCE(STELLARIS_IDI_MAIN_ICON));

	if (!RegisterClassEx(&_WndClass))
	{
		return false;
	}

	MainWindowData.PlacementMutex = &PlacementMutex;
	MainWindowData.RectMutex = &RectMutex;
	MainWindowData.FullScreenMutex = &FullScreenMutex;
	MainWindowData.CloseMutex = &CloseMutex;
	MainWindowData.MinSizeMutex = &MinSizeMutex;
	MainWindowData.InputMutex = &InputMutex;
	MainWindowData.ContextMutex = &ContextMutex;

	MainWindowData.Context = &Context;

	if (!MainWindow.Create(NULL, STELLARIS_WND_CLASS_NAME, AURORA_CORE_STRING_PREFIX("Stellaris"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_DESKTOP, NULL, GetInstanceHandle(), nullptr, NULL, Window::InitWindowThread, Window::CleanUpWindowThread, Window::InitWindow, Window::CleanUpWindow, &MainWindowData))
	{
		MainWindowData = Window::Data();
		UnregisterClass(_WndClass.lpszClassName, _WndClass.hInstance);
		return false;
	}

	SetSync(MainWindow.GetRefreshRate());

	return true;
}

void Stellaris::RunTime::Application::CleanUpMainWindow()
{
	if (!MainWindow.CheckOn())
	{
		return;
	}

	MainWindow.Destroy();
	MainWindowData = Window::Data();
	UnregisterClass(STELLARIS_WND_CLASS_NAME, GetInstanceHandle());
}

bool Stellaris::RunTime::Application::InitAssets()
{
	if (!Context.Bind())
	{
		return false;
	}

	{
		AuroraCore::Graphics::GL::MeshCPUCash _MeshCPU;

		{
			AuroraCore::Graphics::GL::VertexData _VertexData;

			_VertexData.Position = AuroraCore::Math::Vec3f(-0.5f, -0.5f, 1.0f);
			_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
			_VertexData.TextureCoords = AuroraCore::Math::Vec2f(0.0f, 0.0f);

			_MeshCPU.VBO.push_back(_VertexData);

			_VertexData.Position = AuroraCore::Math::Vec3f(-0.5f, 0.5f, 1.0f);
			_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
			_VertexData.TextureCoords = AuroraCore::Math::Vec2f(0.0f, 1.0f);

			_MeshCPU.VBO.push_back(_VertexData);

			_VertexData.Position = AuroraCore::Math::Vec3f(0.5f, 0.5f, 1.0f);
			_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
			_VertexData.TextureCoords = AuroraCore::Math::Vec2f(1.0f, 1.0f);

			_MeshCPU.VBO.push_back(_VertexData);

			_VertexData.Position = AuroraCore::Math::Vec3f(0.5f, -0.5f, 1.0f);
			_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
			_VertexData.TextureCoords = AuroraCore::Math::Vec2f(1.0f, 0.0f);

			_MeshCPU.VBO.push_back(_VertexData);
		}

		_MeshCPU.IBO.push_back(0);
		_MeshCPU.IBO.push_back(1);
		_MeshCPU.IBO.push_back(2);

		_MeshCPU.IBO.push_back(0);
		_MeshCPU.IBO.push_back(2);
		_MeshCPU.IBO.push_back(3);

		AuroraCore::Graphics::GL::Mesh* _Quad = new AuroraCore::Graphics::GL::Mesh;

		if (!_Quad)
		{
			return false;
		}

		if (!_Quad->VBO.Create(_MeshCPU.VBO))
		{
			delete _Quad;
			return false;
		}

		_Quad->VBO.Bind();

		if (!_Quad->IBO.Create(_MeshCPU.IBO))
		{
			_Quad->VBO.Destroy();
			delete _Quad;
			return false;
		}

		_Quad->IBO.Bind();

		if (!Assets.AddAsset(_Quad, L"Quad"))
		{
			_Quad->VBO.Destroy();
			delete _Quad;
			return false;
		}
	}

	{
		AuroraCore::Graphics::GL::VertexAttribArray* _VAO = new AuroraCore::Graphics::GL::VertexAttribArray;

		if (!_VAO)
		{
			return false;
		}

		if (!_VAO->Create())
		{
			delete _VAO;
			return false;
		}

		_VAO->Bind();

		if (!_VAO->EnableAttrib(0, 3, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::Position) / sizeof(float)))
		{
			_VAO->Destroy();
			delete _VAO;
			return false;
		}

		if (!_VAO->EnableAttrib(1, 4, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::Color) / sizeof(float)))
		{
			_VAO->Destroy();
			delete _VAO;
			return false;
		}

		if (!_VAO->EnableAttrib(2, 2, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::TextureCoords) / sizeof(float)))
		{
			_VAO->Destroy();
			delete _VAO;
			return false;
		}

		if (!Assets.AddAsset(_VAO, L"VAO"))
		{
			_VAO->Destroy();
			delete _VAO;
			return false;
		}
	}

	{
		char* _VertexShader = nullptr;

		{
			HRSRC _ShaderResource = FindResource(GetInstanceHandle(), MAKEINTRESOURCE(STELLARIS_IDS_DEFAULT_VERTEX_SHADER), MAKEINTRESOURCE(AURORA_CORE_GLSL_RESOURCE));

			if (!_ShaderResource)
			{
				return false;
			}

			size_t _Size = SizeofResource(GetInstanceHandle(), _ShaderResource);

			if (!_Size)
			{
				return false;
			}

			const char* _ResourceMemory = (const char*)(LoadResource(GetInstanceHandle(), _ShaderResource));

			if (!_ResourceMemory)
			{
				return false;
			}

			_VertexShader = new char[_Size + 1];

			if (!_VertexShader)
			{
				FreeResource((HGLOBAL)(_ResourceMemory));
				return false;
			}

			_VertexShader[_Size] = '\0';

			for (size_t _Index = 0; _Index < _Size; _Index++)
			{
				_VertexShader[_Index] = _ResourceMemory[_Index];
			}

			FreeResource((HGLOBAL)(_ResourceMemory));
		}

		char* _FragmentShader = nullptr;

		{
			HRSRC _ShaderResource = FindResource(GetInstanceHandle(), MAKEINTRESOURCE(STELLARIS_IDS_DEFAULT_FRAGMENT_SHADER), MAKEINTRESOURCE(AURORA_CORE_GLSL_RESOURCE));

			if (!_ShaderResource)
			{
				delete[] _VertexShader;
				return false;
			}

			size_t _Size = SizeofResource(GetInstanceHandle(), _ShaderResource);

			if (!_Size)
			{
				delete[] _VertexShader;
				return false;
			}

			const char* _ResourceMemory = (const char*)(LoadResource(GetInstanceHandle(), _ShaderResource));

			if (!_ResourceMemory)
			{
				delete[] _VertexShader;
				return false;
			}

			_FragmentShader = new char[_Size + 1];

			if (!_FragmentShader)
			{
				FreeResource((HGLOBAL)(_ResourceMemory));
				delete[] _VertexShader;
				return false;
			}

			_FragmentShader[_Size] = '\0';

			for (size_t _Index = 0; _Index < _Size; _Index++)
			{
				_FragmentShader[_Index] = _ResourceMemory[_Index];
			}

			FreeResource((HGLOBAL)(_ResourceMemory));
		}

		AuroraCore::Graphics::GL::Shader* _DefaultShader = new AuroraCore::Graphics::GL::Shader;

		if (!_DefaultShader)
		{
			delete[] _VertexShader;
			delete[] _FragmentShader;
			return false;
		}

		if (!_DefaultShader->Create(_VertexShader, _FragmentShader))
		{
			delete _DefaultShader;
			delete[] _VertexShader;
			delete[] _FragmentShader;
			return false;
		}

		if (!Assets.AddAsset(_DefaultShader, L"DefaultShader"))
		{
			_DefaultShader->Destroy();
			delete _DefaultShader;
			delete[] _VertexShader;
			delete[] _FragmentShader;
			return false;
		}

		delete[] _VertexShader;
		delete[] _FragmentShader;
	}

	{
		AuroraCore::Graphics::Assets::Image _WhiteTextureCPU;

		if (!_WhiteTextureCPU.Create(1, 1, 4))
		{
			return false;
		}

		_WhiteTextureCPU[0] = 255;
		_WhiteTextureCPU[1] = 255;
		_WhiteTextureCPU[2] = 255;
		_WhiteTextureCPU[3] = 255;

		AuroraCore::Graphics::GL::Texture2D* _WhiteTexture = new AuroraCore::Graphics::GL::Texture2D;

		if (!_WhiteTexture)
		{
			_WhiteTextureCPU.Destroy();
			return false;
		}

		if (!_WhiteTexture->Create(_WhiteTextureCPU))
		{
			delete _WhiteTexture;
			_WhiteTextureCPU.Destroy();
			return false;
		}

		_WhiteTextureCPU.Destroy();

		if (!Assets.AddAsset(_WhiteTexture, L"WhiteTexture"))
		{
			_WhiteTexture->Destroy();
			delete _WhiteTexture;
			return false;
		}
	}

	{
		AuroraCore::Graphics::Assets::Image _TextAttlassCPU;

		if (!_TextAttlassCPU.Load(L".\\Sprites\\Characters.bmp"))
		{
			return false;
		}

		for (size_t _Index = 0; _Index < _TextAttlassCPU.GetWidth() * _TextAttlassCPU.GetHeight(); _Index++)
		{
			if (_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 0] == 55 &&
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 1] == 148 &&
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 2] == 110)
			{
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 0] = 0;
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 1] = 0;
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 2] = 0;
				_TextAttlassCPU[_Index * _TextAttlassCPU.GetChannelsCount() + 3] = 0;
			}
		}

		AuroraCore::Graphics::GL::Texture2D* _TextAttlass = new AuroraCore::Graphics::GL::Texture2D;

		if (!_TextAttlass)
		{
			_TextAttlassCPU.Destroy();
			return false;
		}

		if (!_TextAttlass->Create(_TextAttlassCPU))
		{
			delete _TextAttlass;
			_TextAttlassCPU.Destroy();
			return false;
		}

		_TextAttlassCPU.Destroy();

		if (!Assets.AddAsset(_TextAttlass, L"TextAttlass"))
		{
			_TextAttlass->Destroy();
			delete _TextAttlass;
			return false;
		}
	}

	{
		AuroraCore::Graphics::Assets::Image _SpritesCPU;

		if (!_SpritesCPU.Load(L".\\Sprites\\Sprites.bmp"))
		{
			return false;
		}

		for (size_t _Index = 0; _Index < _SpritesCPU.GetWidth() * _SpritesCPU.GetHeight(); _Index++)
		{
			if (_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 0] == 55 &&
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 1] == 148 &&
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 2] == 110)
			{
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 0] = 0;
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 1] = 0;
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 2] = 0;
				_SpritesCPU[_Index * _SpritesCPU.GetChannelsCount() + 3] = 0;
			}
		}

		AuroraCore::Graphics::GL::Texture2D* _Sprites = new AuroraCore::Graphics::GL::Texture2D;

		if (!_Sprites)
		{
			_SpritesCPU.Destroy();
			return false;
		}

		if (!_Sprites->Create(_SpritesCPU))
		{
			delete _Sprites;
			_SpritesCPU.Destroy();
			return false;
		}

		_SpritesCPU.Destroy();

		if (!Assets.AddAsset(_Sprites, L"Sprites"))
		{
			_Sprites->Destroy();
			delete _Sprites;
			return false;
		}
	}

	{
		AuroraCore::Graphics::Assets::Image _BackgroundCPU;

		if (!_BackgroundCPU.Load(L".\\Sprites\\Background.bmp"))
		{
			return false;
		}

		AuroraCore::Graphics::GL::Texture2D* _Background = new AuroraCore::Graphics::GL::Texture2D;

		if (!_Background)
		{
			_BackgroundCPU.Destroy();
			return false;
		}

		if (!_Background->Create(_BackgroundCPU))
		{
			delete _Background;
			_BackgroundCPU.Destroy();
			return false;
		}

		_BackgroundCPU.Destroy();

		if (!Assets.AddAsset(_Background, L"Background"))
		{
			_Background->Destroy();
			delete _Background;
			return false;
		}
	}

	{
		AuroraCore::Sound::CPUBuffer* _CPUBuffer = new AuroraCore::Sound::CPUBuffer;

		if (!_CPUBuffer)
		{
			return false;
		}

		_CPUBuffer->Data = AuroraCore::Sound::CPUBuffer::LoadSoundFile(L".\\Sound\\Background.wav", _CPUBuffer->Size, _CPUBuffer->SoundInfo);

		if (!_CPUBuffer->Data)
		{
			delete _CPUBuffer;
			return false;
		}

		if (!Assets.AddAsset(_CPUBuffer, L"Background music"))
		{
			delete[] _CPUBuffer->Data;
			delete _CPUBuffer;
			return false;
		}
	}

	{
		AuroraCore::Sound::CPUBuffer* _CPUBuffer = new AuroraCore::Sound::CPUBuffer;

		if (!_CPUBuffer)
		{
			return false;
		}

		_CPUBuffer->Data = AuroraCore::Sound::CPUBuffer::LoadSoundFile(L".\\Sound\\Collect SFX.wav", _CPUBuffer->Size, _CPUBuffer->SoundInfo);

		if (!_CPUBuffer->Data)
		{
			delete _CPUBuffer;
			return false;
		}

		if (!Assets.AddAsset(_CPUBuffer, L"Collect SFX"))
		{
			delete[] _CPUBuffer->Data;
			delete _CPUBuffer;
			return false;
		}
	}

	return true;
}

void Stellaris::RunTime::Application::CleanUpAssets()
{
	{
		AuroraCore::Sound::CPUBuffer* _CPUBuffer = (AuroraCore::Sound::CPUBuffer*)(Assets.GetAssetData(L"Collect SFX"));

		if (_CPUBuffer)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"Collect SFX"));
			delete[] _CPUBuffer->Data;
			delete _CPUBuffer;
		}
	}

	{
		AuroraCore::Sound::CPUBuffer* _CPUBuffer = (AuroraCore::Sound::CPUBuffer*)(Assets.GetAssetData(L"Background music"));

		if (_CPUBuffer)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"Background music"));
			delete[] _CPUBuffer->Data;
			delete _CPUBuffer;
		}
	}

	{
		AuroraCore::Graphics::GL::Texture2D* _Background = (AuroraCore::Graphics::GL::Texture2D*)(Assets.GetAssetData(L"Background"));

		if (_Background)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"Background"));
			_Background->Destroy();
			delete _Background;
		}
	}

	{
		AuroraCore::Graphics::GL::Texture2D* _Sprites = (AuroraCore::Graphics::GL::Texture2D*)(Assets.GetAssetData(L"Sprites"));

		if (_Sprites)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"Sprites"));
			_Sprites->Destroy();
			delete _Sprites;
		}
	}

	{
		AuroraCore::Graphics::GL::Texture2D* _TextAttlass = (AuroraCore::Graphics::GL::Texture2D*)(Assets.GetAssetData(L"TextAttlass"));

		if (_TextAttlass)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"TextAttlass"));
			_TextAttlass->Destroy();
			delete _TextAttlass;
		}
	}

	{
		AuroraCore::Graphics::GL::Texture2D* _WhiteTexture = (AuroraCore::Graphics::GL::Texture2D*)(Assets.GetAssetData(L"WhiteTexture"));

		if (_WhiteTexture)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"WhiteTexture"));
			_WhiteTexture->Destroy();
			delete _WhiteTexture;
		}
	}

	{
		AuroraCore::Graphics::GL::Shader* _DefaultShader = (AuroraCore::Graphics::GL::Shader*)(Assets.GetAssetData(L"DefaultShader"));

		if (_DefaultShader)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"DefaultShader"));
			_DefaultShader->Destroy();
			delete _DefaultShader;
		}
	}

	{
		AuroraCore::Graphics::GL::VertexAttribArray* _VAO = (AuroraCore::Graphics::GL::VertexAttribArray*)(Assets.GetAssetData(L"VAO"));

		if (_VAO)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"VAO"));
			_VAO->Destroy();
			delete _VAO;
		}
	}

	{
		AuroraCore::Graphics::GL::Mesh* _Quad = (AuroraCore::Graphics::GL::Mesh*)(Assets.GetAssetData(L"Quad"));

		if (_Quad)
		{
			Assets.RemoveAsset(Assets.GetAssetIndex(L"Quad"));
			_Quad->VBO.Destroy();
			_Quad->IBO.Destroy();
			delete _Quad;
		}
	}
}

bool Stellaris::RunTime::Application::InitSound()
{
	AuroraCore::Sound::UpdateDevices();

	size_t _DefaultIndex = AuroraCore::Sound::GetDefaultDeviceIndex();

	if (_DefaultIndex == MAXSIZE_T)
	{
		return false;
	}

	CurrentDeviceDriver = AuroraCore::Sound::Devices[_DefaultIndex].Driver;

	SoundContext.Create(_DefaultIndex);

	Volume = true;
	SoundContext.SetVolume(1.0f);

	AuroraCore::Sound::CPUBuffer* _BackgroundSound = (AuroraCore::Sound::CPUBuffer*)(Assets.GetAssetData(L"Background music"));

	if (!_BackgroundSound)
	{
		return false;
	}

	BackgroundSound.Create(SoundContext, _BackgroundSound->Size, _BackgroundSound->SoundInfo, _BackgroundSound->Data);

	AuroraCore::Sound::CPUBuffer* _CollectSFX = (AuroraCore::Sound::CPUBuffer*)(Assets.GetAssetData(L"Collect SFX"));

	if (!_CollectSFX)
	{
		return false;
	}

	CollectSound.Create(SoundContext, _CollectSFX->Size, _CollectSFX->SoundInfo, _CollectSFX->Data);

	AuroraCore::Sound::Source* _BackgroundSource = new AuroraCore::Sound::Source;

	_BackgroundSource->Create(SoundContext, BackgroundSound);
	_BackgroundSource->Play(true);
	SoundSources.push_back(_BackgroundSource);

	return true;
}

void Stellaris::RunTime::Application::CleanUpSound()
{
	for (size_t _Index = 0; _Index < SoundSources.size(); _Index++)
	{
		SoundSources[_Index]->Stop();
		SoundSources[_Index]->Destroy();
		delete SoundSources[_Index];
	}

	SoundSources.clear();

	BackgroundSound.Destroy();
	CollectSound.Destroy();

	SoundContext.Destroy();
	CurrentDeviceDriver = L"";
}

void Stellaris::RunTime::Application::Setup()
{
	srand(time(nullptr));

	if (GetArgC() != 1)
	{
		Close(-1);
		return;
	}

	if (!InitMainWindow())
	{
		Close(-1);
		return;
	}

	if (!InitAssets())
	{
		Close(-1);
		return;
	}

	if (!InitSound())
	{
		Close(-1);
		return;
	}

	if (!MainWindow.Show(GetShowCmd()))
	{
		Close(-1);
		return;
	}

	SetCurrentMenu(_StartMenu);
	TurnOn();
}

void Stellaris::RunTime::Application::Update()
{
	switch (GetCurrentMenu())
	{
	case _PlayMenu:
	{
		PlayMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case _StartMenu:
	{
		StartMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case _RestartMenu:
	{
		RestartMenu _Menu;
		_Menu.Run(this);
		break;
	}
	case AuroraCore::RunTime::_NullMenu:
	{
		AURORA_CORE_DEBUG_BREAK();
		Close(-1);
		break;
	}
	default:
	{
		AURORA_CORE_DEBUG_BREAK();
		Close(-1);
		break;
	}
	}
}

void Stellaris::RunTime::Application::Stop()
{
	CleanUpSound();
	CleanUpAssets();
	CleanUpMainWindow();
}
