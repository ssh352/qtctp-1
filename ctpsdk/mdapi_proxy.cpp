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
        QString filePath = QDir::temp().absoluteFilePath("ctpapi/mdapi.dll");
        extractQrcFile(":/ctpsdk_bin/thostmduserapi.dll", filePath);
        s_mod_mdapi = ::LoadLibraryW((wchar_t*)filePath.utf16());
    }
    if (s_mod_mdapi) {
        p_CreateMdApi = (f_CreateMdApi)GetProcAddress(
            s_mod_mdapi, "?CreateFtdcMdApi@CThostFtdcMdApi@@SAPAV1@PBD_N1@Z");

        p_GetApiVersion = (f_GetApiVersion)GetProcAddress(
            s_mod_mdapi, "?GetApiVersion@CThostFtdcMdApi@@SAPBDXZ");
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
