#ifndef AuroraCore_Networking_hpp

#define AuroraCore_Networking_hpp



#include "AuroraCore.hpp"



namespace AuroraCore
{

	namespace Networking
	{

		extern WSADATA WSAData;

		bool Init();
		void Stop();

		class EndPoint
		{

		public:

			EndPoint();
			EndPoint(const EndPoint& _Other) = delete;
			EndPoint(EndPoint&& _Other) noexcept;
			~EndPoint();

			bool Host(const wchar_t* _Address, const wchar_t* _Port);
			bool GetNextClient(EndPoint& _NextClient, sockaddr* _Address = nullptr);
			bool Connect(const wchar_t* _Address, const wchar_t* _Port);
			void Disconnect();

			bool SendBuff(const uint8_t* _Buff, const size_t _BuffSize);
			bool SendInt8(const int8_t _Value);
			bool SendInt16(const int16_t _Value);
			bool SendInt32(const int32_t _Value);
			bool SendInt64(const int64_t _Value);
			bool SendUInt8(const uint8_t _Value);
			bool SendUInt16(const uint16_t _Value);
			bool SendUInt32(const uint32_t _Value);
			bool SendUInt64(const uint64_t _Value);
			bool SendFloat(const float _Value);
			bool RecvBuff(uint8_t* _Buff, const size_t _BuffSize);
			bool RecvInt8(int8_t& _Value);
			bool RecvInt16(int16_t& _Value);
			bool RecvInt32(int32_t& _Value);
			bool RecvInt64(int64_t& _Value);
			bool RecvUInt8(uint8_t& _Value);
			bool RecvUInt16(uint16_t& _Value);
			bool RecvUInt32(uint32_t& _Value);
			bool RecvUInt64(uint64_t& _Value);
			bool RecvFloat(float& _Value);

			operator const SOCKET() const;

			EndPoint& operator= (const EndPoint& _Other) = delete;
			EndPoint& operator= (EndPoint&& _Other) noexcept;

		private:

			SOCKET Socket;

		};

	}

}



#endif
