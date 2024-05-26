#include "..\Headers\Stellaris.hpp"



Stellaris::RunTime::StartMenu::StartMenu() : AuroraCore::RunTime::Menu(), Keys(), ControllerStates(), HighScore(0)
{

}

Stellaris::RunTime::StartMenu::~StartMenu()
{

}

const uint64_t Stellaris::RunTime::StartMenu::GetType() const
{
	return _StartMenu;
}

void Stellaris::RunTime::StartMenu::Setup()
{
	Application& _Application = *(Application*)(GetApplicationObj());

	HighScore = _Application.GetHighScore();

	DeleteInput();

	TurnOn();
}

void Stellaris::RunTime::StartMenu::Update()
{
	AURORA_CORE_LOG_OUTPUT_DEBUG_LINE(AURORA_CORE_TO_STRING(1.0f / GetFrameTime(AuroraCore::_Previous)).c_str());

	Input();
	Engine();
	FrameBuild();
}

void Stellaris::RunTime::StartMenu::Stop()
{

}

void Stellaris::RunTime::StartMenu::Input()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	AuroraCore::Window& _MainWindow = _ApplicationObj->GetMainWindow();

	Window::Data& _MainWindowData = _ApplicationObj->GetMainWindowData();

	_MainWindowData.InputMutex->lock();

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[AuroraCore::_Previous][_Index] = Keys[AuroraCore::_Current][_Index];
		Keys[AuroraCore::_Current][_Index] = _MainWindowData.Keys[_Index];
	}

	_MainWindowData.InputMutex->unlock();

	ControllerStates[AuroraCore::_Previous] = ControllerStates[AuroraCore::_Current];
	AuroraCore::Input::Controller::GetState(0, ControllerStates[AuroraCore::_Current]);

	_MainWindowData.InputMutex->lock();

	if (!_MainWindowData.Focus)
	{
		DeleteInput();
	}

	_MainWindowData.InputMutex->unlock();
}

void Stellaris::RunTime::StartMenu::DeleteInput()
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[AuroraCore::_Previous][_Index] = false;
		Keys[AuroraCore::_Current][_Index] = false;
	}

	AuroraCore::Input::Controller::CleanState(ControllerStates[AuroraCore::_Previous]);
	AuroraCore::Input::Controller::CleanState(ControllerStates[AuroraCore::_Current]);
}

void Stellaris::RunTime::StartMenu::Engine()
{
	Application* _ApplicationObj = (Application*)(GetApplicationObj());

	AuroraCore::Window& _MainWindow = _ApplicationObj->GetMainWindow();

	Window::Data& _MainWindowData = _ApplicationObj->GetMainWindowData();

	if ((Keys[AuroraCore::_Previous][VK_F11] || ControllerStates[AuroraCore::_Previous].ShoulderRight) && !(Keys[AuroraCore::_Current][VK_F11] || ControllerStates[AuroraCore::_Current].ShoulderRight))
	{
		_ApplicationObj->UpdateFullScreen();
	}

	if ((Keys[AuroraCore::_Previous]['M'] || ControllerStates[AuroraCore::_Previous].Back) && !(Keys[AuroraCore::_Current]['M'] || ControllerStates[AuroraCore::_Current].Back))
	{
		_ApplicationObj->UpdateMute();
	}

	if ((Keys[AuroraCore::_Previous]['P'] || ControllerStates[AuroraCore::_Previous].Start) && !(Keys[AuroraCore::_Current]['P'] || ControllerStates[AuroraCore::_Current].Start))
	{
		Close(_PlayMenu);
	}

	if ((Keys[AuroraCore::_Previous][VK_ESCAPE] || ControllerStates[AuroraCore::_Previous].ButtonB) && !(Keys[AuroraCore::_Current][VK_ESCAPE] || ControllerStates[AuroraCore::_Current].ButtonB))
	{
		_ApplicationObj->Close(0);
	}

	_ApplicationObj->SetSync(_MainWindow.GetRefreshRate());

	_MainWindowData.CloseMutex->lock();

	if (_MainWindowData.Close)
	{
		_ApplicationObj->Close(0);
	}

	_MainWindowData.CloseMutex->unlock();

	_ApplicationObj->UpdateSound();
}

