#ifndef AuroraCore_Window_hpp

#define AuroraCore_Window_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	class Window
	{

	public:

		Window();
		Window(const Window& _Other) = delete;
		Window(Window&& _Other) noexcept = delete;
		~Window();

		bool Create(const DWORD _ExStyle, const LPCWSTR _ClassName, const LPCWSTR _WindowName, const DWORD _Style, const int _X, const int _Y, const int _Width, const int _Height, const HWND _HandleParent, const HMENU _HandleMenu, const HINSTANCE _HandleInstance, LPVOID _Param, const HACCEL _HandleAccel, bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData);
		void Destroy();
		bool Show(const int _ShowCmd) const;
		bool UpdateContent() const;

		const bool CheckOn() const;
		const HWND GetHandle() const;
		void* GetUserData();
		const void* GetUserData() const;
		const bool GetClientSize(size_t& _Width, size_t& _Height) const;
		const bool GetWindowSize(size_t& _Width, size_t& _Height) const;
		const uint64_t GetRefreshRate() const;

		operator const HWND() const;

		const Window& operator= (const Window& _Other) = delete;
		const Window& operator= (Window&& _Other) noexcept = delete;

		static Window* GetWindowPtr(const HWND _Handle);

	private:

		static void WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const DWORD _ExStyle, const LPCWSTR _ClassName, const LPCWSTR _WindowName, const DWORD _Style, const int _X, const int _Y, const int _Width, const int _Height, const HWND _HandleParent, const HMENU _HandleMenu, const HINSTANCE _HandleInstance, LPVOID _Param, const HACCEL _HandleAccel, bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData);

		static Window* LastWnd;
		static std::mutex LastWndMutex;

		HWND Handle;
		std::thread WndThread;
		void* UserData;

	};

}



#endif
