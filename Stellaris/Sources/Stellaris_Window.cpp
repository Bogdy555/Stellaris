#include "..\Headers\Stellaris.hpp"



Stellaris::Window::Data::Data() : PlacementMutex(nullptr), Placement({ 0 }), RectMutex(nullptr), Rect({ 0 }), FullScreenMutex(nullptr), FullScreen(false), CloseMutex(nullptr), Close(false), InputMutex(nullptr), Focus(false), Keys(), MinSizeMutex(nullptr), MinWidth(700), MinHeight(400), ContextMutex(nullptr), Context(nullptr)
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = false;
	}
}

Stellaris::Window::Data::Data(const Data& _Other) : PlacementMutex(_Other.PlacementMutex), Placement(_Other.Placement), RectMutex(_Other.RectMutex), Rect(_Other.Rect), FullScreenMutex(_Other.FullScreenMutex), FullScreen(_Other.FullScreen), CloseMutex(_Other.CloseMutex), Close(_Other.Close), InputMutex(_Other.InputMutex), Focus(_Other.Focus), Keys(), MinSizeMutex(_Other.MinSizeMutex), MinWidth(_Other.MinWidth), MinHeight(_Other.MinHeight), ContextMutex(_Other.ContextMutex), Context(_Other.Context)
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = _Other.Keys[_Index];
	}
}

Stellaris::Window::Data::Data(Data&& _Other) noexcept : PlacementMutex(_Other.PlacementMutex), Placement(_Other.Placement), RectMutex(_Other.RectMutex), Rect(_Other.Rect), FullScreenMutex(_Other.FullScreenMutex), FullScreen(_Other.FullScreen), CloseMutex(_Other.CloseMutex), Close(_Other.Close), InputMutex(_Other.InputMutex), Focus(_Other.Focus), Keys(), MinSizeMutex(_Other.MinSizeMutex), MinWidth(_Other.MinWidth), MinHeight(_Other.MinHeight), ContextMutex(_Other.ContextMutex), Context(_Other.Context)
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = _Other.Keys[_Index];
		_Other.Keys[_Index] = false;
	}

	_Other.PlacementMutex = nullptr;
	_Other.Placement = { 0 };
	_Other.RectMutex = nullptr;
	_Other.Rect = { 0 };
	_Other.FullScreenMutex = nullptr;
	_Other.FullScreen = false;
	_Other.CloseMutex = nullptr;
	_Other.Close = false;
	_Other.InputMutex = nullptr;
	_Other.Focus = false;
	_Other.MinSizeMutex = nullptr;
	_Other.MinWidth = 700;
	_Other.MinHeight = 400;
	_Other.ContextMutex = nullptr;
	_Other.Context = nullptr;
}

Stellaris::Window::Data::~Data()
{

}

void Stellaris::Window::Data::operator= (const Data& _Other)
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = _Other.Keys[_Index];
	}

	PlacementMutex = _Other.PlacementMutex;
	Placement = _Other.Placement;
	RectMutex = _Other.RectMutex;
	Rect = _Other.Rect;
	FullScreenMutex = _Other.FullScreenMutex;
	FullScreen = _Other.FullScreen;
	CloseMutex = _Other.CloseMutex;
	Close = _Other.Close;
	InputMutex = _Other.InputMutex;
	Focus = _Other.Focus;
	MinSizeMutex = _Other.MinSizeMutex;
	MinWidth = _Other.MinWidth;
	MinHeight = _Other.MinHeight;
	ContextMutex = _Other.ContextMutex;
	Context = _Other.Context;
}

