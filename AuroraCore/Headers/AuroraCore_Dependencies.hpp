#ifndef AuroraCore_Dependencies_hpp

#define AuroraCore_Dependencies_hpp



#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Dsound.lib")
#pragma comment(lib, "dxguid.lib")



#include "AuroraCore_WinTargetVer.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <dsound.h>
#include <mmdeviceapi.h>

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

	namespace RunTime
	{



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
