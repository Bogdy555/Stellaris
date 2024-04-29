#include "..\Headers\Stellaris.hpp"
#include <fstream>



struct WndData
{
	WndData() : CloseMutex(), Close(false), ContextMutex(), Context(), InputMutex(), KeyDown()
	{

	}

	std::mutex CloseMutex;
	bool Close;

	std::mutex ContextMutex;
	AuroraCore::Graphics::GL::Context Context;

	std::mutex InputMutex;
	bool KeyDown[256];
};



bool InitWindow(AuroraCore::Window* _Wnd)
{
	WndData* _WndData = (WndData*)(_Wnd->GetUserData());

	AURORA_CORE_ASSERT(_WndData != nullptr);

	_WndData->ContextMutex.lock();

	if (!_WndData->Context.Create(*_Wnd))
	{
		_WndData->ContextMutex.unlock();
		return false;
	}

	_WndData->ContextMutex.unlock();

	return true;
}



void CleanUpWindow(AuroraCore::Window* _Wnd)
{
	WndData* _WndData = (WndData*)(_Wnd->GetUserData());

	AURORA_CORE_ASSERT(_WndData != nullptr);

	_WndData->ContextMutex.lock();

	_WndData->Context.Destroy();

	_WndData->ContextMutex.unlock();
}



LRESULT CALLBACK WndProc(_In_ HWND _hWnd, _In_ UINT _Msg, _In_ WPARAM _wParam, _In_ LPARAM _lParam)
{
	AuroraCore::Window* _Wnd = AuroraCore::Window::GetWindowPtr(_hWnd);

	AURORA_CORE_ASSERT(_Wnd != nullptr);

	WndData* _WndData = (WndData*)(_Wnd->GetUserData());

	AURORA_CORE_ASSERT(_WndData != nullptr);

	switch (_Msg)
	{
	case WM_CLOSE:
	{
		_WndData->CloseMutex.lock();

		_WndData->Close = true;

		_WndData->CloseMutex.unlock();

		break;
	}
	case WM_KEYDOWN:
	{
		_WndData->InputMutex.lock();

		_WndData->KeyDown[_wParam] = true;

		_WndData->InputMutex.unlock();

		break;
	}
	case WM_KEYUP:
	{
		_WndData->InputMutex.lock();

		_WndData->KeyDown[_wParam] = false;

		_WndData->InputMutex.unlock();

		break;
	}
	case WM_KILLFOCUS:
	{
		_WndData->InputMutex.lock();

		for (size_t _Index = 0; _Index < 256; _Index++)
		{
			_WndData->KeyDown[_Index] = false;
		}

		_WndData->InputMutex.unlock();

		break;
	}
	case WM_ERASEBKGND:
	{
		break;
	}
	default:
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	}

	return 0;
}



