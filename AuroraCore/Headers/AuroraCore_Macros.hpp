#ifndef AuroraCore_Macros_hpp

#define AuroraCore_Macros_hpp



#include "AuroraCore.hpp"



#ifdef _UNICODE

#define AURORA_CORE_CHAR wchar_t
#define AURORA_CORE_STRING std::wstring
#define AURORA_CORE_TO_STRING(X) std::to_wstring(X)
#define AURORA_CORE_STRING_PREFIX(X) L ## X

#endif

#ifndef _UNICODE

#define AURORA_CORE_CHAR char
#define AURORA_CORE_STRING std::string
#define AURORA_CORE_TO_STRING(X) std::to_string(X)
#define AURORA_CORE_STRING_PREFIX(X) X

#endif



#define AURORA_CORE_PRINT(X) std::wcout << X
#define AURORA_CORE_PRINT_LINE(X) std::wcout << X << L'\n'



#ifdef _DEBUG

#define AURORA_CORE_LOG(X) std::wcout << X
#define AURORA_CORE_LOG_LINE(X) std::wcout << X << L'\n'

#endif

#ifndef _DEBUG

#define AURORA_CORE_LOG(X)
#define AURORA_CORE_LOG_LINE(X)

#endif



#define AURORA_CORE_PRINT_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)
#define AURORA_CORE_PRINT_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)

#ifdef _UNICODE

#define AURORA_CORE_PRINT_OUTPUT_DEBUG_STR(X) AURORA_CORE_PRINT_OUTPUT_DEBUG_STR_W(X)

#endif

#ifndef _UNICODE

#define AURORA_CORE_PRINT_OUTPUT_DEBUG_STR(X) AURORA_CORE_PRINT_OUTPUT_DEBUG_STR_A(X)

#endif

#define AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")
#define AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")

#ifdef _UNICODE

#define AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE(X) AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE_W(X)

#endif

#ifndef _UNICODE

#define AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE(X) AURORA_CORE_PRINT_OUTPUT_DEBUG_LINE_A(X)

#endif



#ifdef _DEBUG

#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR_W(X) OutputDebugStringW(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR_A(X) OutputDebugStringA(X)

#ifdef _UNICODE

#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR(X) AURORA_CORE_LOG_OUTPUT_DEBUG_STR_W(X)

#endif

#ifndef _UNICODE

#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR(X) AURORA_CORE_LOG_OUTPUT_DEBUG_STR_A(X)

#endif

#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_W(X) OutputDebugStringW(X); OutputDebugStringW(L"\n")
#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_A(X) OutputDebugStringA(X); OutputDebugStringA("\n")

#ifdef _UNICODE

#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE(X) AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_W(X)

#endif

#ifndef _UNICODE

#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE(X) AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_A(X)

#endif

#endif

#ifndef _DEBUG

#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR_W(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR_A(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_STR(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_W(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE_A(X)
#define AURORA_CORE_LOG_OUTPUT_DEBUG_LINE(X)

#endif



#ifdef _DEBUG

#define AURORA_CORE_DEBUG_BREAK() __debugbreak()

#define AURORA_CORE_DEBUG_BREAK_MSG_W(Msg) MessageBoxW(NULL, Msg, L"Debug break!", MB_OK); __debugbreak()
#define AURORA_CORE_DEBUG_BREAK_MSG_A(Msg) MessageBoxA(NULL, Msg, L"Debug break!", MB_OK); __debugbreak()

#ifdef _UNICODE

#define AURORA_CORE_DEBUG_BREAK_MSG(Msg) AURORA_CORE_DEBUG_BREAK_MSG_W(Msg)

#endif

#ifndef _UNICODE

#define AURORA_CORE_DEBUG_BREAK_MSG(Msg) AURORA_CORE_DEBUG_BREAK_MSG_A(Msg)

#endif

#endif

#ifndef _DEBUG

#define AURORA_CORE_DEBUG_BREAK()
#define AURORA_CORE_DEBUG_BREAK_MSG_W(Msg)
#define AURORA_CORE_DEBUG_BREAK_MSG_A(Msg)
#define AURORA_CORE_DEBUG_BREAK_MSG(Msg)

#endif



#ifdef _DEBUG

#define AURORA_CORE_ASSERT(Condition) if (!(Condition))\
{\
	AURORA_CORE_DEBUG_BREAK();\
}

#define AURORA_CORE_ASSERT_MSG_W(Condition, Msg) if (!(Condition))\
{\
	AURORA_CORE_DEBUG_BREAK_MSG_W(Msg);\
}

#define AURORA_CORE_ASSERT_MSG_A(Condition, Msg) if (!(Condition))\
{\
	AURORA_CORE_DEBUG_BREAK_MSG_A(Msg);\
}

#ifdef _UNICODE

#define AURORA_CORE_ASSERT_MSG(Condition, Msg) AURORA_CORE_ASSERT_MSG_W(Condition, Msg)

#endif

#ifndef _UNICODE

#define AURORA_CORE_ASSERT_MSG(Condition, Msg) AURORA_CORE_ASSERT_MSG_A(Condition, Msg)

#endif

#endif

#ifndef _DEBUG

#define AURORA_CORE_ASSERT(Condition)
#define AURORA_CORE_ASSERT_MSG_W(Condition, Msg)
#define AURORA_CORE_ASSERT_MSG_A(Condition, Msg)
#define AURORA_CORE_ASSERT_MSG(Condition, Msg)

#endif



#ifdef _DEBUG

#define AURORA_CORE_DEBUG_CALL(X) X
#define AURORA_CORE_RELEASE_CALL(X)

#endif

#ifndef _DEBUG

#define AURORA_CORE_DEBUG_CALL(X)
#define AURORA_CORE_RELEASE_CALL(X) X

#endif



#ifdef _WIN64

#define AURORA_CORE_X64_CALL(X) X
#define AURORA_CORE_X86_CALL(X)

#define AURORA_CORE_LITTLE_ENDIAN

#endif

#ifndef _WIN64

#define AURORA_CORE_X64_CALL(X)
#define AURORA_CORE_X86_CALL(X) X

#define AURORA_CORE_LITTLE_ENDIAN

#endif



#ifdef AURORA_CORE_LITTLE_ENDIAN

#define AURORA_CORE_LITTLE_ENDIAN_CALL(X) X
#define AURORA_CORE_BIG_ENDIAN_CALL(X)

#endif

#ifdef AURORA_CORE_BIG_ENDIAN

#define AURORA_CORE_LITTLE_ENDIAN_CALL(X)
#define AURORA_CORE_BIG_ENDIAN_CALL(X) X

#endif



#define AURORA_CORE_COM_RELEASE(X) if (X)\
{\
	X->Release();\
	X = nullptr;\
}



#endif
