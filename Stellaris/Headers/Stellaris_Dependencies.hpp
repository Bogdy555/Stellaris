#ifndef Stellaris_Dependencies_hpp

#define Stellaris_Dependencies_hpp



#pragma comment(lib, "AuroraCore.lib")



#include <AuroraCore.hpp>



#include "Stellaris_Macros.hpp"



namespace Stellaris
{

	namespace Window
	{

		struct Data;

	}

	namespace RunTime
	{

		class Application;

		enum MenuTypes : const uint64_t
		{
			_PlayMenu = 1,
			_StartMenu = 2,
			_RestartMenu = 3
		};

		class PlayMenu;

		class StartMenu;

		class RestartMenu;

	}

}



#include "Stellaris_Templates.hpp"



#endif
