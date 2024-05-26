#ifndef Stellaris_RestartMenu_hpp

#define Stellaris_RestartMenu_hpp



#include "Stellaris.hpp"



namespace Stellaris
{

	namespace RunTime
	{

		class RestartMenu : public AuroraCore::RunTime::Menu
		{

		public:

			RestartMenu();
			RestartMenu(const RestartMenu& _Other) = delete;
			RestartMenu(RestartMenu&& _Other) noexcept = delete;
			~RestartMenu();

			const uint64_t GetType() const override;

			RestartMenu& operator= (const RestartMenu& _Other) = delete;
			RestartMenu& operator= (RestartMenu&& _Other) noexcept = delete;

		private:

			bool Keys[2][256];
			AuroraCore::Input::Controller::State ControllerStates[2];

			size_t HighScore;
			size_t Score;

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
