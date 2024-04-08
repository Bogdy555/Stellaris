#include "..\Headers\AuroraCore.hpp"



static TIMECAPS TimeCaps = { 0 };
static bool Initialized = false;



bool AuroraCore::Time::Init()
{
	if (Initialized == true)
	{
		return true;
	}

	if (timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS)) != MMSYSERR_NOERROR)
	{
		return false;
	}

	if (timeBeginPeriod(TimeCaps.wPeriodMin) != TIMERR_NOERROR)
	{
		return false;
	}

	Initialized = true;

	return true;
}

void AuroraCore::Time::Stop()
{
	if (!Initialized)
	{
		return;
	}

	timeEndPeriod(TimeCaps.wPeriodMin);

	Initialized = false;
	TimeCaps = { 0 };
}



AuroraCore::Time::Timer::Timer() : Begin(std::chrono::system_clock::now()), End()
{
	End = Begin;
}

AuroraCore::Time::Timer::Timer(const Timer& _Other) : Begin(_Other.Begin), End(_Other.End)
{

}

AuroraCore::Time::Timer::Timer(Timer&& _Other) noexcept : Begin(std::move(_Other.Begin)), End(std::move(_Other.End))
{

}

AuroraCore::Time::Timer::~Timer()
{

}

void AuroraCore::Time::Timer::Start()
{
	Begin = std::chrono::system_clock::now();
	End = Begin;
}

void AuroraCore::Time::Timer::Stop()
{
	End = std::chrono::system_clock::now();
}

void AuroraCore::Time::Timer::Reset()
{
	Begin = std::chrono::system_clock::now();
	End = Begin;
}

AuroraCore::Time::Timer::operator const float() const
{
	return std::chrono::duration<float>(End - Begin).count();
}

AuroraCore::Time::Timer& AuroraCore::Time::Timer::operator= (const Timer& _Other)
{
	Begin = _Other.Begin;
	End = _Other.End;

	return *this;
}

AuroraCore::Time::Timer& AuroraCore::Time::Timer::operator= (Timer&& _Other) noexcept
{
	Begin = std::move(_Other.Begin);
	End = std::move(_Other.End);

	return *this;
}
