require "hash"

-- result userdata methods
local ret = hash.md5( "a" )
print(ret)
print(tostring( ret ) )
print( ret:lower() )
print( ret:upper() )
local raw = ret:raw()
print( raw )
for i = 1, raw:len() do
    print( string.format( "%2.2x", raw:byte( i ) ) )
end

print( "\n\n=====md2=========================================" )
print( ": ", hash.md2("") )
print( "a: ", hash.md2("a") )
print( "abc: ", hash.md2("abc") )
print( "message digest: ", hash.md2("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.md2("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.md2("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.md2("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====md4=========================================" )
print( ": ", hash.md4("") )
print( "a: ", hash.md4("a") )
print( "abc: ", hash.md4("abc") )
print( "message digest: ", hash.md4("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.md4("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.md4("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.md4("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====md5=========================================" )
print( ": ", hash.md5("") )
print( "a: ", hash.md5("a") )
print( "abc: ", hash.md5("abc") )
print( "message digest: ", hash.md5("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.md5("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.md5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.md5("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====sha1=========================================" )
print( ": ", hash.sha1("") )
print( "a: ", hash.sha1("a") )
print( "abc: ", hash.sha1("abc") )
print( "message digest: ", hash.sha1("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sha1("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sha1("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sha1("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====md4=========================================" )
print( ": ", hash.sha224("") )
print( "a: ", hash.sha224("a") )
print( "abc: ", hash.sha224("abc") )
print( "message digest: ", hash.sha224("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sha224("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sha224("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sha224("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====sha256=========================================" )
print( ": ", hash.sha256("") )
print( "a: ", hash.sha256("a") )
print( "abc: ", hash.sha256("abc") )
print( "message digest: ", hash.sha256("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sha256("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sha256("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sha256("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====sha384=========================================" )
print( ": ", hash.sha384("") )
print( "a: ", hash.sha384("a") )
print( "abc: ", hash.sha384("abc") )
print( "message digest: ", hash.sha384("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sha384("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sha384("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sha384("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====sha512=========================================" )
print( ": ", hash.sha512("") )
print( "a: ", hash.sha512("a") )
print( "abc: ", hash.sha512("abc") )
print( "message digest: ", hash.sha512("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sha512("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sha512("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sha512("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ripemd128=========================================" )
print( ": ", hash.ripemd128("") )
print( "a: ", hash.ripemd128("a") )
print( "abc: ", hash.ripemd128("abc") )
print( "message digest: ", hash.ripemd128("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.ripemd128("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.ripemd128("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.ripemd128("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ripemd160=========================================" )
print( ": ", hash.ripemd160("") )
print( "a: ", hash.ripemd160("a") )
print( "abc: ", hash.ripemd160("abc") )
print( "message digest: ", hash.ripemd160("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.ripemd160("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.ripemd160("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.ripemd160("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ripemd256=========================================" )
-- print( ": ", hash.ripemd256("") )
-- print( "a: ", hash.ripemd256("a") )
-- print( "abc: ", hash.ripemd256("abc") )
-- print( "message digest: ", hash.ripemd256("message digest") )
-- print( "abcdefghijklmnopqrstuvwxyz: ", 
-- hash.ripemd256("abcdefghijklmnopqrstuvwxyz") )
-- print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
-- hash.ripemd256("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
-- print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
-- hash.ripemd256("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ripemd320=========================================" )
-- print( ": ", hash.ripemd320("") )
-- print( "a: ", hash.ripemd320("a") )
-- print( "abc: ", hash.ripemd320("abc") )
-- print( "message digest: ", hash.ripemd320("message digest") )
-- print( "abcdefghijklmnopqrstuvwxyz: ", 
-- hash.ripemd320("abcdefghijklmnopqrstuvwxyz") )
-- print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
-- hash.ripemd320("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
-- print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
-- hash.ripemd320("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====tiger=========================================" )
print( ": ", hash.tiger("") )
print( "a: ", hash.tiger("a") )
print( "abc: ", hash.tiger("abc") )
print( "message digest: ", hash.tiger("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.tiger("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.tiger("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.tiger("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====whirlpool=========================================" )
print( ": ", hash.whirlpool("") )
print( "a: ", hash.whirlpool("a") )
print( "abc: ", hash.whirlpool("abc") )
print( "message digest: ", hash.whirlpool("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.whirlpool("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.whirlpool("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.whirlpool("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_3_128=========================================" )
print( ": ", hash.haval_3_128("") )
print( "a: ", hash.haval_3_128("a") )
print( "abc: ", hash.haval_3_128("abc") )
print( "message digest: ", hash.haval_3_128("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_3_128("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_3_128("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_3_128("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_3_160=========================================" )
print( ": ", hash.haval_3_160("") )
print( "a: ", hash.haval_3_160("a") )
print( "abc: ", hash.haval_3_160("abc") )
print( "message digest: ", hash.haval_3_160("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_3_160("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_3_160("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_3_160("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_3_192=========================================" )
print( ": ", hash.haval_3_192("") )
print( "a: ", hash.haval_3_192("a") )
print( "abc: ", hash.haval_3_192("abc") )
print( "message digest: ", hash.haval_3_192("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_3_192("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_3_192("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_3_192("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_3_224=========================================" )
print( ": ", hash.haval_3_224("") )
print( "a: ", hash.haval_3_224("a") )
print( "abc: ", hash.haval_3_224("abc") )
print( "message digest: ", hash.haval_3_224("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_3_224("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_3_224("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_3_224("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_3_256=========================================" )
print( ": ", hash.haval_3_256("") )
print( "a: ", hash.haval_3_256("a") )
print( "abc: ", hash.haval_3_256("abc") )
print( "message digest: ", hash.haval_3_256("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_3_256("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_3_256("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_3_256("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_4_128=========================================" )
print( ": ", hash.haval_4_128("") )
print( "a: ", hash.haval_4_128("a") )
print( "abc: ", hash.haval_4_128("abc") )
print( "message digest: ", hash.haval_4_128("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_4_128("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_4_128("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_4_128("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_4_160=========================================" )
print( ": ", hash.haval_4_160("") )
print( "a: ", hash.haval_4_160("a") )
print( "abc: ", hash.haval_4_160("abc") )
print( "message digest: ", hash.haval_4_160("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_4_160("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_4_160("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_4_160("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_4_192=========================================" )
print( ": ", hash.haval_4_192("") )
print( "a: ", hash.haval_4_192("a") )
print( "abc: ", hash.haval_4_192("abc") )
print( "message digest: ", hash.haval_4_192("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_4_192("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_4_192("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_4_192("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_4_224=========================================" )
print( ": ", hash.haval_4_224("") )
print( "a: ", hash.haval_4_224("a") )
print( "abc: ", hash.haval_4_224("abc") )
print( "message digest: ", hash.haval_4_224("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_4_224("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_4_224("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_4_224("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_4_256=========================================" )
print( ": ", hash.haval_4_256("") )
print( "a: ", hash.haval_4_256("a") )
print( "abc: ", hash.haval_4_256("abc") )
print( "message digest: ", hash.haval_4_256("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_4_256("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_4_256("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_4_256("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_5_128=========================================" )
print( ": ", hash.haval_5_128("") )
print( "a: ", hash.haval_5_128("a") )
print( "abc: ", hash.haval_5_128("abc") )
print( "message digest: ", hash.haval_5_128("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_5_128("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_5_128("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_5_128("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_5_160=========================================" )
print( ": ", hash.haval_5_160("") )
print( "a: ", hash.haval_5_160("a") )
print( "abc: ", hash.haval_5_160("abc") )
print( "message digest: ", hash.haval_5_160("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_5_160("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_5_160("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_5_160("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_5_192=========================================" )
print( ": ", hash.haval_5_192("") )
print( "a: ", hash.haval_5_192("a") )
print( "abc: ", hash.haval_5_192("abc") )
print( "message digest: ", hash.haval_5_192("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_5_192("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_5_192("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_5_192("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_5_224=========================================" )
print( ": ", hash.haval_5_224("") )
print( "a: ", hash.haval_5_224("a") )
print( "abc: ", hash.haval_5_224("abc") )
print( "message digest: ", hash.haval_5_224("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_5_224("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_5_224("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_5_224("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====haval_5_256=========================================" )
print( ": ", hash.haval_5_256("") )
print( "a: ", hash.haval_5_256("a") )
print( "abc: ", hash.haval_5_256("abc") )
print( "message digest: ", hash.haval_5_256("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.haval_5_256("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.haval_5_256("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.haval_5_256("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====crc16=========================================" )
print( ": ", hash.crc16("") )
print( "a: ", hash.crc16("a") )
print( "abc: ", hash.crc16("abc") )
print( "message digest: ", hash.crc16("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.crc16("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.crc16("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.crc16("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====crc16ccitt=========================================" )
print( ": ", hash.crc16ccitt("") )
print( "a: ", hash.crc16ccitt("a") )
print( "abc: ", hash.crc16ccitt("abc") )
print( "message digest: ", hash.crc16ccitt("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.crc16ccitt("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.crc16ccitt("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.crc16ccitt("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====crc32=========================================" )
print( ": ", hash.crc32("") )
print( "a: ", hash.crc32("a") )
print( "abc: ", hash.crc32("abc") )
print( "message digest: ", hash.crc32("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.crc32("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.crc32("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.crc32("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====fcs16=========================================" )
print( ": ", hash.fcs16("") )
print( "a: ", hash.fcs16("a") )
print( "abc: ", hash.fcs16("abc") )
print( "message digest: ", hash.fcs16("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.fcs16("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.fcs16("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.fcs16("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====fcs32=========================================" )
print( ": ", hash.fcs32("") )
print( "a: ", hash.fcs32("a") )
print( "abc: ", hash.fcs32("abc") )
print( "message digest: ", hash.fcs32("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.fcs32("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.fcs32("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.fcs32("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ghash32_3=========================================" )
print( ": ", hash.ghash32_3("") )
print( "a: ", hash.ghash32_3("a") )
print( "abc: ", hash.ghash32_3("abc") )
print( "message digest: ", hash.ghash32_3("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.ghash32_3("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.ghash32_3("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.ghash32_3("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====ghash32_5=========================================" )
print( ": ", hash.ghash32_5("") )
print( "a: ", hash.ghash32_5("a") )
print( "abc: ", hash.ghash32_5("abc") )
print( "message digest: ", hash.ghash32_5("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.ghash32_5("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.ghash32_5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.ghash32_5("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====gost=========================================" )
print( ": ", hash.gost("") )
print( "a: ", hash.gost("a") )
print( "abc: ", hash.gost("abc") )
print( "message digest: ", hash.gost("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.gost("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.gost("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.gost("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====size32=========================================" )
print( ": ", hash.size32("") )
print( "a: ", hash.size32("a") )
print( "abc: ", hash.size32("abc") )
print( "message digest: ", hash.size32("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.size32("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.size32("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.size32("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====adler32=========================================" )
print( ": ", hash.adler32("") )
print( "a: ", hash.adler32("a") )
print( "abc: ", hash.adler32("abc") )
print( "message digest: ", hash.adler32("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.adler32("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.adler32("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.adler32("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====edonkey=========================================" )
print( ": ", hash.edonkey("") )
print( "a: ", hash.edonkey("a") )
print( "abc: ", hash.edonkey("abc") )
print( "message digest: ", hash.edonkey("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.edonkey("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.edonkey("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.edonkey("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====emule=========================================" )
print( ": ", hash.emule("") )
print( "a: ", hash.emule("a") )
print( "abc: ", hash.emule("abc") )
print( "message digest: ", hash.emule("message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.emule("abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.emule("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.emule("12345678901234567890123456789012345678901234567890123456789012345678901234567890") )

print( "\n\n=====sum eg:md5=========================================" )
print( ": ", hash.sum("md5", "") )
print( "a: ", hash.sum("md5", "a") )
print( "abc: ", hash.sum("md5", "abc") )
print( "message digest: ", hash.sum("md5", "message digest") )
print( "abcdefghijklmnopqrstuvwxyz: ", 
hash.sum("md5", "abcdefghijklmnopqrstuvwxyz") )
print( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789: ", 
hash.sum("md5", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
print( "12345678901234567890123456789012345678901234567890123456789012345678901234567890: ", 
hash.sum("md5", "12345678901234567890123456789012345678901234567890123456789012345678901234567890") )
