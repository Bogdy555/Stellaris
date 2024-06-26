#ifndef AuroraCore_Dependencies_hpp

#define AuroraCore_Dependencies_hpp



#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "Xinput9_1_0.lib")
#pragma comment(lib, "Ws2_32.lib")



#include "AuroraCore_WinTargetVer.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <dsound.h>
#include <mmdeviceapi.h>
#include <Xinput.h>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>



#include "AuroraCore_Macros.hpp"



namespace AuroraCore
{

	enum States : const size_t
	{
		_Previous = 0,
		_Current = 1
	};

	namespace Time
	{

		class Timer;

	}

	namespace Math
	{

		enum Axes : const size_t;

		class Vec2f;

		class Vec3f;

		class Vec4f;

		class Mat2f;

		class Mat3f;

		class Mat4f;

	}

	struct Asset;

	class AssetManager;

	namespace RunTime
	{

		class Application;

		enum MenuTypes : const uint64_t;

		class Menu;

	}

	namespace Sound
	{

		struct CPUBuffer;

		struct Device;

		class Context;

		class Buffer;

		class Buffer3D;

		class Source;

		class Source3D;

	}

	namespace Graphics
	{

		namespace Assets
		{

			class Image;

		}

		namespace GL
		{

			class Context;

			struct VertexData;

			typedef std::vector<VertexData> VertexBufferCPUCash;

			class VertexBuffer;

			typedef std::vector<unsigned int> IndexBufferCPUCash;

			class IndexBuffer;

			struct MeshCPUCash;

			struct Mesh;

			class VertexAttribArray;

			class Shader;

			class Uniform;

			class Texture2D;

			struct CameraStruct;

			struct MeshWorldDataStruct;

			struct MaterialStruct;

		}

	}

	namespace Networking
	{

		class EndPoint;

	}

	namespace Input
	{

		namespace Controller
		{

			struct State;

		}

	}

	namespace Physics
	{

		struct AABB;

		struct HitBox;

		class Entity;

		class DynamicEntity;

		class Scene;

	}

	class Window;

}



#include "AuroraCore_Templates.hpp"



#endif
