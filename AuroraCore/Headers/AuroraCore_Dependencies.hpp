#ifndef AuroraCore_Dependencies_hpp

#define AuroraCore_Dependencies_hpp



#pragma comment(lib, "Winmm.lib")



#include "AuroraCore_WinTargetVer.hpp"
#include <Windows.h>

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

		class Buffer;

	}

	namespace Graphics
	{

		namespace GL
		{



		}

	}

	namespace Networking
	{



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
