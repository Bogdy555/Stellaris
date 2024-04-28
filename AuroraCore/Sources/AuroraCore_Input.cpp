#include "..\Headers\AuroraCore.hpp"



bool AuroraCore::Input::Controller::GetState(const uint32_t _Id, State& _State, const bool _DeadZone, const bool _Threshold)
{
	XINPUT_STATE _XInputState = { 0 };

	if (XInputGetState(_Id, &_XInputState) != ERROR_SUCCESS)
	{
		CleanState(_State);
		return false;
	}

	if (_XInputState.Gamepad.sThumbLX == -32768)
	{
		_XInputState.Gamepad.sThumbLX = -32767;
	}

	if (_XInputState.Gamepad.sThumbLY == -32768)
	{
		_XInputState.Gamepad.sThumbLY = -32767;
	}

	if (_XInputState.Gamepad.sThumbRX == -32768)
	{
		_XInputState.Gamepad.sThumbRX = -32767;
	}

	if (_XInputState.Gamepad.sThumbRY == -32768)
	{
		_XInputState.Gamepad.sThumbRY = -32767;
	}

	_State.Start = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
	_State.Back = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0;

	_State.XLeft = (float)(_XInputState.Gamepad.sThumbLX) / 32767.0f;
	_State.YLeft = (float)(_XInputState.Gamepad.sThumbLY) / 32767.0f;
	_State.ThumbLeft = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;

	_State.XRight = (float)(_XInputState.Gamepad.sThumbRX) / 32767.0f;
	_State.YRight = (float)(_XInputState.Gamepad.sThumbRY) / 32767.0f;
	_State.ThumbRight = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;

	_State.ButtonX = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0;
	_State.ButtonY = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0;
	_State.ButtonA = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0;
	_State.ButtonB = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0;

	_State.DPadLeft = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
	_State.DPadRight = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
	_State.DPadUp = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
	_State.DPadDown = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;

	_State.ShoulderLeft = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
	_State.TriggerLeft = (float)(_XInputState.Gamepad.bLeftTrigger) / 255.0f;

	_State.ShoulderRight = (_XInputState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
	_State.TriggerRight = (float)(_XInputState.Gamepad.bRightTrigger) / 255.0f;

	if (_DeadZone)
	{
		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbLX && _XInputState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			_State.XLeft = 0.0f;
		}

		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbLY && _XInputState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			_State.YLeft = 0.0f;
		}

		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbRX && _XInputState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			_State.XRight = 0.0f;
		}

		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < _XInputState.Gamepad.sThumbRY && _XInputState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			_State.YRight = 0.0f;
		}
	}

	if (_Threshold)
	{
		if (_XInputState.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			_State.TriggerLeft = 0.0f;
		}

		if (_XInputState.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			_State.TriggerRight = 0.0f;
		}
	}

	return true;
}

void AuroraCore::Input::Controller::CleanState(State& _State)
{
	_State.Start = false;
	_State.Back = false;

	_State.XLeft = 0.0f;
	_State.YLeft = 0.0f;
	_State.ThumbLeft = false;

	_State.XRight = 0.0f;
	_State.YRight = 0.0f;
	_State.ThumbRight = false;

	_State.ButtonX = false;
	_State.ButtonY = false;
	_State.ButtonA = false;
	_State.ButtonB = false;

	_State.DPadLeft = false;
	_State.DPadRight = false;
	_State.DPadUp = false;
	_State.DPadDown = false;

	_State.ShoulderLeft = false;
	_State.TriggerLeft = 0.0f;

	_State.ShoulderRight = false;
	_State.TriggerRight = 0.0f;
}

bool AuroraCore::Input::Controller::SetRumble(const uint32_t _Id, const float _Left, const float _Right)
{
	XINPUT_VIBRATION _Vibration = { 0 };

	_Vibration.wLeftMotorSpeed = (uint16_t)(Math::Clamp(_Left, 0.0f, 1.0f) * (float)(MAXUINT16));
	_Vibration.wRightMotorSpeed = (uint16_t)(Math::Clamp(_Right, 0.0f, 1.0f) * (float)(MAXUINT16));

	return XInputSetState(_Id, &_Vibration) == ERROR_SUCCESS;
}