void Stellaris::RunTime::StartMenu::FrameBuild()
{
	Application& _Application = *(Application*)(GetApplicationObj());
	AuroraCore::Window& _Wnd = _Application.GetMainWindow();
	Window::Data& _WndData = *(Window::Data*)(_Wnd.GetUserData());
	AuroraCore::AssetManager& _Assets = _Application.GetAssets();

	AuroraCore::Graphics::GL::Texture2D& _WhiteTexture = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"WhiteTexture"));
	AuroraCore::Graphics::GL::Texture2D& _TextAttlass = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"TextAttlass"));
	AuroraCore::Graphics::GL::Texture2D& _Sprites = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"Sprites"));
	AuroraCore::Graphics::GL::Texture2D& _Background = *(AuroraCore::Graphics::GL::Texture2D*)(_Assets.GetAssetData(L"Background"));
	AuroraCore::Graphics::GL::Shader& _DefaultShader = *(AuroraCore::Graphics::GL::Shader*)(_Assets.GetAssetData(L"DefaultShader"));
	AuroraCore::Graphics::GL::VertexAttribArray& _VAO = *(AuroraCore::Graphics::GL::VertexAttribArray*)(_Assets.GetAssetData(L"VAO"));
	AuroraCore::Graphics::GL::Mesh& _Quad = *(AuroraCore::Graphics::GL::Mesh*)(_Assets.GetAssetData(L"Quad"));

	size_t _Width = 0, _Height = 0;
	_Wnd.GetClientSize(_Width, _Height);

	_WndData.Context->Bind();

	PAINTSTRUCT _PaintStruct = { 0 };

	HDC _WndDC = BeginPaint(_Wnd, &_PaintStruct);

	AuroraCore::Graphics::GL::glEnable(GL_BLEND);
	AuroraCore::Graphics::GL::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	AuroraCore::Graphics::GL::glDisable(GL_DEPTH_TEST);
	AuroraCore::Graphics::GL::glEnable(GL_CULL_FACE);
	AuroraCore::Graphics::GL::glCullFace(GL_BACK);
	AuroraCore::Graphics::GL::glFrontFace(GL_CW);

	AuroraCore::Graphics::GL::glViewport(0, 0, (int)(_Width), (int)(_Height));

	AuroraCore::Graphics::GL::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	AuroraCore::Graphics::GL::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE0);
	_WhiteTexture.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE1);
	_TextAttlass.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE2);
	_Sprites.Bind();

	AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE3);
	_Background.Bind();

	_DefaultShader.Bind();
	_VAO.Bind();
	_Quad.IBO.Bind();
	_Quad.VBO.Bind();

	{
		AuroraCore::Graphics::GL::CameraStruct _Camera;
		_Camera.Fov = 1.0f;

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
		if ((float)(_Width) / (float)(_Height) >= 16.0f / 9.0f)
		{
			_WorldData.Scale.x = (float)(_Width) / (float)(_Height);
			_WorldData.Scale.y = _WorldData.Scale.x / 16.0f * 9.0f;
		}
		else
		{
			_WorldData.Scale.x = 16.0f / 9.0f;
		}

		AuroraCore::Graphics::GL::MaterialStruct _Material;
		_Material.TextureAlbedo = 3;

		_Application.RenderSprite((float)(_Width) / (float)(_Height), _Camera, _WorldData, _Material, _DefaultShader);
	}

	{
		std::string _Score = "HIGHSCORE:" + std::to_string(HighScore);

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, 9.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	{
		std::string _Score = "PLAY:KEYBOARD-P,CONTROLLER-START";

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, 1.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	{
		std::string _Score = "EXIT:KEYBOARD-ESCAPE,CONTROLLER-B";

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, -1.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	{
		std::string _Score = "F.SCREEN:KEYBOARD-F11,CONTROLLER-R1";

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, -7.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	{
		std::string _Score = "MUTE:KEYBOARD-M,CONTROLLER-BACK";

		AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;

		_WorldData.Position = AuroraCore::Math::Vec3f(-(float)(_Score.length() - 1) / 2.0f, -9.0f, 0.0f);
		_WorldData.Scale = AuroraCore::Math::Vec2f(1.0f, 1.0f);
		_WorldData.Angle = 0.0f;

		_Application.RenderText(_Score.c_str(), (float)(_Width) / (float)(_Height), 20.0f, _WorldData, 1, AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), _DefaultShader);
	}

	AuroraCore::Graphics::GL::wglSwapIntervalEXT(1);

	SwapBuffers(_WndDC);

	EndPaint(_Wnd, &_PaintStruct);
}
