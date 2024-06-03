#ifndef AuroraCore_AssetManager_hpp

#define AuroraCore_AssetManager_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	struct Asset
	{
		void* Data = nullptr;
		const wchar_t* Name = nullptr;
	};

	// NU ARE OWNERSHIP ASUPRA RESURSELOR, E DOAR O METODA DE A ACCESA DATE
	// Loading si clean up facute in user code, nu engine code!
	class AssetManager
	{

	public:

		AssetManager();
		AssetManager(const AssetManager& _Other) = delete;
		AssetManager(AssetManager&& _Other) noexcept;
		~AssetManager();

		// Sunt permise referinte catre aceasi data dar cu nume diferit
		bool AddAsset(void* _Data, const wchar_t* _Name);

		void RemoveAsset(const wchar_t* _Name);
		void RemoveAsset(const size_t _Index);
		void RemoveAllAssets();

		const size_t GetAssetsCount() const;
		const size_t GetAssetIndex(const wchar_t* _Name) const;

		void* GetAssetData(const wchar_t* _Name);
		const void* GetAssetData(const wchar_t* _Name) const;

		Asset& operator[] (const size_t _Index);
		const Asset& operator[] (const size_t _Index) const;

		void operator= (const AssetManager& _Other) = delete;
		void operator= (AssetManager&& _Other) noexcept;

	private:

		std::vector<Asset> Assets;

	};

}



#endif
