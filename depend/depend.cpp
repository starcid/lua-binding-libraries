#include <algorithm>
#include <vector>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include <detours.h>

#define MYNAME	"depend"

#ifndef RELEASE
#  define RELEASE "0.1"
#endif

using namespace std;


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static char * getVersion( )
{
    static char marker[] = { "depend v" RELEASE " (c) DForD Software"};
    return( marker );
}

static BOOL CALLBACK ListFileCallback(PVOID pContext,
                                      PCHAR pszOrigFile,
                                      PCHAR pszFile,
                                      PCHAR *ppszOutFile)
{
    vector<string>* pArr = (vector<string>*)pContext;
    (void)pszFile;

    *ppszOutFile = NULL;

    static CHAR s_szFile[MAX_PATH] = "\0";
#ifdef _CRT_INSECURE_DEPRECATE
    strcpy_s(s_szFile, sizeof(s_szFile), pszOrigFile);
#else
    strcpy(s_szFile, pszOrigFile);
#endif

    pArr->push_back(s_szFile);
    return TRUE;
}

static int check(lua_State* L)
{
    const char* executable = luaL_checkstring(L, 1);
    const char* importdll = luaL_checkstring(L, 2);

    BOOL bGood = TRUE;
    HANDLE hOld = INVALID_HANDLE_VALUE;
    PDETOUR_BINARY pBinary = NULL;
    vector<string> g_arrFiles;

    hOld = CreateFileA(executable,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hOld == INVALID_HANDLE_VALUE) 
    {
        lua_pushfstring(L, "%s: Failed to open input file with error: %d\n",
            executable, GetLastError());
        lua_pushboolean(L, FALSE);
        goto end;
    }

    if ((pBinary = DetourBinaryOpen(hOld)) == NULL) 
    {
        lua_pushfstring(L, "%s: DetourBinaryOpen failed: %d\n", executable, GetLastError());
        lua_pushboolean(L, FALSE);
        goto end;
    }

    if (hOld != INVALID_HANDLE_VALUE) 
    {
        CloseHandle(hOld);
        hOld = INVALID_HANDLE_VALUE;
    }

    if (!DetourBinaryEditImports(pBinary,
        (PVOID)&g_arrFiles,
        NULL,
        ListFileCallback,
        NULL,
        NULL)) 
    {
        lua_pushfstring(L, "%s: DetourBinaryEditImports failed: %d\n", executable, GetLastError());
        lua_pushboolean(L, FALSE);
        DetourBinaryClose(pBinary);
        goto end;
    }

    DetourBinaryClose(pBinary);
    pBinary = NULL;

    // search in g_arrFiles
    for (vector<string>::iterator it = g_arrFiles.begin();
        g_arrFiles.end() != it;
        ++it)
    {
        if (_stricmp(it->c_str(), importdll) == 0)
        {
            lua_pushboolean(L, TRUE);
            goto end;
        }
    }
    lua_pushboolean(L, FALSE);
end:
    if (pBinary) 
    {
        DetourBinaryClose(pBinary);
        pBinary = NULL;
    }

    if (hOld != INVALID_HANDLE_VALUE) 
    {
        CloseHandle(hOld);
        hOld = INVALID_HANDLE_VALUE;
    }
    
    return 1;
}

static const luaL_reg R[] =
{
    {"check", check},
    {NULL,	NULL}
};

/**
 * Bind our exported functions to the Lua intepretter, making our functions
 * available to the calling script.
 * @param L The lua intepreter object.
 * @return 1 (for the table we leave on the stack)
 */

LUALIB_API int luaopen_depend (lua_State *L)
{
    /* Version number from CVS marker. */
    char *version = getVersion();

#ifdef PRE_LUA51
    luaL_openlib (L, MYNAME, R, 0);
#else
    luaL_register (L, MYNAME, R);
#endif

    lua_pushliteral (L, "_VERSION");
    lua_pushstring (L, version );
    lua_settable (L, -3);

    return 1;
}


};