void Stellaris::Window::Data::operator= (Data&& _Other) noexcept
{
	for (size_t _Index = 0; _Index < 256; _Index++)
	{
		Keys[_Index] = _Other.Keys[_Index];
		_Other.Keys[_Index] = false;
	}

	PlacementMutex = _Other.PlacementMutex;
	Placement = _Other.Placement;
	RectMutex = _Other.RectMutex;
	Rect = _Other.Rect;
	FullScreenMutex = _Other.FullScreenMutex;
	FullScreen = _Other.FullScreen;
	CloseMutex = _Other.CloseMutex;
	Close = _Other.Close;
	InputMutex = _Other.InputMutex;
	Focus = _Other.Focus;
	MinSizeMutex = _Other.MinSizeMutex;
	MinWidth = _Other.MinWidth;
	MinHeight = _Other.MinHeight;
	ContextMutex = _Other.ContextMutex;
	Context = _Other.Context;

	_Other.PlacementMutex = nullptr;
	_Other.Placement = { 0 };
	_Other.RectMutex = nullptr;
	_Other.Rect = { 0 };
	_Other.FullScreenMutex = nullptr;
	_Other.FullScreen = false;
	_Other.CloseMutex = nullptr;
	_Other.Close = false;
	_Other.InputMutex = nullptr;
	_Other.Focus = false;
	_Other.MinSizeMutex = nullptr;
	_Other.MinWidth = 700;
	_Other.MinHeight = 400;
	_Other.ContextMutex = nullptr;
	_Other.Context = nullptr;
}

bool Stellaris::Window::InitWindowThread(void* _UserData)
{
	return true;
}

void Stellaris::Window::CleanUpWindowThread(void* _UserData)
{

}

bool Stellaris::Window::InitWindow(AuroraCore::Window* _Wnd)
{
	Data& _WindowData = *(Data*)(_Wnd->GetUserData());

	if (!_WindowData.Context->Create(*_Wnd))
	{
		return false;
	}

	return true;
}

void Stellaris::Window::CleanUpWindow(AuroraCore::Window* _Wnd)
{
	Data& _WindowData = *(Data*)(_Wnd->GetUserData());

	_WindowData.Context->Destroy();
}

LRESULT CALLBACK Stellaris::Window::WindowProcedure(_In_ HWND _hWnd, _In_ UINT _Msg, _In_ WPARAM _wParam, _In_ LPARAM _lParam)
{
	AuroraCore::Window* _Wnd = AuroraCore::Window::GetWindowPtr(_hWnd);

	AURORA_CORE_ASSERT(_Wnd != nullptr);

	Data* _WndData = (Data*)(_Wnd->GetUserData());

	AURORA_CORE_ASSERT(_WndData != nullptr);

	switch (_Msg)
	{
	case WM_CLOSE:
	{
		_WndData->CloseMutex->lock();

		_WndData->Close = true;

		_WndData->CloseMutex->unlock();

		break;
	}
	case WM_KEYDOWN:
	{
		_WndData->InputMutex->lock();

		_WndData->Keys[_wParam] = true;

		_WndData->InputMutex->unlock();

		break;
	}
	case WM_KEYUP:
	{
		_WndData->InputMutex->lock();

		_WndData->Keys[_wParam] = false;

		_WndData->InputMutex->unlock();

		break;
	}
	case WM_SETFOCUS:
	{
		_WndData->InputMutex->lock();

		_WndData->Focus = true;

		for (size_t _Index = 0; _Index < 256; _Index++)
		{
			_WndData->Keys[_Index] = false;
		}

		_WndData->InputMutex->unlock();

		break;
	}
	case WM_KILLFOCUS:
	{
		_WndData->InputMutex->lock();

		_WndData->Focus = false;

		for (size_t _Index = 0; _Index < 256; _Index++)
		{
			_WndData->Keys[_Index] = false;
		}

		_WndData->InputMutex->unlock();

		break;
	}
	case WM_ERASEBKGND:
	{
		break;
	}
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO _MinMaxInfo = (LPMINMAXINFO)(_lParam);

		_WndData->MinSizeMutex->lock();

		_MinMaxInfo->ptMinTrackSize.x = _WndData->MinWidth;
		_MinMaxInfo->ptMinTrackSize.y = _WndData->MinHeight;

		_WndData->MinSizeMutex->unlock();

		break;
	}
	default:
	{
		return DefWindowProc(_hWnd, _Msg, _wParam, _lParam);
	}
	}

	return 0;
}
