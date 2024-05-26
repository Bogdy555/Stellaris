#ifndef Stellaris_Application_hpp

#define Stellaris_Application_hpp



#include "Stellaris.hpp"



namespace Stellaris
{

	namespace RunTime
	{
		
		class Application : public AuroraCore::RunTime::Application
		{

		public:

			Application(const Application& _Other) = delete;
			Application(Application&& _Other) noexcept = delete;
			~Application();

			AuroraCore::Window& GetMainWindow();
			const AuroraCore::Window& GetMainWindow() const;

			Window::Data& GetMainWindowData();
			const Window::Data& GetMainWindowData() const;

			void UpdateFullScreen();

			AuroraCore::AssetManager& GetAssets();
			const AuroraCore::AssetManager& GetAssets() const;

			static Application* GetInstance();

			void RenderText(const char* _Text, const float& _AspectRatio, const float& _Fov, const AuroraCore::Graphics::GL::MeshWorldDataStruct& _WorldData, const int& _TextureAlbedo, const AuroraCore::Math::Vec4f& _Color, const AuroraCore::Graphics::GL::Shader& _Shader);
			void RenderSprite(const float _AspectRatio, const AuroraCore::Graphics::GL::CameraStruct& _Camera, const AuroraCore::Graphics::GL::MeshWorldDataStruct& _WorldData, const AuroraCore::Graphics::GL::MaterialStruct& _Material, const AuroraCore::Graphics::GL::Shader& _Shader);

			void PlayCollectSound();
			void UpdateSound();
			void UpdateMute();

			void SetScore(const size_t _Score);
			const size_t GetScore() const;

			void SetHighScore(const size_t _Score);
			const size_t GetHighScore() const;

			void operator= (const Application& _Other) = delete;
			void operator= (Application&& _Other) noexcept = delete;

		private:

			Application();

			AuroraCore::Window MainWindow;
			Window::Data MainWindowData;
			std::mutex PlacementMutex;
			std::mutex RectMutex;
			std::mutex FullScreenMutex;
			std::mutex CloseMutex;
			std::mutex InputMutex;
			std::mutex MinSizeMutex;
			std::mutex ContextMutex;

			AuroraCore::Graphics::GL::Context Context;

			AuroraCore::AssetManager Assets;

			AuroraCore::Sound::Context SoundContext;
			std::wstring CurrentDeviceDriver;
			AuroraCore::Sound::Buffer BackgroundSound;
			AuroraCore::Sound::Buffer CollectSound;
			std::vector<AuroraCore::Sound::Source*> SoundSources;

			size_t Score;

			bool Volume;

			bool InitMainWindow();
			void CleanUpMainWindow();

			bool InitAssets();
			void CleanUpAssets();

			bool InitSound();
			void CleanUpSound();

			void Setup() override;
			void Update() override;
			void Stop() override;

		};

	}

}



#endif
