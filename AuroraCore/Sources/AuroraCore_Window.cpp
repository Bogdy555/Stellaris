#include "..\Headers\AuroraCore.hpp"



AuroraCore::Window* AuroraCore::Window::LastWnd = nullptr;
std::mutex AuroraCore::Window::LastWndMutex;



AuroraCore::Window::Window() : Handle(NULL), WndThread(), UserData(nullptr)
{

}

AuroraCore::Window::~Window()
{
	AURORA_CORE_ASSERT_MSG(Handle == NULL, AURORA_CORE_STRING_PREFIX("A window was not destroyed!"));
}

// Spawneaza thread ul unde va rula coada de mesaje a ferestrei grafice

bool AuroraCore::Window::Create(const DWORD _ExStyle, const LPCWSTR _ClassName, const LPCWSTR _WindowName, const DWORD _Style, const int _X, const int _Y, const int _Width, const int _Height, const HWND _HandleParent, const HMENU _HandleMenu, const HINSTANCE _HandleInstance, LPVOID _Param, const HACCEL _HandleAccel, bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData)
{
	if (Handle)
	{
		AURORA_CORE_DEBUG_BREAK_MSG(AURORA_CORE_STRING_PREFIX("Can not create a window before destroying the old one!"));

		if (_HandleMenu)
		{
			DestroyMenu(_HandleMenu);
		}

		if (_HandleAccel)
		{
			DestroyAcceleratorTable(_HandleAccel);
		}

		return false;
	}

	bool _Done = false;
	bool _Fail = false;

	WndThread = std::move(std::thread(WndThreadFnc, std::ref(_Done), std::ref(_Fail), this, _ExStyle, _ClassName, _WindowName, _Style, _X, _Y, _Width, _Height, _HandleParent, _HandleMenu, _HandleInstance, _Param, _HandleAccel, _ThreadInitFnc, _ThreadCleanUpFnc, _WndInitFnc, _WndCleanUpFnc, _UserData));

	// Asteapta sa vezi daca thread ul a reusit sa creeze sau nu fereastra

	while (!_Done)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	if (_Fail)
	{
		WndThread.join();
		return false;
	}

	return true;
}

void AuroraCore::Window::Destroy()
{
	if (!Handle)
	{
		return;
	}

	PostMessage(Handle, WM_QUIT, 0, 0);
	WndThread.join(); // IMPORTANT, NU UITA SA ASTEPTI DUPA THREAD UL FERESTREI
}

// Functie async pentru ca ruleaza pe alt thread

bool AuroraCore::Window::Show(const int _ShowCmd) const
{
	if (!Handle)
	{
		return false;
	}

	return ShowWindowAsync(Handle, _ShowCmd) != 0;
}

bool AuroraCore::Window::UpdateContent() const
{
	if (!Handle)
	{
		return false;
	}

	if (!InvalidateRect(Handle, nullptr, false))
	{
		return false;
	}

	return UpdateWindow(Handle);
}

const bool AuroraCore::Window::CheckOn() const
{
	return Handle != NULL;
}

const HWND AuroraCore::Window::GetHandle() const
{
	return Handle;
}

void* AuroraCore::Window::GetUserData()
{
	return UserData;
}

const void* AuroraCore::Window::GetUserData() const
{
	return UserData;
}

// Client size e pentru regiunea pe care se deseneaza

const bool AuroraCore::Window::GetClientSize(size_t& _Width, size_t& _Height) const
{
	if (!Handle)
	{
		return false;
	}

	RECT _ClientRect = { 0 };

	if (!GetClientRect(Handle, &_ClientRect))
	{
		return false;
	}

	_Width = (size_t)(_ClientRect.right) - (size_t)(_ClientRect.left);
	_Height = (size_t)(_ClientRect.bottom) - (size_t)(_ClientRect.top);

	return true;
}

const bool AuroraCore::Window::GetWindowSize(size_t& _Width, size_t& _Height) const
{
	if (!Handle)
	{
		return false;
	}

	RECT _WindowRect = { 0 };

	if (!GetWindowRect(Handle, &_WindowRect))
	{
		return false;
	}

	_Width = (size_t)(_WindowRect.right) - (size_t)(_WindowRect.left);
	_Height = (size_t)(_WindowRect.bottom) - (size_t)(_WindowRect.top);

	return true;
}

// Se adapteaza in functie de monitorul pe care se aflta fereastra

const uint64_t AuroraCore::Window::GetRefreshRate() const
{
	if (!Handle)
	{
		return 0;
	}

	// Obtine monitorul

	HMONITOR _hMonitor = MonitorFromWindow(Handle, MONITOR_DEFAULTTOPRIMARY);

	if (!_hMonitor)
	{
		return 0;
	}

	MONITORINFOEX _MonitorInfo = { 0 };

	_MonitorInfo.cbSize = sizeof(MONITORINFOEX);

	// Obtine date despre monitor

	if (!GetMonitorInfo(_hMonitor, &_MonitorInfo))
	{
		return 0;
	}

	DEVMODE _DevMode = { 0 };

	_DevMode.dmSize = sizeof(DEVMODE);

	// Obtine alte date despre monitor

	if (!EnumDisplaySettingsEx(_MonitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &_DevMode, 0))
	{
		return 0;
	}

	return (uint64_t)(_DevMode.dmDisplayFrequency);
}

