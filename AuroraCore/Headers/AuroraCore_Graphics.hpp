#ifndef AuroraCore_Graphics_hpp

#define AuroraCore_Graphics_hpp



#include <cstdint>
#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Graphics
	{
		namespace Assets
		{
			class Image
			{
			public:
				Image();
				Image(const Image& _Other) = delete;
				Image(Image&& _Other) noexcept;
				~Image();

				Image& operator= (const Image& _Other) = delete;
				Image& operator= (Image&& _Other) noexcept;

				bool Create(const size_t _Width, const size_t _Height, const size_t _ChannelsCount);
				bool Load(const wchar_t* _Path);
				const bool Save(const wchar_t* _Path) const;
				void Destroy();

				const size_t GetWidth() const;
				const size_t GetHeight() const;
				const size_t GetChannelsCount() const;
				uint8_t* GetData();
				const uint8_t* GetData() const;

				uint8_t& operator[] (const size_t _Index);
				const uint8_t& operator[] (const size_t _Index) const;

			private:
				size_t Width;
				size_t Height;
				size_t ChannelsCount;
				uint8_t* Data;
			};
		}

	}

}



#endif
