#include "MdApi.h"
#include <Windows.h>
#include "sdk_utils.h"
#include <QDir>

// protype,__stdcall,__cdecl,__fastcall
typedef MdApi*(__cdecl* f_CreateMdApi)(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast);
static f_CreateMdApi p_CreateMdApi = nullptr;

typedef const char*(__cdecl* f_GetApiVersion)();
static f_GetApiVersion p_GetApiVersion = nullptr;

// init
static void LoadMdApi()
{
    static HMODULE s_mod_mdapi = nullptr;
    if (!s_mod_mdapi) {
#ifdef WIN64
        QString filePath = QDir::temp().absoluteFilePath("ctpapi_x64/mdapi.dll");
#else
        QString filePath = QDir::temp().absoluteFilePath("ctpapi/mdapi.dll");
#endif
        extractQrcFile(":/ctpsdk_bin/thostmduserapi.dll", filePath);
        s_mod_mdapi = ::LoadLibraryW((wchar_t*)filePath.utf16());
    }
    if (s_mod_mdapi) {
        p_CreateMdApi = (f_CreateMdApi)GetProcAddress(
#ifdef WIN64
            s_mod_mdapi, "?CreateFtdcMdApi@CThostFtdcMdApi@@SAPEAV1@PEBD_N1@Z");
#else
            s_mod_mdapi, "?CreateFtdcMdApi@CThostFtdcMdApi@@SAPAV1@PBD_N1@Z");
#endif

        p_GetApiVersion = (f_GetApiVersion)GetProcAddress(
#ifdef WIN64
            s_mod_mdapi, "?GetApiVersion@CThostFtdcMdApi@@SAPEBDXZ");
#else
            s_mod_mdapi, "?GetApiVersion@CThostFtdcMdApi@@SAPBDXZ");
#endif
    }
}

// proxy
MdApi* MdApi::CreateMdApi(const char* pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast)
{
    LoadMdApi();

    if (p_CreateMdApi) {
        return p_CreateMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);
    }
    else {
        return nullptr;
    }
}

const char* MdApi::GetApiVersion()
{
    LoadMdApi();

    if (p_GetApiVersion) {
        return p_GetApiVersion();
    }
    else {
        return nullptr;
    }
}
