#ifndef AuroraCore_Time_hpp

#define AuroraCore_Time_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Time
	{

		bool Init();
		void Stop();

		class Timer
		{
		public:
			Timer();
			Timer(const Timer& _Other);
			Timer(Timer&& _Other) noexcept;
			~Timer();

			void Start();
			void Stop();
			void Reset();

			operator const float() const;

			Timer& operator= (const Timer& _Other);
			Timer& operator= (Timer&& _Other) noexcept;

		private:
			std::chrono::system_clock::time_point Begin;
			std::chrono::system_clock::time_point End;
		};

	}

}



#endif
