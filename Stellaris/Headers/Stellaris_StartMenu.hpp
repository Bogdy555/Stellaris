#ifndef Stellaris_StartMenu_hpp

#define Stellaris_StartMenu_hpp



#include "Stellaris.hpp"



namespace Stellaris
{

	namespace RunTime
	{

		class StartMenu : public AuroraCore::RunTime::Menu
		{

		public:

			StartMenu();
			StartMenu(const StartMenu& _Other) = delete;
			StartMenu(StartMenu&& _Other) noexcept = delete;
			~StartMenu();

			const uint64_t GetType() const override;

			StartMenu& operator= (const StartMenu& _Other) = delete;
			StartMenu& operator= (StartMenu&& _Other) noexcept = delete;

		private:

			bool Keys[2][256];
			AuroraCore::Input::Controller::State ControllerStates[2];

			size_t HighScore;

			void Setup() override;
			void Update() override;
			void Stop() override;

			void Input();
			void DeleteInput();
			void Engine();
			void FrameBuild();

		};

	}

}



#endif
