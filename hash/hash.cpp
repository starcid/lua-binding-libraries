#include <windows.h>
#include <string>
#include <cstdlib>
#include "HashCalc.h"
#include "hash.h"

using namespace std;

typedef struct hash_ud 
{
    size_t nLen;
    unsigned char * pszDigest;
} hash_ud;

string BinToHex(unsigned char * pszDigest, size_t ulLen, bool bUpperCase)
{
    string strRet;
    char szNum[] = "0123456789ABCDEF";
    if (!bUpperCase)
    {
        strcpy(szNum, "0123456789abcdef");
    }
    char szDigestRes[64 * 2 +1] = {0}; // > 64 * 2 is ok

    int nIndex = 0;
    while (ulLen--)
    {
        szDigestRes[nIndex++] = szNum[(*pszDigest & 0xF0) >> 4];
        szDigestRes[nIndex++] = szNum[*pszDigest & 0x0F];
        pszDigest++;
    }
    strRet = szDigestRes;
    return strRet;
}
extern "C"{

    static char * getVersion( )
    {
        static char marker[] = { LIBNAME " v" LIBVER " (c) DForD Software."};
        return( marker );
    }

    static int hash_lower(lua_State* L)
    {
        hash_ud* hash_userdata = (hash_ud *) luaL_checkudata(L, 1, "hash_metatable");

        lua_pop(L, 1);

        lua_pushstring(L, BinToHex( hash_userdata->pszDigest, hash_userdata->nLen, false ).c_str() );
        return 1;
    }

    static int hash_upper(lua_State* L)
    {
        hash_ud* hash_userdata = (hash_ud *) luaL_checkudata(L, 1, "hash_metatable");

        lua_pop(L, 1);

        lua_pushstring(L, BinToHex( hash_userdata->pszDigest, hash_userdata->nLen, true ).c_str() );
        return 1;
    }

    static int hash_destroy(lua_State* L)
    {
        hash_ud* hash_userdata = (hash_ud *) luaL_checkudata(L, 1, "hash_metatable");

        lua_pop(L, 1);
        delete[] hash_userdata->pszDigest;
        hash_userdata->pszDigest = NULL;
        hash_userdata->nLen = 0;
        return 0;
    }

    static int hash_raw(lua_State* L)
    {
        hash_ud* hash_userdata = (hash_ud *) luaL_checkudata(L, 1, "hash_metatable");

        lua_pop(L, 1);
        lua_pushlstring(L, (const char *)hash_userdata->pszDigest, hash_userdata->nLen);
        return 1;
    }

    static int md2(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CMD2> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);        

        return 1;
    }

    static int md4(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CMD4> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int md5(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CMD5> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int sha1(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSHA1> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int sha224(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSHA224> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int sha256(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSHA256> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int sha512(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSHA512> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int sha384(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSHA384 > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);    
        return 1;
    }

    static int ripemd128(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CRMD128 > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int ripemd160(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CRMD160 > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int ripemd256(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CRMD256 > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int ripemd320(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CRMD320 > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int tiger(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CTiger > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int whirlpool(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CWhirlPool > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_3_128(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL3<128> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_3_160(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL3<160> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_3_192(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL3<192> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_3_224(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL3<224> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_3_256(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL3<256> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_4_128(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL4<128> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_4_160(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL4<160> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_4_192(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL4<192> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_4_224(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL4<224> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_4_256(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL4<256> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_5_128(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL5<128> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_5_160(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL5<160> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_5_192(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL5<192> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_5_224(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL5<224> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int crc16(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CCRC16> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int haval_5_256(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CHAVAL5<256> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int crc16ccitt(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CCRC16CCITT> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int crc32(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CCRC32> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest);  
        return 1;
    }

    static int fcs16(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CFCS16> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int fcs32(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CFCS32> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int ghash32_3(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CGHash<3> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int ghash32_5(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CGHash<5> > hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int gost(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CGostHash> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int size32(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CSizeHash> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int adler32(lua_State* L)
    {
        size_t l;
        const char *message = luaL_checklstring(L, 1, &l);
        lua_pop(L, 1);

        hash_ud *pu = (hash_ud *) lua_newuserdata(L, sizeof(hash_ud));
        // set metatable for userdata
        luaL_getmetatable(L, "hash_metatable");
        lua_setmetatable(L, -2);
        CHash<CAdler32> hash;
        pu->nLen = hash.GetDigestLength();
        pu->pszDigest = new unsigned char[pu->nLen];
        hash.HashText((unsigned char *)message, l, pu->pszDigest); 
        return 1;
    }

    static int sum(lua_State* L);

    static const struct luaL_reg hash_metamethods[] = {
        { "__tostring", hash_upper},
        { "__gc", hash_destroy},
        { "raw", hash_raw},
        { "upper", hash_upper},
        { "lower", hash_lower},
        {NULL, NULL} /* sentinel */
    };

    static const struct luaL_reg hash_methods[] = {
        { "md2", md2 },
        { "md4", md4 },
        { "md5", md5 },
        { "sha1", sha1 },
        { "sha224", sha224 },
        { "sha256", sha256 },
        { "sha512", sha512 },
        { "sha384", sha384 },
        { "ripemd128", ripemd128 },
        { "ripemd160", ripemd160 },
        { "ripemd256", ripemd256 },
        { "ripemd320", ripemd320 },
        { "tiger", tiger },
        { "whirlpool", whirlpool },
        { "haval_3_128", haval_3_128 },
        { "haval_3_160", haval_3_160 },
        { "haval_3_192", haval_3_192 },
        { "haval_3_224", haval_3_224 },
        { "haval_3_256", haval_3_256 },
        { "haval_4_128", haval_4_128 },
        { "haval_4_160", haval_4_160 },
        { "haval_4_192", haval_4_192 },
        { "haval_4_224", haval_4_224 },
        { "haval_4_256", haval_4_256 },
        { "haval_5_128", haval_5_128 },
        { "haval_5_160", haval_5_160 },
        { "haval_5_192", haval_5_192 },
        { "haval_5_224", haval_5_224 },
        { "haval_5_256", haval_5_256 },
        { "crc16", crc16 },
        { "crc16ccitt", crc16ccitt },
        { "crc32", crc32 },
        { "fcs16", fcs16 },
        { "fcs32", fcs32 },
        { "ghash32_3", ghash32_3 },
        { "ghash32_5", ghash32_5 },
        { "gost", gost },
        { "size32", size32 },
        { "adler32", adler32 },
        { "edonkey", md4 },
        { "emule", md4 },
        { "sum", sum },
        { NULL, NULL }
    };

    static int sum(lua_State* L)
    {
        const char *algo = luaL_checkstring(L, 1);
        size_t l;
        const char *message = luaL_checklstring(L, 2, &l);
        lua_pop(L, 2);
        lua_pushlstring(L, message, l);

        for (luaL_reg* r = (luaL_reg *)&hash_methods[0]; r->name != NULL; r++)
        {
            if (strcmp(r->name, algo) == 0)
            {
                return r->func(L);
            }
        }

        lua_pushnil(L);
        return 1;
    }

    int luaopen_hash(lua_State* L) 
    {
        // create metatable
        luaL_newmetatable(L, "hash_metatable");
        // metatable.__index = metatable
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        // register methods
        luaL_register(L, NULL, hash_metamethods);

        // register functions
        luaL_register(L, "hash", hash_methods);
        lua_getglobal(L, "hash");

        char *version = getVersion();
        lua_pushliteral (L, "_VERSION");
        lua_pushstring (L, version );
        lua_rawset(L, -3);
        lua_pop(L, 1);
        return 1;
    }
};