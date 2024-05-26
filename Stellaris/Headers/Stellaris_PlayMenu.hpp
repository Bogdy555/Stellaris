#ifndef Stellaris_PlayMenu_hpp

#define Stellaris_PlayMenu_hpp



#include "Stellaris.hpp"



namespace Stellaris
{

	namespace RunTime
	{

		class PlayMenu : public AuroraCore::RunTime::Menu
		{

		public:

			PlayMenu();
			PlayMenu(const PlayMenu& _Other) = delete;
			PlayMenu(PlayMenu&& _Other) noexcept = delete;
			~PlayMenu();

			const uint64_t GetType() const override;

			void operator= (const PlayMenu& _Other) = delete;
			void operator= (PlayMenu&& _Other) noexcept = delete;

		private:

			bool Keys[2][256];
			AuroraCore::Input::Controller::State ControllerStates[2];

			float AnimationTime;

			std::vector<std::vector<bool>> WorldMatrix;
			AuroraCore::Physics::Entity World;
			AuroraCore::Physics::DynamicEntity Player;
			bool Flying;
			bool LastLeft;
			AuroraCore::Physics::Entity Star;
			std::vector<AuroraCore::Physics::DynamicEntity*> Particles;
			std::vector<float> ParticlesTime;
			bool HitStar;

			float TimeFromStart;

			static PlayMenu* CurrentPlayMenu;
			static const float ParticleLifeTime;
			static const float TotalTime;

			void SetupScene();
			void CleanUpScene();

			void SpawnParticle();
			void UpdateParticles();

			static void PhysicsCallback(AuroraCore::Physics::Entity& _Entity1, AuroraCore::Physics::Entity& _Entity2);

			void GenerateStarPosition();

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
