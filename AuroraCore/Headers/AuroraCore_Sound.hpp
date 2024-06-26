#ifndef AuroraCore_Sound_hpp

#define AuroraCore_Sound_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Sound
	{

		struct CPUBuffer
		{

			size_t Size = 0;
			uint8_t* Data = nullptr;
			WAVEFORMATEX SoundInfo = { 0 };

			// Helpers pentru menajare
			static float GetTotalTime(const size_t _Size, const WAVEFORMATEX& _SoundInfo);
			static size_t GetSecondIndex(const float _Second, const size_t _Size, const WAVEFORMATEX& _SoundInfo);
			static float GetIndexSecond(const size_t _Index, const size_t _Size, const WAVEFORMATEX& _SoundInfo);

			// Loaders and savers
			static uint8_t* LoadSoundFile(const wchar_t* _Path, size_t& _Size, WAVEFORMATEX& _SoundInfo);
			static uint8_t* LoadSoundResource(const HINSTANCE _InstanceHandle, const uint32_t _ResourceId, size_t& _Size, WAVEFORMATEX& _SoundInfo);
			static bool SaveSoundFile(const wchar_t* _Path, const uint8_t* _Data, const size_t _Size, const WAVEFORMATEX& _SoundInfo);

		};

		struct Device
		{
			LPGUID Id = nullptr;
			std::wstring Name;
			// Foloseste Driver pentru a identifica device changes
			std::wstring Driver;
		};

		extern const std::vector<Device>& Devices;

		// Foloseste pentru menajare de device uri
		bool UpdateDevices();
		void CleanDevices();
		size_t GetDefaultDeviceIndex();

		class Context
		{

		public:

			Context();
			Context(const Context& _Other) = delete;
			Context(Context&& _Other) noexcept;
			~Context();

			bool Create(const size_t _DeviceIndex);
			void Destroy();

			// ATENTIE: NON LINIAR
			bool SetVolume(const float _Volume);
			bool SetPosition(const Math::Vec3f& _Position, const bool _Deferred = true);
			bool SetOrientation(const Math::Vec3f& _Front, const Math::Vec3f& _Up, const bool _Deferred = true);
			bool SetVelocity(const Math::Vec3f& _Velocity, const bool _Deferred = true);

			// ATENTIE: NON LINIAR
			const bool GetVolume(float& _Volume) const;
			const bool GetPosition(Math::Vec3f& _Position) const;
			const bool GetOrientation(Math::Vec3f& _Front, Math::Vec3f& _Up) const;
			const bool GetVelocity(Math::Vec3f& _Velocity) const;

			bool CommitChanges();

			const bool CheckCreated() const;

			Context& operator= (const Context& _Other) = delete;
			Context& operator= (Context&& _Other) noexcept;

		private:

			friend Buffer;
			friend Buffer3D;
			friend Source;
			friend Source3D;

			IDirectSound8* DirectSoundContext;
			IDirectSoundBuffer* PrimaryBuffer;
			IDirectSound3DListener8* Listener;

		};

		// Mono si stereo
		class Buffer
		{

		public:

			Buffer();
			Buffer(const Buffer& _Other) = delete;
			Buffer(Buffer&& _Other) noexcept;
			~Buffer();

			bool Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _SoundInfo, const uint8_t* _Data);
			void Destroy();

			bool Lock(const size_t _Offset, const size_t _Size, uint8_t** _Buff1, size_t& _BuffSize1, uint8_t** _Buff2, size_t& _BuffSize2);
			bool Unlock(uint8_t* _Buff1, const size_t _BuffSize1, uint8_t* _Buff2, const size_t _BuffSize2);

			const bool CheckCreated() const;
			const float GetTotalTime() const;
			const size_t GetSecondIndex(const float _Second) const;
			const float GetIndexSecond(const size_t _Index) const;
			const size_t GetSize() const;
			const WAVEFORMATEX GetSoundInfo() const;

			Buffer& operator= (const Buffer& _Other) = delete;
			Buffer& operator= (Buffer&& _Other) noexcept;

		private:

			friend Source;

			IDirectSoundBuffer* DirectSoundBuffer;
			size_t Size;
			WAVEFORMATEX SoundInfo;

		};

		// Doar mono
		class Buffer3D
		{

		public:

			Buffer3D();
			Buffer3D(const Buffer3D& _Other) = delete;
			Buffer3D(Buffer3D&& _Other) noexcept;
			~Buffer3D();

			bool Create(Context& _Context, const size_t _Size, const WAVEFORMATEX& _SoundInfo, const uint8_t* _Data);
			void Destroy();

			bool Lock(const size_t _Offset, const size_t _Size, uint8_t** _Buff1, size_t& _BuffSize1, uint8_t** _Buff2, size_t& _BuffSize2);
			bool Unlock(uint8_t* _Buff1, const size_t _BuffSize1, uint8_t* _Buff2, const size_t _BuffSize2);

			const bool CheckCreated() const;
			const float GetTotalTime() const;
			const size_t GetSecondIndex(const float _Second) const;
			const float GetIndexSecond(const size_t _Index) const;
			const size_t GetSize() const;
			const WAVEFORMATEX GetSoundInfo() const;

			Buffer3D& operator= (const Buffer3D& _Other) = delete;
			Buffer3D& operator= (Buffer3D&& _Other) noexcept;

		private:

			friend Source3D;

			IDirectSoundBuffer* DirectSoundBuffer;
			size_t Size;
			WAVEFORMATEX SoundInfo;

		};

		// Mono si stereo
		class Source
		{

		public:

			Source();
			Source(const Source& _Other) = delete;
			Source(Source&& _Other) noexcept;
			~Source();

			bool Create(Context& _Context, Buffer& _Buffer);
			void Destroy();

			// ATENTIE: NON LINIAR
			bool SetVolume(const float _Volume);
			bool SetFrequency(const float _Frequency);
			bool SetCurrentPosition(const size_t _CurrentPosition);

			// ATENTIE: NON LINIAR
			const bool GetVolume(float& _Volume) const;
			const bool GetFrequency(float& _Frequency) const;
			const bool GetCurrentPosition(size_t& _CurrentPosition) const;

			bool Play(const bool _Looping);
			bool Stop();
			void UpdatePlayTime();

			const bool CheckCreated() const;
			const bool IsPlaying() const;
			const bool IsLooping() const;
			const float GetTotalTime() const;
			const size_t GetSecondIndex(const float _Second) const;
			const float GetIndexSecond(const size_t _Index) const;
			const float GetPlayTime() const;
			const float GetStartTime() const;
			const size_t GetSize() const;
			const WAVEFORMATEX GetSoundInfo() const;

			Source& operator= (const Source& _Other) = delete;
			Source& operator= (Source&& _Other) noexcept;

		private:

			IDirectSoundBuffer8* DirectSoundBuffer;
			bool Playing;
			bool Looping;
			size_t Size;
			WAVEFORMATEX SoundInfo;
			Time::Timer PlayTime;
			float StartTime;

		};

		// Doar mono
		class Source3D
		{

		public:

			Source3D();
			Source3D(const Source3D& _Other) = delete;
			Source3D(Source3D&& _Other) noexcept;
			~Source3D();

			bool Create(Context& _Context, Buffer3D& _Buffer);
			void Destroy();

			// ATENTIE: NON LINIAR
			bool SetVolume(const float _Volume);
			bool SetFrequency(const float _Frequency);
			bool SetPosition(const Math::Vec3f& _Position, const bool _Deferred = true);
			bool SetVelocity(const Math::Vec3f& _Velocity, const bool _Deferred = true);
			bool SetMinDistance(const float _Distance, const bool _Deferred = true);
			bool SetMaxDistance(const float _Distance, const bool _Deferred = true);
			bool SetConeAngles(const uint32_t _Inside, const uint32_t _Outside, const bool _Deferred = true);
			bool SetConeOrientation(const Math::Vec3f& _Orientation, const bool _Deferred = true);
			bool SetConeOutsideVolume(const float _Volume, const bool _Deferred = true);
			bool SetCurrentPosition(const size_t _CurrentPosition);

			// ATENTIE: NON LINIAR
			const bool GetVolume(float& _Volume) const;
			const bool GetFrequency(float& _Frequency) const;
			const bool GetPosition(Math::Vec3f& _Position) const;
			const bool GetVelocity(Math::Vec3f& _Velocity) const;
			const bool GetMinDistance(float& _Distance) const;
			const bool GetMaxDistance(float& _Distance) const;
			const bool GetConeAngles(uint32_t& _Inside, uint32_t& _Outside) const;
			const bool GetConeOrientation(Math::Vec3f& _Orientation) const;
			const bool GetConeOutsideVolume(float& _Volume) const;
			const bool GetCurrentPosition(size_t& _CurrentPosition) const;

			bool Play(const bool _Looping);
			bool Stop();
			void UpdatePlayTime();

			const bool CheckCreated() const;
			const bool IsPlaying() const;
			const bool IsLooping() const;
			const float GetTotalTime() const;
			const size_t GetSecondIndex(const float _Second) const;
			const float GetIndexSecond(const size_t _Index) const;
			const float GetPlayTime() const;
			const float GetStartTime() const;
			const size_t GetSize() const;
			const WAVEFORMATEX GetSoundInfo() const;

			Source3D& operator= (const Source3D& _Other) = delete;
			Source3D& operator= (Source3D&& _Other) noexcept;

		private:

			IDirectSoundBuffer8* DirectSoundBuffer;
			IDirectSound3DBuffer8* DirectSound3DBuffer;
			bool Playing;
			bool Looping;
			size_t Size;
			WAVEFORMATEX SoundInfo;
			Time::Timer PlayTime;
			float StartTime;

		};

	}

}



#endif