AuroraCore::Window::operator const HWND() const
{
	return Handle;
}

AuroraCore::Window* AuroraCore::Window::GetWindowPtr(const HWND _Handle)
{
	if (!_Handle)
	{
		return nullptr;
	}

	Window* _WndPtr = (Window*)(GetWindowLongPtr(_Handle, GWLP_USERDATA));

	if (!_WndPtr)
	{
		// Daca fereastra inca nu are setat user data la pointer ul corect inseamna ca suntem in mijlocul apelului CreateWindowEx si folosim membrul static al clasei Window
		return LastWnd;
	}

	return _WndPtr;
}

// IMPORTANT: Modifica done si fail daca ai reusit/nu ai reusit sa creezi fereastra. Asigura te ca thread ul principal nu ramane blocat pentru ca ai uitat sa il notifici

void AuroraCore::Window::WndThreadFnc(bool& _Done, bool& _Fail, Window* _Wnd, const DWORD _ExStyle, const LPCWSTR _ClassName, const LPCWSTR _WindowName, const DWORD _Style, const int _X, const int _Y, const int _Width, const int _Height, const HWND _HandleParent, const HMENU _HandleMenu, const HINSTANCE _HandleInstance, LPVOID _Param, const HACCEL _HandleAccel, bool (*_ThreadInitFnc)(void* _UserData), void (*_ThreadCleanUpFnc)(void* _UserData), bool (*_WndInitFnc)(Window* _Wnd), void (*_WndCleanUpFnc)(Window* _Wnd), void* _UserData)
{
	if (_ThreadInitFnc)
	{
		if (!_ThreadInitFnc(_UserData))
		{
			if (_HandleMenu)
			{
				DestroyMenu(_HandleMenu);
			}

			if (_HandleAccel)
			{
				DestroyAcceleratorTable(_HandleAccel);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	_Wnd->UserData = _UserData;

	LastWndMutex.lock();

	LastWnd = _Wnd;

	_Wnd->Handle = CreateWindowEx(_ExStyle, _ClassName, _WindowName, _Style, _X, _Y, _Width, _Height, _HandleParent, _HandleMenu, _HandleInstance, _Param);

	LastWnd = nullptr;

	LastWndMutex.unlock();

	if (!_Wnd->Handle)
	{
		_Wnd->UserData = nullptr;

		if (_ThreadCleanUpFnc)
		{
			_ThreadCleanUpFnc(_UserData);
		}

		if (_HandleMenu)
		{
			DestroyMenu(_HandleMenu);
		}

		if (_HandleAccel)
		{
			DestroyAcceleratorTable(_HandleAccel);
		}

		_Fail = true;
		_Done = true;

		return;
	}

	SetLastError(0);

	if (!SetWindowLongPtr(_Wnd->Handle, GWLP_USERDATA, (LONG_PTR)(_Wnd)))
	{
		// Cel mai ciudat error checking. Merci Microsoft...

		if (GetLastError())
		{
			DestroyWindow(_Wnd->Handle);
			_Wnd->Handle = NULL;
			_Wnd->UserData = nullptr;

			if (_ThreadCleanUpFnc)
			{
				_ThreadCleanUpFnc(_UserData);
			}

			if (_HandleAccel)
			{
				DestroyAcceleratorTable(_HandleAccel);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	if (_WndInitFnc)
	{
		if (!_WndInitFnc(_Wnd))
		{
			DestroyWindow(_Wnd->Handle);
			_Wnd->Handle = NULL;
			_Wnd->UserData = nullptr;

			if (_ThreadCleanUpFnc)
			{
				_ThreadCleanUpFnc(_UserData);
			}

			if (_HandleAccel)
			{
				DestroyAcceleratorTable(_HandleAccel);
			}

			_Fail = true;
			_Done = true;

			return;
		}
	}

	MSG _Msg = { 0 };

	_Fail = false;
	_Done = true;

	while (GetMessage(&_Msg, NULL, 0, 0) > 0)
	{
		if (_HandleAccel)
		{
			// Pentru shortcut uri
			if (TranslateAccelerator(_Wnd->Handle, _HandleAccel, &_Msg))
			{
				continue;
			}

			if (GetLastError())
			{
				break;
			}
		}

		TranslateMessage(&_Msg);
		DispatchMessage(&_Msg);
	}

	if (_WndCleanUpFnc)
	{
		_WndCleanUpFnc(_Wnd);
	}

	DestroyWindow(_Wnd->Handle);
	_Wnd->Handle = NULL;
	_Wnd->UserData = nullptr;

	if (_ThreadCleanUpFnc)
	{
		_ThreadCleanUpFnc(_UserData);
	}

	if (_HandleAccel)
	{
		DestroyAcceleratorTable(_HandleAccel);
	}
}
