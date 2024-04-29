#ifndef AuroraCore_Dependencies_hpp

#define AuroraCore_Dependencies_hpp



#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "opengl32.lib")



#include "AuroraCore_WinTargetVer.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>



#include "AuroraCore_Macros.hpp"



namespace AuroraCore
{

	namespace Time
	{



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

	namespace RunTime
	{



	}

	namespace Sound
	{



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



	}

	namespace Physics
	{



	}

	class Window;

}



#include "AuroraCore_Templates.hpp"



#endif
