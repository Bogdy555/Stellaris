#ifndef AuroraCore_Resources_hpp

#define AuroraCore_Resources_hpp



#define AURORA_CORE_VERSION_LIST 1, 0, 0, 0



#define AURORA_CORE_VERSION_STRING_A "1.0.0.0"
#define AURORA_CORE_VERSION_STRING_W L"1.0.0.0"

#ifdef _UNICODE

#define AURORA_CORE_VERSION_STRING AURORA_CORE_VERSION_STRING_W

#endif

#ifndef _UNICODE

#define AURORA_CORE_VERSION_STRING AURORA_CORE_VERSION_STRING_A

#endif



#define AURORA_CORE_APP_NAME_A "AuroraCore"
#define AURORA_CORE_APP_NAME_W L"AuroraCore"

#ifdef _UNICODE

#define AURORA_CORE_APP_NAME AURORA_CORE_APP_NAME_W

#endif

#ifndef _UNICODE

#define AURORA_CORE_APP_NAME AURORA_CORE_APP_NAME_A

#endif



#define AURORA_CORE_FILE_NAME_A "AuroraCore.lib"
#define AURORA_CORE_FILE_NAME_W L"AuroraCore.lib"

#ifdef _UNICODE

#define AURORA_CORE_FILE_NAME AURORA_CORE_FILE_NAME_W

#endif

#ifndef _UNICODE

#define AURORA_CORE_FILE_NAME AURORA_CORE_FILE_NAME_A

#endif



#define AURORA_CORE_COMPANY_NAME_A "AuroraCore"
#define AURORA_CORE_COMPANY_NAME_W L"AuroraCore"

#ifdef _UNICODE

#define AURORA_CORE_COMPANY_NAME AURORA_CORE_COMPANY_NAME_W

#endif

#ifndef _UNICODE

#define AURORA_CORE_COMPANY_NAME AURORA_CORE_COMPANY_NAME_A

#endif



#define AURORA_CORE_COPY_RIGHT_EN_US_A "Copyright AuroraCore. All rights reserved."
#define AURORA_CORE_COPY_RIGHT_EN_US_W L"Copyright © AuroraCore™. All rights reserved."

#ifdef _UNICODE

#define AURORA_CORE_COPY_RIGHT_EN_US AURORA_CORE_COPY_RIGHT_EN_US_W

#endif

#ifndef _UNICODE

#define AURORA_CORE_COPY_RIGHT_EN_US AURORA_CORE_COPY_RIGHT_EN_US_A

#endif



#define AURORA_CORE_WAV_RESOURCE 256



#endif
