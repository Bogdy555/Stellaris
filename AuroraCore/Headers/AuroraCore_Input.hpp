#ifndef AuroraCore_Input_hpp

#define AuroraCore_Input_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Input
	{

		namespace Controller
		{

			struct State
			{
				bool Start = false;
				bool Back = false;

				float XLeft = 0.0f;
				float YLeft = 0.0f;
				bool ThumbLeft = false;

				float XRight = 0.0f;
				float YRight = 0.0f;
				bool ThumbRight = false;

				bool ButtonX = false;
				bool ButtonY = false;
				bool ButtonA = false;
				bool ButtonB = false;

				bool DPadLeft = false;
				bool DPadRight = false;
				bool DPadUp = false;
				bool DPadDown = false;

				bool ShoulderLeft = false;
				float TriggerLeft = 0.0f;

				bool ShoulderRight = false;
				float TriggerRight = 0.0f;
			};

			bool GetState(const uint32_t _Id, State& _State, const bool _DeadZone = true, const bool _Threshold = true);
			void CleanState(State& _State);
			bool SetRumble(const uint32_t _Id, const float _Left, const float _Right);

		}

	}

}



#endif
