#ifndef Stellaris_Resources_hpp

#define Stellaris_Resources_hpp



#define STELLARIS_VERSION_LIST 1, 0, 0, 0



#define STELLARIS_VERSION_STRING_A "1.0.0.0"
#define STELLARIS_VERSION_STRING_W L"1.0.0.0"

#ifdef _UNICODE

#define STELLARIS_VERSION_STRING STELLARIS_VERSION_STRING_W

#endif

#ifndef _UNICODE

#define STELLARIS_VERSION_STRING STELLARIS_VERSION_STRING_A

#endif



#define STELLARIS_APP_NAME_A "Stellaris"
#define STELLARIS_APP_NAME_W L"Stellaris"

#ifdef _UNICODE

#define STELLARIS_APP_NAME STELLARIS_APP_NAME_W

#endif

#ifndef _UNICODE

#define STELLARIS_APP_NAME STELLARIS_APP_NAME_A

#endif



#define STELLARIS_FILE_NAME_A "Stellaris.exe"
#define STELLARIS_FILE_NAME_W L"Stellaris.exe"

#ifdef _UNICODE

#define STELLARIS_FILE_NAME STELLARIS_FILE_NAME_W

#endif

#ifndef _UNICODE

#define STELLARIS_FILE_NAME STELLARIS_FILE_NAME_A

#endif



#define STELLARIS_COMPANY_NAME_A "AuroraCore"
#define STELLARIS_COMPANY_NAME_W L"AuroraCore"

#ifdef _UNICODE

#define STELLARIS_COMPANY_NAME STELLARIS_COMPANY_NAME_W

#endif

#ifndef _UNICODE

#define STELLARIS_COMPANY_NAME STELLARIS_COMPANY_NAME_A

#endif



#define STELLARIS_COPY_RIGHT_EN_US_A "Copyright AuroraCore. All rights reserved."
#define STELLARIS_COPY_RIGHT_EN_US_W L"Copyright © AuroraCore™. All rights reserved."

#ifdef _UNICODE

#define STELLARIS_COPY_RIGHT_EN_US STELLARIS_COPY_RIGHT_EN_US_W

#endif

#ifndef _UNICODE

#define STELLARIS_COPY_RIGHT_EN_US STELLARIS_COPY_RIGHT_EN_US_A

#endif



#define STELLARIS_IDI_MAIN_ICON 1



#define STELLARIS_IDM_MAIN_MANIFEST 1



#endif
