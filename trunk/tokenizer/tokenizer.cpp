#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/bind.hpp>
#include <string>

#define MYNAME		"tokenizer"

#ifndef RELEASE
#  define RELEASE "0.2"
#endif

using namespace std;

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static char * getVersion( )
{
    static char marker[] = { "tokenizer v" RELEASE " (c) DForD Software"};
    return( marker );
}

static int pusherror(lua_State *L, const char *info)
{
    int save_errno = errno;      /* in case lua_pushnil() or lua_pushfstring changes errno */

    lua_pushnil(L);
#ifdef _MSC_VER
    if (info==NULL)
        lua_pushstring(L, strerror(save_errno));
    else
        lua_pushfstring(L, "%s: %s", info, strerror (save_errno));
#else
    lua_pushstring(L, info);
#endif
    lua_pushnumber(L, save_errno);

    return 3;
}

static int parse(lua_State* L)
{
    string strToParse;
    if (lua_isstring(L, 1))
        strToParse = lua_tostring(L, 1);
    else
        return pusherror(L, "parse(string [, seperators]);") ;

    string strSep = "-;|()[]{}+-*/.,\\<>?\":&^%$#@!~`=' \t\r\n";
    if (lua_isstring(L, 2))
        strSep = lua_tostring(L, 2);
    
    typedef boost::tokenizer<boost::char_separator<char> > Tok;
    boost::char_separator<char> sep(strSep.c_str()); // default constructed
    Tok tok(strToParse, sep);
    std::vector<std::string> arr;
    for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        arr.push_back(*tok_iter);
    std::sort(arr.begin(), arr.end());
    std::vector<std::string>::iterator it = std::unique(arr.begin(), arr.end());
    arr.erase(it, arr.end());

    lua_newtable (L);

    int index = 0;
    for (vector<string>::iterator it = arr.begin();
        arr.end() != it;
        ++it)
    {
        lua_pushnumber (L,index++);
        lua_pushstring (L, it->c_str());
        lua_rawset (L, -3);
    }
    
    return 1;
}

static bool not_leading_with(string str, string strLeading)
{
    string::size_type nPos = str.find(strLeading);
    return (nPos != 0);
}

static int extract(lua_State* L)
{
    string strToParse;
    if (lua_isstring(L, 1))
        strToParse = lua_tostring(L, 1);
    else
        return pusherror(L, "extract(string, leading string [, seperators]);") ;

    string strLeading;
    if (lua_isstring(L, 2))
        strLeading = lua_tostring(L, 2);
    else
        return pusherror(L, "extract(string, leading string [, seperators]);") ;

    string strSep = "-;|()[]{}+-*/.,\\<>?\":&^%$#@!~`=' \t\r\n";
    if (lua_isstring(L, 3))
        strSep = lua_tostring(L, 3);

    typedef boost::tokenizer<boost::char_separator<char> > Tok;
    boost::char_separator<char> sep(strSep.c_str()); // default constructed
    Tok tok(strToParse, sep);
    std::vector<std::string> arr;
    for(Tok::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
        arr.push_back(*tok_iter);
    std::sort(arr.begin(), arr.end());
    std::vector<std::string>::iterator it = std::unique(arr.begin(), arr.end());
    arr.erase(it, arr.end());
    it = std::find_if( arr.begin(), arr.end(),
        boost::lambda::_1 > strLeading);
    if (arr.end() != it && arr.begin() != it)
    {        
        cout << "remove to " << *it << endl;
        arr.erase(arr.begin(), it);
    }

    it = std::find_if(arr.begin(), arr.end(),
        boost::bind(not_leading_with, _1, strLeading));
    if (arr.end() != it)
    {
        cout << "remove from " << *it << endl;
        arr.erase(it, arr.end());
    }

    lua_newtable (L);

    int index = 0;
    for (vector<string>::iterator it = arr.begin();
        arr.end() != it;
        ++it)
    {
        lua_pushnumber (L,index++);
        lua_pushstring (L, it->c_str());
        lua_rawset (L, -3);
    }

    return 1;
}

static const luaL_reg R[] =
{
    {"parse", parse},
    {"extract", extract},
    {NULL,		NULL}
};

/**
 * Bind our exported functions to the Lua intepretter, making our functions
 * available to the calling script.
 * @param L The lua intepreter object.
 * @return 1 (for the table we leave on the stack)
 */

LUALIB_API int luaopen_tokenizer (lua_State *L)
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