int WINAPI wWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance, _In_ LPWSTR _CmdLine, _In_ int _ShowCmd)
{
	if (!AuroraCore::Graphics::GL::Load())
	{
		return -1;
	}

	WNDCLASSEX _WndClass = { 0 };

	_WndClass.cbSize = sizeof(WNDCLASSEX);
	_WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	_WndClass.lpfnWndProc = WndProc;
	_WndClass.cbClsExtra = 0;
	_WndClass.cbWndExtra = 0;
	_WndClass.hInstance = _hInstance;
	_WndClass.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(STELLARIS_IDI_MAIN_ICON));
	_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClass.hbrBackground = NULL;
	_WndClass.lpszMenuName = nullptr;
	_WndClass.lpszClassName = L"WndClass";
	_WndClass.hIconSm = LoadIcon(_hInstance, MAKEINTRESOURCE(STELLARIS_IDI_MAIN_ICON));

	if (!RegisterClassEx(&_WndClass))
	{
		AuroraCore::Graphics::GL::Unload();
		return -1;
	}

	AuroraCore::Window _Wnd;
	WndData _WndData;

	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		_WndData.KeyDown[_Index] = false;
	}

	if (!_Wnd.Create(NULL, L"WndClass", L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_DESKTOP, NULL, _hInstance, nullptr, NULL, nullptr, nullptr, InitWindow, CleanUpWindow, &_WndData))
	{
		UnregisterClass(L"WndClass", _hInstance);
		AuroraCore::Graphics::GL::Unload();
		return -1;
	}

	AuroraCore::Graphics::GL::Mesh _Mesh;
	AuroraCore::Graphics::GL::MeshCPUCash _CPUMesh;

	{
		AuroraCore::Graphics::GL::VertexData _VertexData;

		_VertexData.Position = AuroraCore::Math::Vec3f(-0.5f, -0.5f, 0.0f);
		_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 0.0f, 0.0f, 1.0f);
		_VertexData.TextureCoords = AuroraCore::Math::Vec2f(0.0f, 0.0f);

		_CPUMesh.VBO.push_back(_VertexData);

		_VertexData.Position = AuroraCore::Math::Vec3f(-0.5f, 0.5f, 0.0f);
		_VertexData.Color = AuroraCore::Math::Vec4f(0.0f, 1.0f, 0.0f, 1.0f);
		_VertexData.TextureCoords = AuroraCore::Math::Vec2f(0.0f, 1.0f);

		_CPUMesh.VBO.push_back(_VertexData);

		_VertexData.Position = AuroraCore::Math::Vec3f(0.5f, 0.5f, 0.0f);
		_VertexData.Color = AuroraCore::Math::Vec4f(0.0f, 0.0f, 1.0f, 1.0f);
		_VertexData.TextureCoords = AuroraCore::Math::Vec2f(1.0f, 1.0f);

		_CPUMesh.VBO.push_back(_VertexData);

		_VertexData.Position = AuroraCore::Math::Vec3f(0.5f, -0.5f, 0.0f);
		_VertexData.Color = AuroraCore::Math::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
		_VertexData.TextureCoords = AuroraCore::Math::Vec2f(1.0f, 0.0f);

		_CPUMesh.VBO.push_back(_VertexData);

		_CPUMesh.IBO.push_back(0);
		_CPUMesh.IBO.push_back(1);
		_CPUMesh.IBO.push_back(2);

		_CPUMesh.IBO.push_back(0);
		_CPUMesh.IBO.push_back(2);
		_CPUMesh.IBO.push_back(3);

		_WndData.ContextMutex.lock();
		_WndData.Context.Bind();
		_WndData.ContextMutex.unlock();

		_Mesh.VBO.Create(_CPUMesh.VBO);
		_Mesh.VBO.Bind();

		_Mesh.IBO.Create(_CPUMesh.IBO);
		_Mesh.IBO.Bind();
	}

	AuroraCore::Graphics::GL::VertexAttribArray _VAO;

	_VAO.Create();
	_VAO.Bind();

	_VAO.EnableAttrib(0, 3, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::Position) / sizeof(float));
	_VAO.EnableAttrib(1, 4, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::Color) / sizeof(float));
	_VAO.EnableAttrib(2, 2, sizeof(AuroraCore::Graphics::GL::VertexData) / sizeof(float), offsetof(AuroraCore::Graphics::GL::VertexData, AuroraCore::Graphics::GL::VertexData::TextureCoords) / sizeof(float));

	AuroraCore::Graphics::GL::Shader _Shader;

	{
		std::ifstream _fInV;
		_fInV.open(".\\Shaders\\DefaultVertexShader.glsl");

		std::ifstream _fInF;
		_fInF.open(".\\Shaders\\DefaultFragmentShader.glsl");

		_fInV.seekg(0, std::ios::end);
		_fInF.seekg(0, std::ios::end);

		size_t _VSLen = (size_t)(_fInV.tellg());
		size_t _FSLen = (size_t)(_fInF.tellg());

		_fInV.seekg(0, std::ios::beg);
		_fInF.seekg(0, std::ios::beg);

		char* _VS = new char[_VSLen + 1];
		char* _FS = new char[_FSLen + 1];

		ZeroMemory(_VS, sizeof(char) * (_VSLen + 1));
		ZeroMemory(_FS, sizeof(char) * (_FSLen + 1));

		_fInV.read(_VS, (std::streamsize)(_VSLen) + 1);
		_fInF.read(_FS, (std::streamsize)(_FSLen) + 1);

		_fInV.close();
		_fInF.close();

		_Shader.Create(_VS, _FS);
		_Shader.Bind();

		delete[] _VS;
		delete[] _FS;
	}

	AuroraCore::Graphics::GL::Texture2D _WhiteTexture;

	{
		AuroraCore::Graphics::Assets::Image _Image;

		_Image.Create(1, 1, 4);

		uint8_t* _Data = _Image.GetData();

		_Data[(0 + 0 * _Image.GetWidth()) * _Image.GetChannelsCount() + 0] = 255;
		_Data[(0 + 0 * _Image.GetWidth()) * _Image.GetChannelsCount() + 1] = 255;
		_Data[(0 + 0 * _Image.GetWidth()) * _Image.GetChannelsCount() + 2] = 255;
		_Data[(0 + 0 * _Image.GetWidth()) * _Image.GetChannelsCount() + 3] = 255;

		_WhiteTexture.Create(_Image);
		_WhiteTexture.Bind();

		_Image.Destroy();
	}

	bool AppOn = true;

	AuroraCore::Graphics::GL::CameraStruct _Camera;
	AuroraCore::Graphics::GL::MeshWorldDataStruct _WorldData;
	AuroraCore::Graphics::GL::MaterialStruct _Material;

	float _DeltaTime = 0.0f;

	_Wnd.Show(_ShowCmd);

	while (AppOn)
	{
		std::chrono::system_clock::time_point _Start = std::chrono::system_clock::now();

		_WndData.InputMutex.lock();

		float _Speed = 2.0f;

		if (_WndData.KeyDown['A'])
		{
			_Camera.Position.x -= _Speed * _DeltaTime;
		}

		if (_WndData.KeyDown['D'])
		{
			_Camera.Position.x += _Speed * _DeltaTime;
		}

		if (_WndData.KeyDown[VK_SHIFT])
		{
			_Camera.Position.y -= _Speed * _DeltaTime;
		}

		if (_WndData.KeyDown[VK_SPACE])
		{
			_Camera.Position.y += _Speed * _DeltaTime;
		}

		_WndData.InputMutex.unlock();

		_WndData.CloseMutex.lock();

		if (_WndData.Close)
		{
			AppOn = false;

			_WndData.Close = false;
		}

		_WndData.CloseMutex.unlock();

		_WndData.ContextMutex.lock();

		_WndData.Context.Bind();
		_Mesh.VBO.Bind();
		_Mesh.IBO.Bind();
		_VAO.Bind();
		_Shader.Bind();

		size_t _Width, _Height;

		_Wnd.GetClientSize(_Width, _Height);

		AuroraCore::Graphics::GL::glViewport(0, 0, (int)(_Width), (int)(_Height));

		AuroraCore::Graphics::GL::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		AuroraCore::Graphics::GL::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		AuroraCore::Graphics::GL::glActiveTexture(GL_TEXTURE0);
		_WhiteTexture.Bind();

		AuroraCore::Graphics::GL::UniformSetCamera(_Camera, _Shader, "u_Camera");
		AuroraCore::Graphics::GL::UniformSetMeshWorldData(_WorldData, _Shader, "u_WorldData");
		AuroraCore::Graphics::GL::UniformSetMaterial(_Material, _Shader, "u_Material");

		AuroraCore::Graphics::GL::Uniform _ModelUniform;
		AuroraCore::Graphics::GL::Uniform _ViewUniform;
		AuroraCore::Graphics::GL::Uniform _ProjectionUniform;
		AuroraCore::Graphics::GL::Uniform _MVPUniform;

		_ModelUniform.GetLocation(_Shader, "u_Model");
		_ViewUniform.GetLocation(_Shader, "u_View");
		_ProjectionUniform.GetLocation(_Shader, "u_Projection");
		_MVPUniform.GetLocation(_Shader, "u_MVP");

		AuroraCore::Math::Mat4f _Model = AuroraCore::Graphics::GL::GetModelFromWorldData(_WorldData);
		AuroraCore::Math::Mat4f _View = AuroraCore::Graphics::GL::GetViewFromCamera(_Camera);
		AuroraCore::Math::Mat4f _Projection = AuroraCore::Graphics::GL::GetProjectionFromCamera(_Camera, (float)(_Width) / (float)(_Height));
		AuroraCore::Math::Mat4f _MVP = _Projection * _View * _Model;

		_ModelUniform.SetMatrix4fv(_Model.Data());
		_ViewUniform.SetMatrix4fv(_View.Data());
		_ProjectionUniform.SetMatrix4fv(_Projection.Data());
		_MVPUniform.SetMatrix4fv(_MVP.Data());

		_ModelUniform.ReleaseLocation();
		_ViewUniform.ReleaseLocation();
		_ProjectionUniform.ReleaseLocation();
		_MVPUniform.ReleaseLocation();

		AuroraCore::Graphics::GL::glDrawElements(GL_TRIANGLES, (int)(_CPUMesh.IBO.size()), GL_UNSIGNED_INT, nullptr);

		SwapBuffers(GetDC(_Wnd.GetHandle()));

		_WndData.ContextMutex.unlock();

		std::this_thread::sleep_for(std::chrono::microseconds(1));

		std::chrono::system_clock::time_point _Stop = std::chrono::system_clock::now();

		_DeltaTime = std::chrono::duration<float>(_Stop - _Start).count();
	}

	_WhiteTexture.Destroy();
	_Shader.Destroy();
	_VAO.Destroy();
	_Mesh.IBO.Destroy();
	_Mesh.VBO.Destroy();
	_Wnd.Destroy();
	UnregisterClass(L"WndClass", _hInstance);
	AuroraCore::Graphics::GL::Unload();

	return 0;
}
