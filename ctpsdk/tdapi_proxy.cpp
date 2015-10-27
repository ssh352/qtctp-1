#include "TraderApi.h"
#include <Windows.h>
#include "sdk_utils.h"
#include <QDir>

// protype,__stdcall,__cdecl,__fastcall
typedef TraderApi*(__cdecl* f_CreateTraderApi)(const char* pszFlowPath);
static f_CreateTraderApi p_CreateTraderApi = nullptr;

typedef const char*(__cdecl* f_GetApiVersion)();
static f_GetApiVersion p_GetApiVersion = nullptr;

// init
static void LoadTdApi()
{
    static HMODULE s_mod_tdapi = nullptr;
    if (!s_mod_tdapi) {
#ifdef WIN64
        QString filePath = QDir::temp().absoluteFilePath("ctpapi_x64/tdapi.dll");
#else
        QString filePath = QDir::temp().absoluteFilePath("ctpapi/tdapi.dll");
#endif
        extractQrcFile(":/ctpsdk_bin/thosttraderapi.dll", filePath);
        s_mod_tdapi = LoadLibraryW((wchar_t*)filePath.utf16());
    }
    if (s_mod_tdapi) {
        p_CreateTraderApi = (f_CreateTraderApi)GetProcAddress(
#ifdef WIN64
            s_mod_tdapi, "?CreateFtdcTraderApi@CThostFtdcTraderApi@@SAPEAV1@PEBD@Z");
#else
            s_mod_tdapi, "?CreateFtdcTraderApi@CThostFtdcTraderApi@@SAPAV1@PBD@Z");
#endif

        p_GetApiVersion = (f_GetApiVersion)GetProcAddress(
#ifdef WIN64
            s_mod_tdapi, "?GetApiVersion@CThostFtdcTraderApi@@SAPEBDXZ");
#else
            s_mod_tdapi, "?GetApiVersion@CThostFtdcTraderApi@@SAPBDXZ");
#endif
    }
}

// proxy
TraderApi* TraderApi::CreateTraderApi(const char* pszFlowPath)
{
    LoadTdApi();

    if (p_CreateTraderApi) {
        return p_CreateTraderApi(pszFlowPath);
    }
    else {
        return nullptr;
    }
}

const char* TraderApi::GetApiVersion()
{
    LoadTdApi();

    if (p_GetApiVersion) {
        return p_GetApiVersion();
    }
    else {
        return nullptr;
    }
}
