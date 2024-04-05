#ifndef AuroraCore_Sound_hpp

#define AuroraCore_Sound_hpp



#include "AuroraCore.hpp"
#include <cstdint>
#include <Windows.h>
#include <fstream>



namespace AuroraCore
{

	namespace Sound
	{

		class Buffer
		{

		public:

			Buffer();
			Buffer(const Buffer& _Other) = delete;
			Buffer(Buffer&& _Other) noexcept;
			~Buffer();

			bool Create(const WAVEFORMATEX& _MetaData, const size_t _Size);
			void Destroy();

			bool LoadFromFile(const wchar_t* _Path);
			bool LoadFromResource(const HINSTANCE _InstanceHandle, const uint16_t _ResourceId);
			const bool SaveToFile(const wchar_t* _Path) const;

			const WAVEFORMATEX GetMetaData() const;
			const size_t GetSize() const;
			uint8_t* GetData();
			const uint8_t* GetData() const;

			uint8_t& operator[] (const size_t _Index);
			const uint8_t& operator[] (const size_t _Index) const;

			Buffer& operator= (const Buffer& _Other) = delete;
			Buffer& operator= (Buffer&& _Other) noexcept;

		private:

			WAVEFORMATEX MetaData;
			size_t Size;
			uint8_t* Data;

		};

	}

}



#endif
