#include "..\Headers\AuroraCore.hpp"



#define AURORA_CORE_LISTEN_MAX 1024



WSADATA AuroraCore::Networking::WSAData = { 0 };



bool AuroraCore::Networking::Init()
{
	return WSAStartup(MAKEWORD(2, 2), &WSAData) == NO_ERROR;
}

void AuroraCore::Networking::Stop()
{
	WSACleanup();
	WSAData = { 0 };
}



AuroraCore::Networking::EndPoint::EndPoint() : Socket(INVALID_SOCKET)
{

}

AuroraCore::Networking::EndPoint::EndPoint(EndPoint&& _Other) noexcept : Socket(_Other.Socket)
{
	_Other.Socket = INVALID_SOCKET;
}

AuroraCore::Networking::EndPoint::~EndPoint()
{
	AURORA_CORE_ASSERT_MSG(Socket == INVALID_SOCKET, AURORA_CORE_STRING_PREFIX("~EndPoint hit before cleanup!"));
}

bool AuroraCore::Networking::EndPoint::Host(const wchar_t* _Address, const wchar_t* _Port)
{
	Disconnect();

	ADDRINFOW* _AddressInfo = nullptr;

	{
		ADDRINFOW _AddressHint = { 0 };

		_AddressHint.ai_family = AF_INET;
		_AddressHint.ai_socktype = SOCK_STREAM;
		_AddressHint.ai_protocol = IPPROTO_TCP;

		if (GetAddrInfoW(_Address, _Port, &_AddressHint, &_AddressInfo) != NO_ERROR)
		{
			return false;
		}
	}

	Socket = socket(_AddressInfo->ai_family, _AddressInfo->ai_socktype, _AddressInfo->ai_protocol);

	if (Socket == INVALID_SOCKET)
	{
		FreeAddrInfoW(_AddressInfo);
		return false;
	}

	if (bind(Socket, _AddressInfo->ai_addr, (int)(_AddressInfo->ai_addrlen)) != NO_ERROR)
	{
		closesocket(Socket);
		Socket = INVALID_SOCKET;
		FreeAddrInfoW(_AddressInfo);
		return false;
	}

	FreeAddrInfoW(_AddressInfo);

	if (listen(Socket, AURORA_CORE_LISTEN_MAX) != NO_ERROR)
	{
		closesocket(Socket);
		Socket = INVALID_SOCKET;
		return false;
	}

	return true;
}

bool AuroraCore::Networking::EndPoint::GetNextClient(EndPoint& _NextClient, sockaddr* _Address)
{
	AURORA_CORE_ASSERT_MSG(_NextClient.Socket == INVALID_SOCKET, AURORA_CORE_STRING_PREFIX("Cleanup the EndPoint befor using it to get the next client!"));

	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	if (_Address == nullptr)
	{
		_NextClient.Socket = accept(Socket, nullptr, nullptr);
	}
	else
	{
		int _AddressLen = sizeof(sockaddr);

		_NextClient.Socket = accept(Socket, _Address, &_AddressLen);
	}

	if (_NextClient.Socket == INVALID_SOCKET)
	{
		Disconnect();
		return false;
	}

	if (listen(Socket, AURORA_CORE_LISTEN_MAX) != NO_ERROR)
	{
		if (_Address)
		{
			*_Address = { 0 };
		}
		_NextClient.Disconnect();
		Disconnect();
		return false;
	}

	return true;
}

bool AuroraCore::Networking::EndPoint::Connect(const wchar_t* _Address, const wchar_t* _Port)
{
	Disconnect();

	ADDRINFOW* _AddressInfo = nullptr;

	{
		ADDRINFOW _AddressHint = { 0 };

		_AddressHint.ai_family = AF_INET;
		_AddressHint.ai_socktype = SOCK_STREAM;
		_AddressHint.ai_protocol = IPPROTO_TCP;

		if (GetAddrInfoW(_Address, _Port, &_AddressHint, &_AddressInfo) != NO_ERROR)
		{
			return false;
		}
	}

	Socket = socket(_AddressInfo->ai_family, _AddressInfo->ai_socktype, _AddressInfo->ai_protocol);

	if (Socket == INVALID_SOCKET)
	{
		FreeAddrInfoW(_AddressInfo);
		return false;
	}

	if (connect(Socket, _AddressInfo->ai_addr, (int)(_AddressInfo->ai_addrlen)) != NO_ERROR)
	{
		closesocket(Socket);
		Socket = INVALID_SOCKET;
		FreeAddrInfoW(_AddressInfo);
		return false;
	}

	FreeAddrInfoW(_AddressInfo);

	return true;
}

