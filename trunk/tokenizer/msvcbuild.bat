@rem Script to build Lua BitOp with MSVC.

@rem First change the paths to your Lua installation below.
@rem Then open a "Visual Studio .NET Command Prompt", cd to this directory
@rem and run this script. Afterwards copy the resulting bit.dll to
@rem the directory where lua.exe is installed.

@if not defined INCLUDE goto :FAIL

@setlocal
@rem Path to the Lua includes and the library file for the Lua DLL:
@set LUA_INC=-IG:\LuaInAll\lua\include -IC:\boost\boost
@set LUA_LIB=c:\MyShareware\CodingStudio\vendor\msvc_debug\lua5.1.lib

@set MYCOMPILE=cl /nologo /MD /O2 /W3 /c %LUA_INC% /wd4819
@set MYLINK=link /nologo
@set MYMT=mt /nologo

%MYCOMPILE% tokenizer.cpp
%MYLINK% /DLL /export:luaopen_tokenizer /out:tokenizer.dll tokenizer.obj %LUA_LIB%
if exist tokenizer.dll.manifest^
  %MYMT% -manifest tokenizer.dll.manifest -outputresource:tokenizer.dll;2

del *.obj *.exp *.manifest

@goto :END
:FAIL
@echo You must open a "Visual Studio .NET Command Prompt" to run this script
:END
