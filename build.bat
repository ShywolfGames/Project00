@echo off

set CommonCompilerFlags=-MT -nologo -Gm- -GR- -EHa- -Od -Oi -W4 -wd4201 -wd4100 -wd4189 -FC -Z7 -Fmwin32_Main.map

set CommonLinkerFlags= /link -incremental:no -opt:ref -subsystem:windows,5.1 user32.lib gdi32.lib winmm.lib
rem set CommonCompilerFlags=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 /Wv:18 -DHANDMADE_INTERNAL=1 -DHANDMADE_SLOW=1 -DHANDMADE_WIN32=1 -FC -Z7
rem set CommonLinkerFlags= -incremental:no -opt:ref -subsystem:windows,5.1 user32.lib gdi32.lib winmm.lib
rem set fileList= ..\code\vector4f.cpp ..\code\vector3f.cpp ..\code\vector2f.cpp
set fileList=..\Project00\MainApplication.cpp
set CommonLinkerFlagsNetwork= /link -opt:ref -subsystem:console,5.1 ws2_32.lib
set CommonLinkerFlagsConsole= /link -opt:ref -subsystem:console,5.1
IF NOT EXIST ..\build mkdir ..\build
pushd ..\build
del *.pdb > NUL 2> NUL


cl %CommonCompilerFlags% /EHsc %fileList% %CommonLinkerFlagsConsole%

rem cl %CommonCompilerFlags% /DWIN32 /EHsc ..\code\win32_BasicWindowsApp.cpp %CommonLinkerFlags%



popd