void AuroraCore::Networking::EndPoint::Disconnect()
{
	if (Socket == INVALID_SOCKET)
	{
		return;
	}

	closesocket(Socket);

	Socket = INVALID_SOCKET;
}

bool AuroraCore::Networking::EndPoint::SendBuff(const uint8_t* _Buff, const size_t _BuffSize)
{
	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	size_t _Total = 0;

	do
	{
		size_t _ReturnValue = send(Socket, (const char*)(_Buff), (int)(_BuffSize), (int)(NULL));

		if (_ReturnValue == SOCKET_ERROR)
		{
			return false;
		}

		_Total += _ReturnValue;
	} while (_Total < _BuffSize);

	return true;
}

bool AuroraCore::Networking::EndPoint::SendInt8(const int8_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendInt16(const int16_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendInt32(const int32_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendInt64(const int64_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[7], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[7], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendUInt8(const uint8_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendUInt16(const uint16_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendUInt32(const uint32_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendUInt64(const uint64_t _Value)
{
	const uint8_t* _Data = (const uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!SendBuff(&_Data[7], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!SendBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!SendBuff(&_Data[7], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::SendFloat(const float _Value)
{
	int32_t _Mantisa = 0;
	int32_t _Exponent = 0;

	_Mantisa = (int32_t)(frexp(_Value, &_Exponent) * 10000.0f);

	if (!SendInt32(_Mantisa))
	{
		return false;
	}

	if (!SendInt32(_Exponent))
	{
		return false;
	}

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvBuff(uint8_t* _Buff, const size_t _BuffSize)
{
	if (Socket == INVALID_SOCKET)
	{
		return false;
	}

	if (recv(Socket, (char*)(_Buff), (int)(_BuffSize), MSG_WAITALL) != _BuffSize)
	{
		return false;
	}

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvInt8(int8_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvInt16(int16_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvInt32(int32_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvInt64(int64_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[7], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[7], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvUInt8(uint8_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvUInt16(uint16_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvUInt32(uint32_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvUInt64(uint64_t& _Value)
{
	uint8_t* _Data = (uint8_t*)(&_Value);

#ifdef AURORA_CORE_LITTLE_ENDIAN

	if (!RecvBuff(&_Data[7], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

	if (!RecvBuff(&_Data[0], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[1], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[2], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[3], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[4], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[5], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[6], 1))
	{
		return false;
	}

	if (!RecvBuff(&_Data[7], 1))
	{
		return false;
	}

#endif

	return true;
}

bool AuroraCore::Networking::EndPoint::RecvFloat(float& _Value)
{
	int32_t _Mantisa = 0;
	int32_t _Exponent = 0;

	if (!RecvInt32(_Mantisa))
	{
		return false;
	}

	if (!RecvInt32(_Exponent))
	{
		return false;
	}

	_Value = (float)(_Mantisa) / 10000.0f * pow(2.0f, (float)(_Exponent));

	return true;
}

AuroraCore::Networking::EndPoint::operator const SOCKET() const
{
	return Socket;
}

AuroraCore::Networking::EndPoint& AuroraCore::Networking::EndPoint::operator= (EndPoint&& _Other) noexcept
{
	AURORA_CORE_ASSERT_MSG(Socket == INVALID_SOCKET, AURORA_CORE_STRING_PREFIX("Move failed on non empty EndPoint object!"));

	Socket = _Other.Socket;

	_Other.Socket = INVALID_SOCKET;

	return *this;
}
